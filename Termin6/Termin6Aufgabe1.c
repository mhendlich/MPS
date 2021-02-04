#include "../h/aic.h"
#include "../h/pio.h"
#include "../h/pmc.h"
#include "../h/tc.h"
#include "../h/usart.h"

#include <stdint.h>

// constants for scale weight calculation
const static int C1 = 2000;
const static int C2 = 0;

#define DEFAULT_BAUD 38400
#define CLOCK_SPEED 25000000
// US_BAUD =  (CLOCK_SPEED / (16*(DEFAULT_BAUD))	// 25MHz / ( 16 * 38400) = 40.69  -> 41 -> 0x29
#define US_BAUD 0x29

// flags for timer channel initialization
#define TC_INIT TC_CLKS_MCK2 | TC_LDBSTOP | TC_CAPT | TC_LDRA_RISING_EDGE | TC_LDRB_RISING_EDGE

typedef enum { IO_SW1, IO_SW2, IO_SW3 } IO_Switches;

typedef enum { IO_Off, IO_On } IO_States;

// current step of th finite state machine
int step = 1;

// weight of the coin we use in mg
const static int muenzgewicht = 5735;


/**
 *	Hardware
 */
inline uint8_t IsKeydown(const IO_Switches keyNr) {
   StructPIO* piobaseB = PIOB_BASE;

   static const uint8_t keys[] = { KEY1, KEY2, KEY3 };

   if(keyNr > IO_SW3)
      return 0;

   const uint8_t key = keys[keyNr];

   // check if the chosen keys are already under control of the PIO
   if(~piobaseB->PIO_PSR & key) {
      piobaseB->PIO_PER = key;

      // check if the chosen keys are configured as input
      if(piobaseB->PIO_OSR & key)
         piobaseB->PIO_ODR = key;
   }

   // check if data status register of the chosen key is low
   if((~piobaseB->PIO_PDSR & key))
      return 1; // if yes, the key is pressed

   return 0;
}

inline void setLEDs(int numberToShow) {
   StructPIO* piobaseB = PIOB_BASE;

   piobaseB->PIO_SODR = ALL_LEDS; // clear all leds

   // shift number 8 bits to the left (as the LEDs on the board are connected to pins 7 to 14 and wa start at bit 0)
   // we also need to reverse the bits inside of that byte as the LEDs are connected the other way around
   uint16_t leds = reverseBits(numberToShow) << 8;

   // clear output for the selected leds as they are low active
   piobaseB->PIO_CODR = leds;
}

char putch(char Zeichen) {
   StructUSART* usartbase0 = USART0;

   // check if transmitter of this channel is ready (empty buffer)
   if(usartbase0->US_CSR & US_TXRDY) {
      // save chracter inti output buffer
      usartbase0->US_THR = Zeichen;
   } else {
      // return 0 to indicate that transmission was not yet possible
      Zeichen = 0;
   }
   return Zeichen;
}

void putstring(char* String) {
   int i = 0;

   // iterate through the characters of the given string
   while(String[i] != 0) {

      // try to output the char, if it fails try again until it goes through successfully
      while(!(putch(String[i]))) {
      }
      i = i + 1;
   }
}

/**
 *	Interrupt
 */
// label function as interrupt
void taste_irq_handler(void) __attribute__((interrupt));

void taste_irq_handler(void) {
   StructPIO* piobaseB = PIOB_BASE;
   StructAIC* aicbase = AIC_BASE;

   // use keys to step through our finite state machine
   if(IsKeydown(IO_SW1)) {
      if(step == 1) {
         step = 2;
      }
   } else if(IsKeydown(IO_SW2)) {
      if(step == 2) {
         step = 3;
      }
   } else if(IsKeydown(IO_SW3)) {
      if(step == 3) {
         step = 4;
      }
   }

   // signal end of interrupt
   aicbase->AIC_EOICR = piobaseB->PIO_ISR;
}


/**
 *	Initializers
 */
void PIO_Init(void) {
   StructPMC* pmcbase = PMC_BASE;

   // enable clocks for PIOA, PIOB, Timer4 and Timer5
   pmcbase->PMC_PCER = 0x06C00;

   StructPIO* piobaseA = PIOA_BASE;
   // disable PIO lanes used by the scale (to prevent PIO taking control of them and disabling timer access)
   piobaseA->PIO_PDR = 0x090;

   StructPIO* piobaseB = PIOB_BASE;

   // enable PIO control of all LEDs and all 3 key pins
   piobaseB->PIO_PER = ALL_LEDS | KEY1 | KEY2 | KEY3;

   // set key pins as input pins by disabling them as output
   piobaseB->PIO_ODR = KEY1 | KEY2 | KEY3;

   // set all led pins as output pins
   piobaseB->PIO_OER = ALL_LEDS;
}

void Timer_Init(void) {
   // initialize timer channel 4 and 5
   // disable them, set the needed flags and reenable them

   StructTC* tcbase4 = TCB4_BASE;
   StructTC* tcbase5 = TCB5_BASE;

   tcbase4->TC_CCR = TC_CLKDIS;
   tcbase4->TC_CMR = TC_INIT;
   tcbase4->TC_CCR = TC_CLKEN;

   tcbase5->TC_CCR = TC_CLKDIS;
   tcbase5->TC_CMR = TC_INIT;
   tcbase5->TC_CCR = TC_CLKEN;
}

void InterruptInit(void) {
   StructAIC* aicbase = AIC_BASE;
   StructPIO* piobaseB = PIOB_BASE;

   aicbase->AIC_IDCR = (1 << PIOB_ID); // Disable all interrupt handling for PIOB
   aicbase->AIC_ICCR = (1 << PIOB_ID); // Clear all pending interrupts from PIOB

   aicbase->AIC_SVR[PIOB_ID] = (unsigned int)taste_irq_handler; // Set the irq-handler for interrupts raised by PIOB
   aicbase->AIC_SMR[PIOB_ID] = AIC_PRIOR; // Set the highest priority for interrupts from PIOB

   aicbase->AIC_IECR = (1 << PIOB_ID); // Enable interrupt handling for PIOB

   piobaseB->PIO_IER = KEY1 | KEY2 | KEY3; // Enables interrupts in PIOB for the first three switches
}

int init_ser() {
   StructPIO* piobaseA = PIOA_BASE;
   StructPMC* pmcbase = PMC_BASE;
   StructUSART* usartbase0 = USART0;

   // enable clock for USART0
   pmcbase->PMC_PCER = 0x4;

   // disable PIO control over pins we use for serial IO
   piobaseA->PIO_PDR = 0x18000;

   // disable transmit and receive while we set things up
   usartbase0->US_CR = 0xa0;

   // set baud rate as configured before
   usartbase0->US_BRGR = US_BAUD;

   // set mode to: no parity, 8 bit per word, MCKI (master clock without any division)
   usartbase0->US_MR = 0x8c0;

   // reenable transmit and receive
   usartbase0->US_CR = 0x50;

   return 0;
}


/**
 *	Algorithm
 */
int MessungderMasse() {
   StructTC* tcbase4 = TCB4_BASE;
   StructTC* tcbase5 = TCB5_BASE;
   int buf;
   buf = tcbase4->TC_SR;
   buf = tcbase5->TC_SR;
   tcbase4->TC_CCR = TC_SWTRG;
   tcbase5->TC_CCR = TC_SWTRG;

   while(!(tcbase4->TC_SR & 0x40))
      ; // Capture Register B wurde geladen Messung abgeschlossen

   int captureRA4 = tcbase4->TC_RA; //
   int captureRB4 = tcbase4->TC_RB;
   int capturediff4 = abs(captureRB4 - captureRA4);

   while(!(tcbase5->TC_SR & 0x40))
      ; // Capture Register B wurde geladen Messung abgeschlossen

   int captureRA7 = tcbase5->TC_RA; //
   int captureRB7 = tcbase5->TC_RB;
   int capturediff7 = abs(captureRB7 - captureRA7);

   return (C1 * (((float)capturediff4 * 1000 / capturediff7) - 1000) - C2 * 1000);
}

int reverseBits(int a) {
   // reverse lowest 8 bits in a byte by shifting each one to its new place and ORing the results together
   return ((a & 0x1) << 7) | ((a & 0x2) << 5) | ((a & 0x4) << 3) | ((a & 0x8) << 1) |
          ((a & 0x10) >> 1) | ((a & 0x20) >> 3) | ((a & 0x40) >> 5) | ((a & 0x80) >> 7);
}

int getIntLength(int value) {
   int length = !value;
   while(value) {
      length++;
      value /= 10;
   }
   return length;
}

void signedIntToString(int value, char* targetString) {
   char* buf = targetString;
   int length = getIntLength(value);
   int isNegative = value < 0;

   // use long to handle edge cases with biggest or smallest signed int
   long longValue = value;

   // if value is negative: put '-' into first char and invert it arithmetically
   if(isNegative) {
      *buf = '-';
      longValue *= (-1);
   } else {
      length--;
   }

   // jump to last needed character space
   buf += length;
   long mod = 10;

   // calculate each character by dividing by ever increasing multiples of 10
   while(mod <= 100000000000) {
      int result = (longValue % mod) / (mod / 10);
      *buf-- = 48 + result;
      if(buf < targetString || (isNegative && buf <= targetString)) {
         return;
      }
      mod *= 10;
   }
}

int main(void) {
   // initialize all needed components of the controller
   init_ser();
   PIO_Init();
   Timer_Init();
   InterruptInit();

   while(1) {
      int tara = 0;
      int brutto = 0;
      int netto = 0;

      putstring("Moin\r\nDruecken sie die Taste 1 um fortzufahren\r\n");


      // wait for interrupt SW1 that starts the tara step
      while(step == 1) {
         // step = 2;
      }

      putstring("Bitte legen sie das Tara-Gewicht auf\r\n");
      putstring("Druecken sie danach die Taste 2 um den Wiegevorgang der Muenzen zu starten\r\n");

      // repeat measurement until SW2 is pressed (which sets step to 3)
      int i = 0;
      long taraMeasures = 0;
      long taraMeasurementsSum = 0;
      while(step == 2) {
         // measure tara
         taraMeasurementsSum += MessungderMasse();

         // average out tara measures
         taraMeasures++;
         tara = taraMeasurementsSum / taraMeasures;
         /* i++;
         if(i == 1000)
            step = 3; */
      };

      putstring("Bitte legen sie ihre Muenzen auf\r\n");
      putstring("Druecken sie danach die Taste 3 um den Wiegevorgang abzuschliessen\r\n");
      tara = 0;
      int k = 0;
      unsigned long bruttoMeasures = 0;
      unsigned long bruttoMeasurementsSum = 0;
      // wait for interrupt SW3 that ends the weighting process
      while(step == 3) {
         // measure again
         bruttoMeasurementsSum += MessungderMasse();

         // average brutto measures
         bruttoMeasures++;
         brutto = bruttoMeasurementsSum / bruttoMeasures;

         netto = brutto - tara;

         // print netto weight
         char nettoString[12] = "";
         signedIntToString(netto, nettoString);
         putstring("Netto: ");
         putstring(nettoString);
         putstring("\r\n");

         // calculate and show number of coins
         int show = netto / muenzgewicht;
         setLEDs(show);
      }

      // output all information to SIO

      char taraString[12] = "";
      signedIntToString(tara, taraString);
      char bruttoString[12] = "";
      signedIntToString(brutto, bruttoString);
      char nettoString[12] = "";
      signedIntToString(netto, nettoString);

      putstring("Tara: ");
      putstring(taraString);
      putstring("\r\nBrutto: ");
      putstring(bruttoString);
      putstring("\r\nNetto: ");
      putstring(nettoString);
      putstring("\r\n");
      putstring("\r\n");
      putstring("\r\n");

      // reset state machine and start again
      step = 1;
   }


   return 0;
}
