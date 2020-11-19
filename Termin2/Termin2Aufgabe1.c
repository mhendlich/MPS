// Loesung zu Termin2
// Aufgabe 1
// von:
// vom:
//

#include <stdint.h>

#include "../h/aic.h"
#include "../h/pio.h"
#include "../h/pmc.h"

typedef enum { IO_SW1, IO_SW2, IO_SW3 } IO_Switches;

typedef enum { IO_Off, IO_On } IO_States;

/*
 * Liefert den Status der angegebenen Taste.
 * @param keyNr	Die Taste, dessen Status geprüft werden soll (SW1-SW3)
 * @return	Gibt 1 zurück, wenn die Taste gedrückt wird, ansonsten 0.
 * @example	if ( IsKeydown(IO_SW2) ) { ... }
 */
inline uint8_t IsKeydown(const IO_Switches keyNr) {
   StructPIO* piobaseB = PIOB_BASE;

   static const uint8_t keys[] = { KEY1, KEY2, KEY3 };

   if(keyNr > IO_SW3)
      return 0;

   const uint8_t key = keys[keyNr];

   // Ist die gewünschte Tasten schon unter der Kontrolle der PIO?
   if(!(piobaseB->PIO_PSR & key)) {
      piobaseB->PIO_PER = key;

      // Ist die gewünschte Taste als input konfiguriert?
      if((piobaseB->PIO_OSR & key))
         piobaseB->PIO_ODR = key;
   }

   // Aufgabe: Hier wurde das falsche PIO-Register genutzt!
   // Berichtigen Sie diesen Fehler, damit der Pin-Status ausgelesen wird.
   // Beachten Sie zudem, ob die Tasten high- oder low-active sind!
   if((piobaseB->PIO_PSR & key))
      return 1;

   return 0;
}


/**
 * Setzt den Zustand der LEDs (an/aus).
 * @param leds	Binäre representation der gewünschten LED(s)
 * @param state	Gewünschter Zustand (On/Off)
 * @example	SetLED( (LED2 | LED5), IO_On)
 */
inline void SetLED(uint16_t leds, IO_States state) {
   StructPIO* piobaseB = PIOB_BASE;

   // Sind die gewünschten LEDs schon unter der Kontrolle der PIO?
   if(!(piobaseB->PIO_PSR & leds)) {
      piobaseB->PIO_PER = leds;

      // Sind die gewünschten LEDs als output konfiguriert?
      if(!(piobaseB->PIO_OSR & leds))
         piobaseB->PIO_OER = leds;
   }

   // Aufgabe: Warum gehen die LEDs an, wenn man den Output cleared?
   if(state == IO_On)
      piobaseB->PIO_CODR = leds;
   else
      piobaseB->PIO_SODR = leds;
}

void PeripheryInit(void) {
   StructPMC* pmcbase = PMC_BASE; // Basisadresse des PMC
   StructPIO* piobaseB = PIOB_BASE; // Basisadresse der PIOB

   // Eventuell benötigte Peripheral-Clocks einschalten (durch PMC)
   // ...

   // LEDS initialisieren
   piobaseB->PIO_PER = ALL_LEDS; // Enable PIO for all LEDs
   piobaseB->PIO_OER = ALL_LEDS; // Set data direction (output) for all LEDs

   // Tasten initialisieren
   piobaseB->PIO_PER = KEY1 | KEY2; // Enable PIO for the first two switches
   piobaseB->PIO_ODR = KEY1 | KEY2; // Set data direction (input) for the first two switches
}

int main(void) {
   PeripheryInit();

   while(1) {
      SetLED(ALL_LEDS, IO_On);
      SetLED(ALL_LEDS, IO_Off);
   }

   return 0;
}
