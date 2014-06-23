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

Semaforo_t *sem1;
Semaforo_t *sem2;
Semaforo_t *sem3;
void delay_ticks(uint16_t ticks)
{ 
	uint16_t i=0;
       	uint16_t j=0;
       	for(i=0;i<ticks;i++)
	       	for(j=0;j<8335;j++);
}

void *func0(void *arg)
{
	Timers_sleep(500);
       	Timer_t * timer = Timers_criaTimer(2500,1);
       	while(1)
       	{
	       	delay_ticks(300);
		Semaforo_lock(sem3);
		PORTB|=1<<3;
	       	delay_ticks(100);
		PORTB&=~(1<<3);
		Semaforo_unlock(sem3);
	       	delay_ticks(100);
		Semaforo_lock(sem2);
		PORTB|=1<<2;
		delay_ticks(100);
		PORTB&=~(1<<2);
		Semaforo_unlock(sem2);
		delay_ticks(100);
	       	Timers_esperaActivacao(timer);
       	}
}


void *func1(void *arg)
{
	Timers_sleep(200);
       	Timer_t * timer = Timers_criaTimer(2500,1);
       	while(1)
       	{
	       	delay_ticks(200);
		Semaforo_lock(sem1);
		PORTB|=1<<1;
	       	delay_ticks(200);
		PORTB&=~(1<<1);
		Semaforo_unlock(sem1);
	       	delay_ticks(200);
	       	Timers_esperaActivacao(timer);
       	}
}

void *func2(void *arg)
{
       	Timer_t * timer = Timers_criaTimer(2500,1);
       	while(1)
       	{
	       	delay_ticks(100);
		Semaforo_lock(sem1);
		PORTB|=1<<1;
	       	delay_ticks(300);
		Semaforo_lock(sem2);
		PORTB|=1<<2;
	       	delay_ticks(300);
		PORTB&=~(1<<2);
		Semaforo_unlock(sem2);
	       	delay_ticks(200);
		PORTB&=~(1<<1);
		Semaforo_unlock(sem1);
	       	delay_ticks(100);
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

	Semaforo_init(&sem1,1);
	Semaforo_init(&sem2,2);
	Semaforo_init(&sem3,2);
	testes();

	UK_inicia();	
		
	return 0;
}
