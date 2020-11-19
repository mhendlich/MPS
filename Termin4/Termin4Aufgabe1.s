	.file	"Termin4Aufgabe1.c"
	.global	__floatsidf
	.global	__divdf3
	.global	__truncdfsf2
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 32
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #32
	mov	r3, #-1610612736
	mov	r3, r3, asr #15
	str	r3, [fp, #-24]
	mov	r3, #-1342177280
	mov	r3, r3, asr #14
	str	r3, [fp, #-20]
	mvn	r3, #179200
	sub	r3, r3, #956
	sub	r3, r3, #3
	str	r3, [fp, #-16]
	mvn	r3, #179200
	sub	r3, r3, #892
	sub	r3, r3, #3
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-24]
	mov	r2, #25600
	str	r2, [r3, #16]
	ldr	r3, [fp, #-20]
	mov	r2, #144
	str	r2, [r3, #4]
	ldr	r3, [fp, #-16]
	mov	r2, #2
	str	r2, [r3, #0]
	ldr	r2, [fp, #-16]
	mov	r3, #327680
	add	r3, r3, #64
	str	r3, [r2, #4]
	ldr	r3, [fp, #-16]
	mov	r2, #1
	str	r2, [r3, #0]
	ldr	r3, [fp, #-16]
	mov	r2, #4
	str	r2, [r3, #0]
.L3:
	ldr	r3, [fp, #-16]
	mov	r2, #4
	str	r2, [r3, #0]
.L2:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #32]
	and	r3, r3, #64
	cmp	r3, #0
	beq	.L2
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #20]
	str	r3, [fp, #-28]
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-32]
	ldr	r2, [fp, #-32]
	ldr	r3, [fp, #-28]
	rsb	r3, r3, r2
	str	r3, [fp, #-36]
	ldr	r3, [fp, #-36]
	mov	r0, r3
	bl	__floatsidf
	mov	r3, r0
	mov	r4, r1
	mov	r0, r3
	mov	r1, r4
	mov	r2, #1073741824
	add	r2, r2, #2686976
	mov	r3, #0
	bl	__divdf3
	mov	r3, r0
	mov	r4, r1
	mov	r0, r3
	mov	r1, r4
	bl	__truncdfsf2
	mov	r3, r0
	str	r3, [fp, #-40]	@ float
	b	.L3
	.size	main, .-main
	.ident	"GCC: (crosstool-NG 1.14.1) 4.4.6"
