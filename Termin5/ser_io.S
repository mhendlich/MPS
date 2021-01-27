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
	bx	lr	@ R�cksprung

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
	ldr	r1, =Zeichen	@ Zeiger holen @ holt gecachedes zeichen nochmals (falls putch 0 zurück gegeben hat)
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
	
	mov r2, #0 // link flag help this is bad code
	mov r1, r0

outer_loop:
	ldr r0, [r1]
	cmp r0, #0
	beq end_outer_loop

	cmp r0, #0x5c // \
	bne write

	ldr r0, [r1, #1]
	cmp r0, #0x6e // n
	ldrne r0, [r1]
	bne write

	mov r0, #0xd
	mov r2, #1 // link flag
	bl write

	mov r0, #0xa
	bl write
	mov r2, #1 // link flag

	add r1, r1, #2
	b outer_loop

write:
	push {r1}
	bl putc	
	pop {r1}
	 
	cmp r0, #0
	beq write

	cmp r2, #1
	mov r2, #0
	bxeq lr
	
	add r1, #1
	b 	outer_loop

end_outer_loop:
	ldmfd sp!,{pc}	@ R�cksprung

@ Funktion
	.text
	.align	2
	.global	gets
	.type	gets,function
gets:
	stmfd	sp!,{lr}	@ Retten der Register
	
// Hier k�nnte Ihr Code eingef�gt werden!

	ldmfd 	sp!,{pc}	@ R�cksprung
	
	.data
Zeichen:	.word 0			

.end
