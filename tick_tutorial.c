/* Cópia do código do tutorial Multitasking on an AVR */

/* Hardware constants for timer 1 on ATMega323. */
#define portCLEAR_COUNTER_ON_MATCH				( 0x08 )
#define portPRESCALE_256						( 0x04 )
#define portCLOCK_PRESCALER						(  256 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE	( 0x10 )

/*
Setup timer 1 compare match A to generate a tick interrupt.
*/
static void prvSetupTimerInterrupt( void )
{
	unsigned portLONG ulCompareMatch;
	unsigned portCHAR ucHighByte, ucLowByte;
	
	/* Generate the compare match value for our required tick
	 * frequency. */
	ulCompareMatch = portCPU_CLOCK_HZ / portTICK_RATE_HZ;

	/* We only have 16 bits so have to scale to get our
	required tick rate. */
	ulCompareMatch /= portCLOCK_PRESCALER;

	/* Setup compare match value for compare match A.
	 * Interrupts are disabled before calling this function so
	 * we need not bother here. [casting has been removed for
	 * each of reading] */
	ucLowByte = ulCompareMatch & 0xff;
	ulCompareMatch >>= 8;
	ucHighByte = ulCompareMatch & 0xff;
	outb( OCR1AH, ucHighByte );
	outb( OCR1AL, ucLowByte );
	
	/* Setup clock source and compare match behaviour. */
	ucLowByte = portCLEAR_COUNTER_ON_MATCH | portPRESCALE_256;
	outb( TCCR1B, ucLowByte );
	
	/* Enable the interrupt - this is okay as interrupt
	 * are currently globally disabled. */
	ucLowByte = inb( TIMSK );
	ucLowByte |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
	outb( TIMSK, ucLowByte );
}
