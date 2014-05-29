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
	ldi r18,lo8(48)
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
 ;  37 "uk.c" 1
	sei
 ;  0 "" 2
/* #NOAPP */
.L2:
	rjmp .L2
	.size	main, .-main
.global	__vector_11
	.type	__vector_11, @function
__vector_11:
	push r1
	push r0
	lds r0,95
	push r0
	clr __zero_reg__
	push r18
	push r19
	push r20
	push r21
	push r22
	push r23
	push r24
	push r25
	push r26
	push r27
	push r30
	push r31
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: Signal */
/* frame size = 0 */
/* stack size = 17 */
.L__stack_usage = 17
	lds r24,i.1532
	lds r25,i.1532+1
	adiw r24,1
	sts i.1532+1,r25
	sts i.1532,r24
	lds r24,i.1532
	lds r25,i.1532+1
	cpi r24,5
	cpc r25,__zero_reg__
	brne .L3
	call funcA
	lds r24,k.1533
	lds r25,k.1533+1
	sbiw r24,0
	breq .L5
	call funcB
.L5:
	lds r24,k.1533
	lds r25,k.1533+1
	ldi r18,lo8(1)
	sbiw r24,0
	breq .L6
	ldi r18,0
.L6:
	mov r24,r18
	ldi r25,0
	sts k.1533+1,r25
	sts k.1533,r24
	sts i.1532+1,__zero_reg__
	sts i.1532,__zero_reg__
.L3:
/* epilogue start */
	pop r29
	pop r28
	pop r31
	pop r30
	pop r27
	pop r26
	pop r25
	pop r24
	pop r23
	pop r22
	pop r21
	pop r20
	pop r19
	pop r18
	pop r0
	sts 95,r0
	pop r0
	pop r1
	reti
	.size	__vector_11, .-__vector_11
.global	funcA
	.type	funcA, @function
funcA:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	lds r24,i.1537
	lds r25,i.1537+1
	adiw r24,1
	sts i.1537+1,r25
	sts i.1537,r24
	lds r24,i.1537
	lds r25,i.1537+1
	cpi r24,100
	cpc r25,__zero_reg__
	brne .L7
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
	sts i.1537+1,__zero_reg__
	sts i.1537,__zero_reg__
.L7:
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	funcA, .-funcA
.global	funcB
	.type	funcB, @function
funcB:
	push r28
	push r29
	in r28,__SP_L__
	in r29,__SP_H__
/* prologue: function */
/* frame size = 0 */
/* stack size = 2 */
.L__stack_usage = 2
	lds r24,i.1541
	lds r25,i.1541+1
	adiw r24,1
	sts i.1541+1,r25
	sts i.1541,r24
	lds r24,i.1541
	lds r25,i.1541+1
	cpi r24,100
	cpc r25,__zero_reg__
	brne .L9
	ldi r24,lo8(37)
	ldi r25,0
	ldi r18,lo8(37)
	ldi r19,0
	movw r30,r18
	ld r19,Z
	ldi r18,lo8(16)
	eor r18,r19
	movw r30,r24
	st Z,r18
	sts i.1541+1,__zero_reg__
	sts i.1541,__zero_reg__
.L9:
/* epilogue start */
	pop r29
	pop r28
	ret
	.size	funcB, .-funcB
	.local	i.1532
	.comm	i.1532,2,1
	.local	k.1533
	.comm	k.1533,2,1
	.local	i.1537
	.comm	i.1537,2,1
	.data
	.type	i.1541, @object
	.size	i.1541, 2
i.1541:
	.word	99
	.ident	"GCC: (GNU) 4.9.0"
.global __do_copy_data
.global __do_clear_bss
