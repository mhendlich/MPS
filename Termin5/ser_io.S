@----------------------------------------------------------------------------
@ File Name           : ser_io.S
@ Object              : Ein- Ausgabe-Funktionen der seriellen Schnittstelle
@			welche ueber den Supervisor-Mode gehen
@			
@
@ Namen :		Matr.-Nr.:
@			Matr.-Nr.:
@
@----------------------------------------------------------------------------

@ Debuginformationen
	.file	"ser_io.S"

@ Funktion
	.text
	.align	2
	.global	inits
	.type	inits,function
inits:
	swi	0x100
	bx	lr	@ Rücksprung

@ Funktion
	.text
	.align	2
	.global	putc
	.type	putc,function
putc:
	mov	r1, r0		@ Zeichen nach r1
	ldr	r0, =Zeichen	@ Zeiger holen
	str	r1, [r0]	@ Zeichen unter Zeiger ablegen
	swi 	0x200		@ 
	ldr	r1, =Zeichen	@ Zeiger holen
	ldr	r0, [r1]	@ Zeichen aus Zeiger holen
	bx 	lr

@ Funktion
	.text
	.align	2
	.global	getc
	.type	getc,function
getc:
	ldr 	r0, =Zeichen	@ Zeiger holen
	swi 	0x300		
	ldr	r0, =Zeichen	@ Zeiger holen		
	ldr 	r0, [r0]	@ empfangenes Zeichen zurueck geben
	bx 	lr
	
@ Funktion
	.text
	.align	2
	.global	puts
	.type	puts,function
puts:
	stmfd sp!,{lr}	@ Retten der Register

// Hier muß Ihr Code eingefügt werden.

	ldmfd sp!,{pc}	@ Rücksprung

@ Funktion
	.text
	.align	2
	.global	gets
	.type	gets,function
gets:
	stmfd	sp!,{lr}	@ Retten der Register
	
// Hier könnte Ihr Code eingefügt werden!

	ldmfd 	sp!,{pc}	@ Rücksprung
	
	.data
Zeichen:	.word 0			

.end
