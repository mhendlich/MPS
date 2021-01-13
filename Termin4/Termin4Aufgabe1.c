// Loesung zur Aufgabe Termin4
// Aufgabe 1
//****************************
// Messen der Periodendauer einer angelegten Frequenz
// 
// von: Manfred Pester
// vom: 17. Januar 2020

#include "../h/pio.h"
#include "../h/tc.h"
#include "../h/pmc.h"

// für die Initialisierung des Zaehler TC4
#define TC_INIT  TC_CLKS_MCK2 | TC_LDBSTOP | TC_CAPT | TC_LDRA_RISING_EDGE | TC_LDRB_RISING_EDGE


int main(void)
{
	volatile int	captureRA4;
	volatile int	captureRB4;
	volatile int	capturediff4;
	volatile float 	Periodendauer4;

	volatile int	captureRA7;
	volatile int	captureRB7;
	volatile int	capturediff7;
	volatile float 	Periodendauer7;
		
	StructPMC* pmcbase = PMC_BASE;
	StructPIO* piobaseA = PIOA_BASE;
	StructTC* tcbase4 = TCB4_BASE;
	StructTC* tcbase5 = TCB5_BASE;
	
	pmcbase->PMC_PCER = 0x06C00;	// Clock fuer PIOA, PIOB, Timer4, Timer5 einschalten
		
// Periodendauer einer der von der Waage gelieferten Frequenz messen
// Die Waage liefert ca. 16kHz entspricht einer Periodendauer von 62,5us
// durch den Vorteiler von 32 ergibt sich an TIOA4 eine Periodendauer von ca. 2ms
// ..

	piobaseA->PIO_PDR	=	0x090;
	tcbase4->TC_CCR		=	TC_CLKDIS;
	tcbase4->TC_CMR		=	TC_INIT;
	tcbase4->TC_CCR		=	TC_CLKEN;
		
	tcbase5->TC_CCR		=	TC_CLKDIS;
	tcbase5->TC_CMR		=	TC_INIT;
	tcbase5->TC_CCR		=	TC_CLKEN;
	
	while(1)
	{
		int buf;
		buf = tcbase4->TC_SR;
		buf = tcbase5->TC_SR;
		tcbase4->TC_CCR	= TC_SWTRG;
		tcbase5->TC_CCR	= TC_SWTRG;
		
		while (!( tcbase4->TC_SR & 0x40));		// Capture Register B wurde geladen Messung abgeschlossen
		
		captureRA4	= tcbase4->TC_RA;
		captureRB4	= tcbase4->TC_RB;
		capturediff4	= captureRB4 - captureRA4;
		Periodendauer4 = capturediff4 / 12.5;		// Zeit in us
			
		while (!( tcbase5->TC_SR & 0x40));		// Capture Register B wurde geladen Messung abgeschlossen
		
		captureRA7	= tcbase4->TC_RA;	
		captureRB7	= tcbase4->TC_RB;
		capturediff7	= captureRB7 - captureRA7;
		Periodendauer7 = capturediff7 / 12.5;		// Zeit in us
	}
	
	return 0;
}
/*
Zu erwarten:
T = 1/500Hz = (1/500)s = 2ms = 2000 us

Maximal Messbar:
2^16/12.5MHz = 65536/12.5 *10^6s = 5242,88 us

Minimal Messbar:
1/12.5MHz = 0,08 us = 80ns
*/
