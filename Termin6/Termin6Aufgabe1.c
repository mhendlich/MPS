#include "../h/pio.h"
#include "../h/tc.h"
#include "../h/pmc.h"
#include "../h/aic.h"

const static int C1 = 2000;
const static int C2 = 0;

#define TC_INIT  TC_CLKS_MCK2 | TC_LDBSTOP | TC_CAPT | TC_LDRA_RISING_EDGE | TC_LDRB_RISING_EDGE

typedef enum  
{ 
	IO_SW1, IO_SW2, IO_SW3 
} IO_Switches;

typedef enum
{
	IO_Off, IO_On
} IO_States;



/**
*	Hardware
*/
inline uint8_t IsKeydown(const IO_Switches keyNr)
{
	StructPIO* piobaseB = PIOB_BASE;	
	
	static const uint8_t keys[] = {KEY1, KEY2, KEY3};

	if (keyNr > IO_SW3)
		return 0;

	const uint8_t key = keys[keyNr];

	// Ist die gewünschte Tasten schon unter der Kontrolle der PIO?
	if (~piobaseB->PIO_PSR & key)
	{
		piobaseB->PIO_PER = key;

		// Ist die gewünschte Taste als input konfiguriert?
		if (piobaseB->PIO_OSR & key)
			piobaseB->PIO_ODR = key;
	}
	
	// Ist der PIN für gewünschen Key low?
	if ( ( ~piobaseB->PIO_PDSR & key ) )
		return 1;	//true, Taste ist gedrückt

	return 0;
}

inline void SetLED(uint16_t leds, IO_States state)
{
	StructPIO* piobaseB = PIOB_BASE;
	
	// Sind die gewÃ¼nschten LEDs schon unter der Kontrolle der PIO?
	if (~piobaseB->PIO_PSR & leds)
	{
		piobaseB->PIO_PER = leds;

		// Sind die gewÃ¼nschten LEDs als output konfiguriert?
		if (~piobaseB->PIO_OSR & leds)
			piobaseB->PIO_OER = leds;
	}

	if (state == IO_On){
		piobaseB->PIO_CODR = leds; 	// Output clearen -> an, low active
		}
	else{
		piobaseB->PIO_SODR = leds;	// Output setzen -> aus, low active
		}
	
}



/**
*	Interrupt
*/
void taste_irq_handler (void) __attribute__ ((interrupt));

void taste_irq_handler (void)
{
  	StructPIO* piobaseB = PIOB_BASE;		// Basisadresse PIO B
  	StructAIC* aicbase  = AIC_BASE;			// Basisadresse des Advanced Interrupt Controller
	
	if(IsKeydown(IO_SW1)){
		//tara
	}
	else if (IsKeydown(IO_SW2)){
		//start wiegen
	}
	else if (IsKeydown(IO_SW3)){
		//ende wiegen
	}
	
	aicbase->AIC_EOICR = piobaseB->PIO_ISR;	// End of Interrupt
}



/**
*	Initializers
*/
void PIO_Init(void)
{
	StructPMC* pmcbase = PMC_BASE;
	pmcbase->PMC_PCER = 0x06C00;	// Clock fuer PIOA, PIOB, Timer4, Timer5 einschalten

	StructPIO* piobaseA = PIOA_BASE;//Capture Lanes für Waage
	piobaseA->PIO_PDR   = 0x090;
	
	StructPIO* piobaseB = PIOB_BASE;//LEDS&KEYS
	piobaseB->PIO_PER   = ALL_LEDS | KEY1 | KEY2 | KEY3;
		
	piobaseB->PIO_ODR = KEY1 | KEY2 | KEY3;
	piobaseB->PIO_OER = ALL_LEDS;
}

void Timer_Init(void)
{
	StructTC* tcbase4 = TCB4_BASE;
	StructTC* tcbase5 = TCB5_BASE;

	tcbase4->TC_CCR		=	TC_CLKDIS;
	tcbase4->TC_CMR		=	TC_INIT;
	tcbase4->TC_CCR		=	TC_CLKEN;
		
	tcbase5->TC_CCR		=	TC_CLKDIS;
	tcbase5->TC_CMR		=	TC_INIT;
	tcbase5->TC_CCR		=	TC_CLKEN;
}

void InterruptInit(void)
{
	StructAIC* aicbase = AIC_BASE;
	StructPIO* piobaseB = PIOB_BASE;

	aicbase->AIC_IDCR = (1 << PIOB_ID);	// Disable all interrupt handling for PIOB
	aicbase->AIC_ICCR = (1 << PIOB_ID);	// Clear all pending interrupts from PIOB

	aicbase->AIC_SVR[PIOB_ID] = (unsigned int) taste_irq_handler;	// Set the irq-handler for interrupts raised by PIOB
	aicbase->AIC_SMR[PIOB_ID] = AIC_PRIOR;				// Set the highest priority for interrupts from PIOB

	aicbase->AIC_IECR = (1 << PIOB_ID);	// Enable interrupt handling for PIOB

	piobaseB->PIO_IER = KEY1 | KEY2 | KEY3;	// Enables interrupts in PIOB for the first three switches
}



/**
*	Algorithm
*/
int MessungderMasse(){
	StructTC* tcbase4 = TCB4_BASE;
	StructTC* tcbase5 = TCB5_BASE;
	int buf;
	buf = tcbase4->TC_SR;
	buf = tcbase5->TC_SR;
	tcbase4->TC_CCR = TC_SWTRG;
	tcbase5->TC_CCR = TC_SWTRG;
	
	while (!( tcbase4->TC_SR & 0x40));		// Capture Register B wurde geladen Messung abgeschlossen
	
	int captureRA4		= tcbase4->TC_RA;	// 	
	int captureRB4		= tcbase4->TC_RB;
	int capturediff4	= abs(captureRB4 - captureRA4);
			
	while (!( tcbase5->TC_SR & 0x40));		// Capture Register B wurde geladen Messung abgeschlossen
		
	int captureRA7		= tcbase4->TC_RA;	// 	
	int captureRB7		= tcbase4->TC_RB;
	int capturediff7	= abs(captureRB7 - captureRA7);
	
	return (C1 * (((float)capturediff4 / capturediff7)-1)-C2);
}

void NumberToLEDS {
	//convert int to corresponding LEDS in binary
}

int main(void){
return 0;
}
