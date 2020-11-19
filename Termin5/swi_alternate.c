/*----------------------------------------------------------------------------
@ File Name         : swi.c
@ Object            : SoftwareInterruptHandler
@
@ Autor 			: Horsch/Pester
@ Datum				: 3.12.2007/Januar2011
@----------------------------------------------------------------------------*/
void SWIHandler () __attribute__ ((interrupt ("SWI")));

void SWIHandler() 
{
	register int reg_r0 asm ("r0");		// Register R0
	register int *reg_14 asm ("r14");	// Register PC

	switch( *(reg_14 - 1) & 0x00FFFFFF) // Maskieren der oberen 8 Bits 
																			// und Verzweigen in Abh. der SWI NUmmer
	{ 
		case 0x100:
			init_ser();
			break;
		case 0x200:
			*((char *)reg_r0) = putch(*((char *)reg_r0));	// 
			break;
		case 0x300:
			*((char *)reg_r0) = (unsigned int) getch();
			break;
	}
}

