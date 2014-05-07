	.file	"asm.c"
__SP_H__ = 0x3e
__SP_L__ = 0x3d
__SREG__ = 0x3f
__tmp_reg__ = 0
__zero_reg__ = 1
	.text
.global	funcA
	.type	funcA, @function
funcA:
	push r28
	push r29
	rcall .
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 4 */
/* stack size = 6 */
.L__stack_usage = 6
	std Y+4,r25
	std Y+3,r24
	ldi r24,lo8(-48)
	ldi r25,lo8(7)
	std Y+2,r25
	std Y+1,r24
	ldd r18,Y+3
	ldd r19,Y+4
	ldd r24,Y+1
	ldd r25,Y+2
	add r24,r18
	adc r25,r19
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	funcA, .-funcA
.global	main
	.type	main, @function
main:
	push r28
	push r29
	rcall .
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 2 */
/* stack size = 4 */
.L__stack_usage = 4
	ldi r24,lo8(-24)
	ldi r25,lo8(3)
	call funcA
	std Y+2,r25
	std Y+1,r24
/* #APP */
 ;  18 "asm.c" 1
	add r2,r4
	add r4,r5
 ;  0 "" 2
/* #NOAPP */
.L4:
	ldd r24,Y+1
	ldd r25,Y+2
	sbiw r24,0
	brne .L4
	ldi r24,lo8(1)
	ldi r25,0
/* epilogue start */
	pop __tmp_reg__
	pop __tmp_reg__
	pop r29
	pop r28
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.0"
