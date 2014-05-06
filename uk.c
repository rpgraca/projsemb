#include <avr/io.h>
#include <avr/interrupt.h>

#define	CLOCKTIME	0.001 // Tempo de tick em segundos
#define PRESCALAR	8
#define LED			5

int main(void)
{
	DDRB = (1<<LED);  // Define LED do arduino como saida (PORTB5)
    OCR1A = (unsigned int) ((F_CPU/PRESCALAR)*CLOCKTIME);

    TCCR1B |= (1 << WGM12);  // Mode 4, CTC on OCR1A

    TIMSK1 |= (1 << OCIE1A); //Set interrupt on compare match
	
	// Iniciar timer com prescaler definido devidamente
	switch(PRESCALAR)
	{
		case 1:		TCCR1B |= (1 << CS10);
					break;
		case 8:		TCCR1B |= (1 << CS11);
					break;
		case 16:	TCCR1B |= (1 << CS11) | (1 << CS10);
					break;
		case 256:	TCCR1B |= (1 << CS12);
					break;
		case 1024:	TCCR1B |= (1 << CS12) | (1 << CS10);
					break;
	}


    sei();    // enable interrupts


    while (1);
    {
        // we have a working Timer
    }
}

ISR (TIMER1_COMPA_vect)
{
	static int i=0;
	i++;
	if(i==1000)
	{
		i=0;
		PORTB ^= (1<<LED);
	}
}

