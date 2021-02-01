#include "../h/aic.h"
#include "../h/pio.h"
#include "../h/pmc.h"
#include "../h/tc.h"
#include "../h/usart.h"

#include <stdint.h>

const static int C1 = 2000;
const static int C2 = 0;

#define DEFAULT_BAUD 38400
#define CLOCK_SPEED 25000000
// US_BAUD =  (CLOCK_SPEED / (16*(DEFAULT_BAUD))	// 25MHz / ( 16 * 38400) = 40.69  -> 41 -> 0x29
#define US_BAUD 0x29

#define TC_INIT TC_CLKS_MCK2 | TC_LDBSTOP | TC_CAPT | TC_LDRA_RISING_EDGE | TC_LDRB_RISING_EDGE

typedef enum { IO_SW1, IO_SW2, IO_SW3 } IO_Switches;

typedef enum { IO_Off, IO_On } IO_States;

int tara, delta, total;


/**
 *	Hardware
 */
inline uint8_t IsKeydown(const IO_Switches keyNr) {
   StructPIO* piobaseB = PIOB_BASE;

   static const uint8_t keys[] = { KEY1, KEY2, KEY3 };

   if(keyNr > IO_SW3)
      return 0;

   const uint8_t key = keys[keyNr];

   // Ist die gew�nschte Tasten schon unter der Kontrolle der PIO?
   if(~piobaseB->PIO_PSR & key) {
      piobaseB->PIO_PER = key;

      // Ist die gew�nschte Taste als input konfiguriert?
      if(piobaseB->PIO_OSR & key)
         piobaseB->PIO_ODR = key;
   }

   // Ist der PIN f�r gew�nschen Key low?
   if((~piobaseB->PIO_PDSR & key))
      return 1; // true, Taste ist gedr�ckt

   return 0;
}

inline void SetLED(uint16_t leds, IO_States state) {
   StructPIO* piobaseB = PIOB_BASE;

   // Sind die gewünschten LEDs schon unter der Kontrolle der PIO?
   if(~piobaseB->PIO_PSR & leds) {
      piobaseB->PIO_PER = leds;

      // Sind die gewünschten LEDs als output konfiguriert?
      if(~piobaseB->PIO_OSR & leds)
         piobaseB->PIO_OER = leds;
   }

   if(state == IO_On) {
      piobaseB->PIO_CODR = leds; // Output clearen -> an, low active
   } else {
      piobaseB->PIO_SODR = leds; // Output setzen -> aus, low active
   }
}

char putch(char Zeichen) {
   StructUSART* usartbase0 = USART0;

   if(usartbase0->US_CSR & US_TXRDY) {
      usartbase0->US_THR = Zeichen;
   } else {
      Zeichen = 0; // wenn keine Ausgabe
   }
   return Zeichen;
}

char getch(void) {
   StructUSART* usartbase0 = USART0;
   char Zeichen;

   if(usartbase0->US_CSR & US_RXRDY) {
      Zeichen = usartbase0->US_RHR;
   } else {
      Zeichen = 0;
   }

   return Zeichen;
}

void putstring(char* String) {
   int i = 0;

   while(String[i] != 0) {
      while(!(putch(String[i]))) {
      }
      i = i + 1;
   }
}


/**
 *	Interrupt
 */
void taste_irq_handler(void) __attribute__((interrupt));

void taste_irq_handler(void) {
   StructPIO* piobaseB = PIOB_BASE; // Basisadresse PIO B
   StructAIC* aicbase = AIC_BASE; // Basisadresse des Advanced Interrupt Controller

   if(IsKeydown(IO_SW1)) {
      // tara
   } else if(IsKeydown(IO_SW2)) {
      // start wiegen
   } else if(IsKeydown(IO_SW3)) {
      // ende wiegen
   }

   aicbase->AIC_EOICR = piobaseB->PIO_ISR; // End of Interrupt
}


/**
 *	Initializers
 */
void PIO_Init(void) {
   StructPMC* pmcbase = PMC_BASE;
   pmcbase->PMC_PCER = 0x06C00; // Clock fuer PIOA, PIOB, Timer4, Timer5 einschalten

   StructPIO* piobaseA = PIOA_BASE; // Capture Lanes f�r Waage
   piobaseA->PIO_PDR = 0x090;

   StructPIO* piobaseB = PIOB_BASE; // LEDS&KEYS
   piobaseB->PIO_PER = ALL_LEDS | KEY1 | KEY2 | KEY3;

   piobaseB->PIO_ODR = KEY1 | KEY2 | KEY3;
   piobaseB->PIO_OER = ALL_LEDS;
}

void Timer_Init(void) {
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

   pmcbase->PMC_PCER = 0x4; // Clock f�r US0 einschalten
   piobaseA->PIO_PDR = 0x18000; // US0 TxD und RxD
   usartbase0->US_CR = 0xa0; // TxD und RxD disable
   usartbase0->US_BRGR = US_BAUD; // Baud Rate Generator Register 38,1khz???
   usartbase0->US_MR = 0x8c0; // Keine Parit�t, 8 Bit, MCKI
   usartbase0->US_CR = 0x50; // TxD und RxD enable

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

   int captureRA7 = tcbase4->TC_RA; //
   int captureRB7 = tcbase4->TC_RB;
   int capturediff7 = abs(captureRB7 - captureRA7);

   return (C1 * (((float)capturediff4 / capturediff7) - 1) - C2);
}

void NumberToLEDS() {
   return; // convert int to corresponding LEDS in binary
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

   long longValue = value;

   if(isNegative) {
      *buf = '-';
      longValue *= (-1);
   } else {
      length--;
   }

   buf += length;
   long mod = 10;

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
   init_ser();
   PIO_Init();
   Timer_Init();
   InterruptInit();

   char* taraString;
   signedIntToString(tara, taraString);

   char* deltaString;
   signedIntToString(delta, deltaString);

   char* totalString;
   signedIntToString(total, totalString);

   putstring("Hallo\nTara:");
   putstring(taraString);
   putstring("\nDelta");
   putstring(deltaString);
   putstring("\nTotal");
   putstring(totalString);

   while(1)
      ;
   return 0;
}
