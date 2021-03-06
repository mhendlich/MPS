// Loesung zu Termin2
// Aufgabe 4
// Namen: __________; ___________
// Matr.: __________; ___________
// vom :  __________
// 

#include <stdint.h>

#include "../h/pmc.h"
#include "../h/pio.h"
#include "../h/aic.h"

typedef enum  
{ 
	IO_SW1, IO_SW2, IO_SW3 
} IO_Switches;

typedef enum
{
	IO_Off, IO_On
} IO_States;

/*
 * Liefert den Status der angegebenen Taste.
 * @param keyNr	Die Taste, dessen Status geprüft werden soll (SW1-SW3)
 * @return	Gibt 1 zurück, wenn die Taste gedrückt wird, ansonsten 0.
 * @example	if ( IsKeydown(IO_SW2) ) { ... }
 */
inline uint8_t IsKeydown(const IO_Switches keyNr)
{
	StructPIO* piobaseB = PIOB_BASE;	
	
	static const uint8_t keys[] = {KEY1, KEY2, KEY3};

	if (keyNr > IO_SW3)
		return 0;

	const uint8_t key = keys[keyNr];

	// Ist die gew�nschte Tasten schon unter der Kontrolle der PIO?
	if (~piobaseB->PIO_PSR & key)
	{
		piobaseB->PIO_PER = key;

		// Ist die gew�nschte Taste als input konfiguriert?
		if (piobaseB->PIO_OSR & key)
			piobaseB->PIO_ODR = key;
	}
	
	// Ist der PIN f�r gew�nschen Key low?
	if ( ( ~piobaseB->PIO_PDSR & key ) )
		return 1;	//true, Taste ist gedr�ckt

	return 0;
}

/**
 * Setzt den Zustand der LEDs (an/aus).
 * @param leds	Binäre representation der gewünschten LED(s)
 * @param state	Gewünschter Zustand (On/Off)
 * @example	SetLED( (LED2 | LED5), IO_On)
 */
inline void SetLED(uint16_t leds, IO_States state)
{
	StructPIO* piobaseB = PIOB_BASE;
	
	// Sind die gewünschten LEDs schon unter der Kontrolle der PIO?
	if (~piobaseB->PIO_PSR & leds)
	{
		piobaseB->PIO_PER = leds;

		// Sind die gewünschten LEDs als output konfiguriert?
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

void taste_irq_handler (void) __attribute__ ((interrupt));

void taste_irq_handler (void)
{
	StructAIC* aicbase = AIC_BASE;		// Basisadresse des AIC
	StructPIO* piobaseB = PIOB_BASE;	// Basisadresse der PIOB
	
	if(IsKeydown(IO_SW1)){
		SetLED(LED1, IO_On);		// LED1 on if key 1 is pressed
	}
	else if (IsKeydown(IO_SW2)){
		SetLED(LED1,IO_Off);		// LED1 on if key 2 is pressed
	}
	
	aicbase->AIC_EOICR = piobaseB->PIO_ISR;	// End of interrupt
}

void InterruptInit(void)
{
	StructAIC* aicbase = AIC_BASE;		// Basisadresse des AIC
	StructPIO* piobaseB = PIOB_BASE;	// Basisadresse der PIOB

	aicbase->AIC_IDCR = (1 << PIOB_ID);	// Disable all interrupt handling for PIOB
	aicbase->AIC_ICCR = (1 << PIOB_ID);	// Clear all pending interrupts from PIOB

	aicbase->AIC_SVR[PIOB_ID] = (unsigned int) taste_irq_handler;	// Set the irq-handler for interrupts raised by PIOB
	aicbase->AIC_SMR[PIOB_ID] = AIC_PRIOR;				// Set the highest priority for interrupts from PIOB

	aicbase->AIC_IECR = 1 << PIOB_ID;	// Enable interrupt handling for PIOB

	piobaseB->PIO_IER = KEY1 | KEY2;	// Enables interrupts in PIOB for the first two switches
}

void PeripheryInit(void)
{
	StructPMC* pmcbase = PMC_BASE;		// Basisadresse des PMC
	StructPIO* piobaseB = PIOB_BASE;	// Basisadresse der PIOB
  	
	pmcbase->PMC_PCER = 0x4000;		// Peripheral Clock f�r PIOB enablen
	
	// LEDS initialisieren
	piobaseB->PIO_PER = ALL_LEDS;		// Enable PIO for all LEDs
	piobaseB->PIO_OER = ALL_LEDS;		// Set data direction (output) for all LEDs

	// Tasten initialisieren
	piobaseB->PIO_PER = KEY1 | KEY2;	// Enable PIO for the first two switches
	piobaseB->PIO_ODR = KEY1 | KEY2;	// Set data direction (input) for the first two switches
}

int main(void)
{
	InterruptInit();
	PeripheryInit();

	StructPIO* piobaseB = PIOB_BASE;	// Basisadresse der PIOB
	StructAIC* aicbase = AIC_BASE;		// Basisadresse des AIC
	
	int count = 0;
  
	while(1)
	{
		count++;

		if(count == 400000){
 			SetLED(LED2, IO_On);
		}
		else if(count == 800000){
			SetLED(LED2, IO_Off);
			count = 0;
		}
	}
	return 0;
}
