	.arch armv4t
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"Termin4Aufgabe1.c"
	.global	__aeabi_i2d
	.global	__aeabi_ddiv
	.global	__aeabi_d2f
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	@ Function supports interworking.
	@ args = 0, pretend = 0, frame = 48
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	add	fp, sp, #8
	sub	sp, sp, #52
	mov	r3, #-1610612736
	mov	r3, r3, asr #15
	str	r3, [fp, #-28]
	mov	r3, #-1342177280
	mov	r3, r3, asr #14
	str	r3, [fp, #-24]
	mvn	r3, #179200
	sub	r3, r3, #956
	sub	r3, r3, #3
	str	r3, [fp, #-20]
	mvn	r3, #179200
	sub	r3, r3, #892
	sub	r3, r3, #3
	str	r3, [fp, #-16]
	ldr	r3, [fp, #-28]
	mov	r2, #27648
	str	r2, [r3, #16]
	ldr	r3, [fp, #-24]
	mov	r2, #144
	str	r2, [r3, #4]
	ldr	r3, [fp, #-20]
	mov	r2, #2
	str	r2, [r3, #0]
	ldr	r2, [fp, #-20]
	mov	r3, #327680
	add	r3, r3, #64
	str	r3, [r2, #4]
	ldr	r3, [fp, #-20]
	mov	r2, #1
	str	r2, [r3, #0]
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
.L4:
	ldr	r3, [fp, #-20]
	mov	r2, #4
	str	r2, [r3, #0]
	ldr	r3, [fp, #-16]
	mov	r2, #4
	str	r2, [r3, #0]
.L2:
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #32]
	and	r3, r3, #64
	cmp	r3, #0
	beq	.L2
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #20]
	str	r3, [fp, #-32]
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-36]
	ldr	r2, [fp, #-36]
	ldr	r3, [fp, #-32]
	rsb	r3, r3, r2
	str	r3, [fp, #-40]
	ldr	r3, [fp, #-40]
	mov	r0, r3
	bl	__aeabi_i2d
	mov	r3, r0
	mov	r4, r1
	mov	r0, r3
	mov	r1, r4
	mov	r2, #0
	mov	r3, #1073741824
	add	r3, r3, #2686976
	bl	__aeabi_ddiv
	mov	r3, r0
	mov	r4, r1
	mov	r0, r3
	mov	r1, r4
	bl	__aeabi_d2f
	mov	r3, r0
	str	r3, [fp, #-44]	@ float
.L3:
	ldr	r3, [fp, #-16]
	ldr	r3, [r3, #32]
	and	r3, r3, #64
	cmp	r3, #0
	beq	.L3
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #20]
	str	r3, [fp, #-48]
	ldr	r3, [fp, #-20]
	ldr	r3, [r3, #24]
	str	r3, [fp, #-52]
	ldr	r2, [fp, #-52]
	ldr	r3, [fp, #-48]
	rsb	r3, r3, r2
	str	r3, [fp, #-56]
	ldr	r3, [fp, #-56]
	mov	r0, r3
	bl	__aeabi_i2d
	mov	r3, r0
	mov	r4, r1
	mov	r0, r3
	mov	r1, r4
	mov	r2, #0
	mov	r3, #1073741824
	add	r3, r3, #2686976
	bl	__aeabi_ddiv
	mov	r3, r0
	mov	r4, r1
	mov	r0, r3
	mov	r1, r4
	bl	__aeabi_d2f
	mov	r3, r0
	str	r3, [fp, #-60]	@ float
	b	.L4
	.size	main, .-main
	.ident	"GCC: (crosstool-NG-1.11.1-v4t) 4.4.5"
