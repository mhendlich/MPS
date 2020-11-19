// Loesung zu Termin1
// Aufgabe 5
// Namen: ___________; ____________
// Matr.: ___________; ____________
// vom:   ___________

// Beispiel des Anlegens und der Nutzung einer Zeigervariablen
#define PIOB_PER ((unsigned int *) 0xFFFF0000)

// Global angelegte Variable mit der Adresse fuer PIOB_CODR
unsigned int adr_PIOB_CODR = 0xFFFF0034;
  
int main (void)
{
// Variable mit der Adresse fuer PIOB_OER
  unsigned int adr_PIOB_OER = 0xFFFF0010;
  
// PIOB_PER = 0x100  
  *PIOB_PER = 0x100;
// PIOB_OER = 0x100;  
  *((unsigned int *) adr_PIOB_OER) = 0x100;
  while (1)
  {
// PIOB_SODR = 0x100;  
  *((unsigned int *) 0xffff0030) = 0x100;
// PIOB_CODR = 0x100;  
  *((unsigned int *) adr_PIOB_CODR) = 0x100;
  }

  return (0);
}
