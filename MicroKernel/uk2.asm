	.file	"uk.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	main
	.type	main, @function
main:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	ldi r24,lo8(36)
	ldi r25,0
	ldi r18,lo8(32)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-120)
	ldi r25,0
	ldi r18,lo8(-48)
	ldi r19,lo8(7)
	movw r30,r24
	std Z+1,r19
	st Z,r18
	ldi r24,lo8(-127)
	ldi r25,0
	ldi r18,lo8(-127)
	ldi r19,0
	movw r30,r18
	ld r18,Z
	ori r18,lo8(8)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(111)
	ldi r25,0
	ldi r18,lo8(111)
	ldi r19,0
	movw r30,r18
	ld r18,Z
	ori r18,lo8(2)
	movw r30,r24
	st Z,r18
	ldi r24,lo8(-127)
	ldi r25,0
	ldi r18,lo8(-127)
	ldi r19,0
	movw r30,r18
	ld r18,Z
	ori r18,lo8(2)
	movw r30,r24
	st Z,r18
	nop
/* #APP */
 ;  33 "uk.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L2:
	rjmp .L2
	.size	main, .-main
.global	__vector_11
	.type	__vector_11, @function
__vector_11:
/* prologue: naked */
/* frame size = 0 */
/* stack size = 0 */
.L__stack_usage = 0
	lds r24,i.1528
	lds r25,i.1528+1
	adiw r24,1
	sts i.1528+1,r25
	sts i.1528,r24
	lds r24,i.1528
	lds r25,i.1528+1
	cpi r24,-24
	ldi r18,3
	cpc r25,r18
	brne .L4
	sts i.1528+1,__zero_reg__
	sts i.1528,__zero_reg__
	ldi r24,lo8(37)
	ldi r25,0
	ldi r18,lo8(37)
	ldi r19,0
	movw r30,r18
	ld r19,Z
	ldi r18,lo8(32)
	eor r18,r19
	movw r30,r24
	st Z,r18
.L4:
/* #APP */
 ;  51 "uk.c" 1
	reti
 ;  0 "" 2
/* epilogue start */
/* #NOAPP */
	.size	__vector_11, .-__vector_11
	.local	i.1528
	.comm	i.1528,2,1
	.ident	"GCC: (GNU) 4.9.0"
.global __do_clear_bss
