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


void PIO_Init(void)
{

}

void Timer_Init(void)
{

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
