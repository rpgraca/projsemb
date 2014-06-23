/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                           Programa de testes do micro-kernel                          */
/*****************************************************************************************/


#include "MicroKernel/MicroKernel.h"

#include <stdlib.h>
#include <avr/sleep.h>

#define HEAPSIZE	600

void delay_ticks(uint16_t ticks)
{ 
	uint16_t i=0;
       	uint16_t j=0;
       	for(i=0;i<ticks;i++)
	       	for(j=0;j<8335;j++);
}

void *func0(void *arg)
{
       	Timer_t * timer = Timers_criaTimer(200,1);
       	while(1)
       	{
	       	delay_ticks(50);
	       	Timers_esperaActivacao(timer);
       	}
}


void *func1(void *arg)
{
       	Timer_t * timer = Timers_criaTimer(300,1);
       	while(1)
       	{
	       	delay_ticks(50);
	       	Timers_esperaActivacao(timer);
       	}
}

void *func2(void *arg)
{
       	Timer_t * timer = Timers_criaTimer(600,1);
       	while(1)
       	{
	       	delay_ticks(300);
	       	Timers_esperaActivacao(timer);
       	}
}

/**************************************************************/
/* MAIN */
/**************************************************************/

void testes()
{
       	ListaTarefas_adicionaTarefa(2, 100, func0,(void*)5);
       	ListaTarefas_adicionaTarefa(1, 100, func1,(void*)4);
       	ListaTarefas_adicionaTarefa(0, 100, func2,(void*)3);
 }



int main()
{
	
	//PORTB ^= (1<< (int) 2);

	//////////////////// INICIALIZACAO DO KERNEL ////////////////////
	UK_inicializa();
	
	DDRB = 0xFF; 
	DDRD = 0xFF; 

	testes();

	UK_inicia();	
		
	return 0;
}
