// Loesung zu Termin2
// Aufgabe 4
// Namen: __________; ___________
// Matr.: __________; ___________
// vom :  __________
//

#include "../h/aic.h"
#include "../h/pio.h"
#include "../h/pmc.h"

void taste_irq_handler(void) __attribute__((interrupt));

void taste_irq_handler(void) {
   StructAIC* aicbase = AIC_BASE;
   StructPIO* piobaseB = PIOB_BASE;

   // ...

   // Aufgabe: Setzen Sie das Register, welches der AIC das Ende des Interrupts meldet, indem
   // Sie den Interrupt-Status der PIO übergeben!
   aicbase->AIC_XXXXXR = piobaseB->PIO_XXR;
}

void InterruptInit(void) {
   StructAIC* aicbase = AIC_BASE;
   StructPIO* piobaseB = PIOB_BASE;

   // Aufgabe: Setzen Sie die richtigen Register ein, indem Sie die Kommentare
   // in den jeweiligen Zeilen als Hinweise nehmen!

   aicbase->AIC_XXXR = (1 << PIOB_ID); // Disable all interrupt handling for PIOB
   aicbase->AIC_XXXR = (1 << PIOB_ID); // Clear all pending interrupts from PIOB

   aicbase->AIC_XXR[PIOB_ID] = (unsigned int)taste_irq_handler; // Set the irq-handler for interrupts raised by PIOB
   aicbase->AIC_XXR[PIOB_ID] = AIC_PRIOR; // Set the highest priority for interrupts from PIOB

   piobaseB->PIO_XXR = KEY1 | KEY2; // Enables interrupts in PIOB for the first two switches
}

int main(void) {
   InterruptInit();


   return 0;
}
