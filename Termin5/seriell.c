/*----------------------------------------------------------------------------
@ File Name         : seriell.c
@ Object            : Grundfunktionen der seriellen Schnittstelle
@	int init_ser(); char putch(char); char getch();
@
@ Autor 			: M.Pester
@ Datum				: 04.12.2007
@
@----------------------------------------------------------------------------*/

#include "../h/pio.h"
#include "../h/pmc.h"
#include "../h/usart.h"

int init_ser(void);
char putch(char);
char getch(void);
void putstring(char*)

#define DEFAULT_BAUD 38400
#define CLOCK_SPEED 25000000
// US_BAUD =  (CLOCK_SPEED / (16*(DEFAULT_BAUD))	// 25MHz / ( 16 * 38400) = 40.69  -> 41 -> 0x29
#define US_BAUD 0x29

// Initialisiert die serielle Schnittstelle USART0

int init_ser() {
   StructPIO* piobaseA = PIOA_BASE;
   StructPMC* pmcbase = PMC_BASE;
   StructUSART* usartbase0 = USART0;

   pmcbase->PMC_PCER = 0x4; // Clock f�r US0 einschalten
   piobaseA->PIO_PDR = 0x18000; // US0 TxD und RxD
   usartbase0->US_CR = 0xa0; // TxD und RxD disable
   usartbase0->US_BRGR = US_BAUD; // Baud Rate Generator Register
   usartbase0->US_MR = 0x8c0; // Keine Parit�t, 8 Bit, MCKI
   usartbase0->US_CR = 0x50; // TxD und RxD enable

   return 0;
}

// Gibt wenn m�glich ein Zeichen auf die serielle Schnittstelle aus
// und liefert das Zeichen wieder zur�ck
// wenn eine Ausgabe nicht m�glich war wird eine 0 zur�ck geliefert

char putch(char Zeichen) {
   StructUSART* usartbase0 = USART0;

   if(usartbase0->US_CSR & US_TXRDY) {
      usartbase0->US_THR = Zeichen;
   } else {
      Zeichen = 0; // wenn keine Ausgabe
   }
   return Zeichen;
}

// Gibt entweder ein empfangenes Zeichen oder eine 0 zur�ck
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

//
void putstring(char*) {
   int i = 0;

   while(char[i] != 0) {
      while(!(putch(char[i])))
         ;
      i = i + 1;
   }
}
