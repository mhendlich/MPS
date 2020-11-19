// Loesung zur Aufgabe Termin4
// Aufgabe 1
//****************************
// Messen der Periodendauer einer angelegten Frequenz
//
// von: Manfred Pester
// vom: 17. Januar 2020

#include "../h/pio.h"
#include "../h/pmc.h"
#include "../h/tc.h"

// f�r die Initialisierung des Zaehler TC4
#define TC4_INIT TC_CLKS_MCK2 | TC_LDBSTOP | TC_CAPT | TC_LDRA_RISING_EDGE | TC_LDRB_RISING_EDGE


int main(void) {
   volatile int captureRA1;
   volatile int captureRB1;
   volatile int capturediff1;
   volatile float Periodendauer1;

   StructPMC* pmcbase = PMC_BASE;
   StructPIO* piobaseA = PIOA_BASE;
   StructTC* tcbase4 = TCB4_BASE;
   StructTC* tcbase5 = TCB5_BASE;

   pmcbase->PMC_PCER = 0x06400; // Clock fuer PIOA, PIOB und Timer4, einschalten

   // Periodendauer einer der von der Waage gelieferten Frequenz messen
   // Die Waage liefert ca. 16kHz entspricht einer Periodendauer von 62,5us
   // durch den Vorteiler von 32 ergibt sich an TIOA4 eine Periodendauer von ca. 2ms
   // ..

   piobaseA->PIO_PDR = 0x090;
   tcbase4->TC_CCR = TC_CLKDIS;
   tcbase4->TC_CMR = TC4_INIT;
   tcbase4->TC_CCR = TC_CLKEN;
   tcbase4->TC_CCR = TC_SWTRG;

   while(1) {
      tcbase4->TC_CCR = TC_SWTRG;
      while(!(tcbase4->TC_SR & 0x40))
         ; // Capture Register B wurde geladen Messung abgeschlossen
      captureRA1 = tcbase4->TC_RA; //
      captureRB1 = tcbase4->TC_RB;
      capturediff1 = captureRB1 - captureRA1;
      Periodendauer1 = capturediff1 / 12.5; // Zeit in us
   }

   return 0;
}
