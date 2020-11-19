// Programmrahmen zur Aufgabe Termin5
// Aufgabe 1
//************************************
// 
// von: Manfred Pester
// vom: 06. August 2003
// letzte Änderung:	30. November 2004
// von: Manfred Pester

int main(void)
{
	char i;
// Serielle initialisieren  
	inits();
	init_ser();
// CR und LF auf das Terminal ausgeben
	putc (0xd);
	putc (0xa);
// ein Zeichen von der seriellen abholen	
	i=getc();
	putc(i);
// String ausgeben
	puts("Hallo! \n");
	
	return 0;
}
