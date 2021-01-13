// Loesung zur Aufgabe Termin4
// Aufgabe 4
//****************************
// Messen der aufgelegten Masse
// 
// von: Manfred Pester
// vom: 06. August 2003

#include "../h/pio.h"
#include "../h/tc.h"
#include "../h/pmc.h"

const static int C1 = 2000;
const static int C2 = 0;

#define TC_INIT  TC_CLKS_MCK2 | TC_LDBSTOP | TC_CAPT | TC_LDRA_RISING_EDGE | TC_LDRB_RISING_EDGE


void PIO_Init(void)
{
	StructPMC* pmcbase = PMC_BASE;
	pmcbase->PMC_PCER = 0x06C00;	// Clock fuer PIOA, PIOB, Timer4, Timer5 einschalten

	StructPIO* piobaseA = PIOA_BASE;
	piobaseA->PIO_PDR	=	0x090;
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

int main(void)
{

	volatile int Masse;
	
	PIO_Init();	
	Timer_Init();
	
	while(1)
	{
		Masse = MessungderMasse();
	}
	
	return 0;
}
