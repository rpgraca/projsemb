#include <avr/io.h>
#include "ListaTarefas.h"

#define	CLOCKTIME	0.001 // Tempo de tick em segundos
#define PRESCALAR	8
#define LEDA		5
#define LEDB		4

void initA(void);
void initB(void);
void funcA(void); /*__attribute__((naked));*/
void funcB(void); /*__attribute__((naked));*/

Tarefa_t tarefas[4];


int main(void)
{
	/*
	
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
	*/
	tarefas[0]=Tarefa_cria(1,200,funcA); return;
	tarefas[1]=Tarefa_cria(2,400,funcB); return;
	tarefas[2]=Tarefa_cria(3,100,funcA); return;
	tarefas[3]=Tarefa_cria(4,100,funcB); return;
	

    sei();    // enable interrupts
	

    while (1);
    {
        // we have a working Timer
    }
}

ISR (TIMER1_COMPA_vect) 
{

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
