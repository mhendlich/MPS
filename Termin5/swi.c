/*----------------------------------------------------------------------------
@ File Name     : swi.c
@ Object        : SoftwareInterruptHandler
@
@ Autor 	: Horsch/Pester/Steiger
@ Datum		: 3.12.2007/Januar2011/April2011
@----------------------------------------------------------------------------*/
void SWIHandler () __attribute__ ((interrupt ("SWI")));

void SWIHandler() 
{
	register char *reg_r0 asm ("r0");
	register unsigned int *reg_14 asm ("r14");

	switch( *(reg_14 - 1) & 0x00FFFFFF) // Ausblenden der oberen 8 Bits 
					    // und Verzweigen in Abh. der SWI-Nummer
	{ 
		case 0x100:
			init_ser();
			break;
		case 0x200:
			*reg_r0 = putch(*reg_r0);
			break;
		case 0x300:
			*reg_r0 = getch();
			break;
	}
}

