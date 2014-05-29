#include <avr/io.h>
#include <avr/interrupt.h>

#define	CLOCKTIME	0.001 // Tempo de tick em segundos
#define PRESCALAR	8
#define LEDA		5
#define LEDB		4

void initA(void);
void initB(void);
void funcA(void); /*__attribute__((naked));*/
void funcB(void); /*__attribute__((naked));*/

int main(void)
{
	DDRB = (1<<LEDA) | (1<<LEDB);  // Define LED do arduino como saida (PORTB5)
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
	static int i=4,k=0;
	i++;
	if(i==5)
	{
		funcA();
		if (k)
		{
			funcB();
		}
		k=!k;
		i=0;
	}
}

void funcA(void)
{
	static int i=0;
	i++;
	if (i==100)
	{
		PORTB ^= (1<<LEDA);
		i=0;
	}
}

void funcB(void)
{
	static int i=99;
	i++;
	if (i==100)
	{
		PORTB ^= (1<<LEDB);
		i=0;
	}
}
