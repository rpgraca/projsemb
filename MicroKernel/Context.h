extern char * stackptrAtual;
extern void * (*funcAtual)(void *);
#define GUARDARCONTEXTO() {	asm volatile(	"push r0		\n\t "\
					"in r0, __SREG__	\n\t "\
					"cli			\n\t "\
					"push r0		\n\t "\
					"push r1		\n\t "\
					"clr r1			\n\t "\
					"push r2		\n\t "\
					"push r3		\n\t "\
					"push r4		\n\t "\
					"push r5		\n\t "\
					"push r6		\n\t "\
					"push r7		\n\t "\
					"push r8		\n\t "\
					"push r9		\n\t "\
					"push r10		\n\t "\
					"push r11		\n\t "\
					"push r12		\n\t "\
					"push r13		\n\t "\
					"push r14		\n\t "\
					"push r15		\n\t "\
					"push r16		\n\t "\
					"push r17		\n\t "\
					"push r18		\n\t "\
					"push r19		\n\t "\
					"push r20		\n\t "\
					"push r21		\n\t "\
					"push r22		\n\t "\
					"push r23		\n\t "\
					"push r24		\n\t "\
					"push r25		\n\t "\
					"push r26		\n\t "\
					"push r27		\n\t "\
					"push r28		\n\t "\
					"push r29		\n\t "\
					"push r30		\n\t "\
					"push r31		\n\t "\
					"in r28, __SP_L__	\n\t "\
					"in r29, __SP_H__	\n\t "\
					"sts stackptrAtual,r28	\n\t "\
					"sts stackptrAtual+1,r29 	\n\t ");}

#define RECUPERARCONTEXTO() { asm volatile("lds R28,stackptrAtual	\n\t	" \
					"lds R29,stackptrAtual+1	\n\t	"\
					"out __SP_L__,R28	\n\t	" \
					"out __SP_H__,R29	\n\t	" \
					"pop R31		\n\t	" \
					"pop R30		\n\t	" \
					"pop R29		\n\t	" \
					"pop R28		\n\t	" \
					"pop R27		\n\t	" \
					"pop R26		\n\t	" \
					"pop R25		\n\t	" \
					"pop R24		\n\t	" \
					"pop R23		\n\t	" \
					"pop R22		\n\t	" \
					"pop R21		\n\t	" \
					"pop R20		\n\t	" \
					"pop R19		\n\t	" \
					"pop R18		\n\t	" \
					"pop R17		\n\t	" \
					"pop R16		\n\t	" \
					"pop R15		\n\t	" \
					"pop R14		\n\t	" \
					"pop R13		\n\t	" \
					"pop R12		\n\t	" \
					"pop R11		\n\t	" \
					"pop R10		\n\t	" \
					"pop R9			\n\t	" \
					"pop R8			\n\t	" \
					"pop R7			\n\t	" \
					"pop R6			\n\t	" \
					"pop R5			\n\t	" \
					"pop R4			\n\t	" \
					"pop R3			\n\t	" \
					"pop R2			\n\t	" \
					"pop R1			\n\t	" \
					"pop R0			\n\t	" \
					"out __SREG__,r0	\n\t	" \
					"pop R0			\n\t	");}
					
#define CRIARCONTEXTOIDLE() { asm volatile("lds R28,stackptrAtual	\n\t	" \
					"lds R29,stackptrAtual+1	\n\t	"\
					"out __SP_L__,R28	\n\t	" \
					"out __SP_H__,R29	\n\t	" \
					"lds R0,funcAtual	\n\t" \
					"push R0		\n\t	" \
					"lds R0,funcAtual+1	\n\t	" \
					"push R0		\n\t	"\
					"clr r0		\n\t");}
	
#define CRIARCONTEXTO() { asm volatile("lds R28,stackptrAtual	\n\t	" \
					"lds R29,stackptrAtual+1	\n\t	"\
					"out __SP_L__,R28	\n\t	" \
					"out __SP_H__,R29	\n\t	" \
					"lds R0,funcAtual	\n\t" \
					"push R0		\n\t	" \
					"lds R0,funcAtual+1	\n\t	" \
					"push R0		\n\t	" \
					"clr R0		\n\t	" \
					"push r0		\n\t "\
					"ldi r16,0x80		\n\t "\
					"push r16	\n\t "\
					"clr r1		\n\t "\
					"push r1			\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"push r28		\n\t "\
					"push r29		\n\t "\
					"push r1		\n\t "\
					"push r1		\n\t "\
					"in r28, __SP_L__	\n\t "\
					"in r29, __SP_H__	\n\t "\
					"sts stackptrAtual,r28	\n\t "\
					"sts stackptrAtual+1,r29 	\n\t ");}
					
#define GUARDARSTACKPTR() {	asm volatile("in r28, __SP_L__	\n\t "\
					"in r29, __SP_H__	\n\t "\
					"sts stackptrAtual,r28	\n\t "\
					"sts stackptrAtual+1,r29 	\n\t ");}

#define RECUPERARSTACKPTR() { asm volatile("lds R28,stackptrAtual	\n\t	" \
					"lds R29,stackptrAtual+1	\n\t	"\
					"out __SP_L__,R28	\n\t	" \
					"out __SP_H__,R29	\n\t	");}