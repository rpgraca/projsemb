/*
 * GccApplication2.c
 *
 * Created: 11-06-2014 00:30:50
 *  Author: Rui Graça
 */ 
#include "Scheduler_Fixo.h"
#include "ATmega.h"
#include "ListaTarefas.h"
#include "Timers.h"
#include <avr/io.h>
#include <stdlib.h>
#include "Sinais.h"
#include <avr/interrupt.h>

#define HEAPSIZE 400
extern ListaTarefas_t * listatarefas;
void tick() __attribute__((naked,signal));
void tick()
{
	Timers_actualizaTimers();
	Sched_dispatch();
	asm volatile("reti");
}
Timer_t *timer;
Sinal_t *sinal;
void * funcA(void * ptr)
{
	//timer = Timers_criaTimer(3);
	int x = 0;
	timer=Timers_criaTimer(7,2);
	sinal=Sinais_criaSinal(1);
	while(1)
	{
		x++;
		if(x==8)
		{
			listatarefas->prioridades[2]->tarefas[0]->activada = 1;
			tick();
		}
		else if(x==12)
		{
			Timers_esperaActivacao(timer);
			tick();
		}
		if(x==50)
		{
			Sinais_sinaliza(sinal);
		}
		tick();
	}
	return 0x00;

}

void * funcB(void * ptr)
{
	int x=0;
	while(1)
	{
		x++;
		if(x==4)
		{
			Timers_sleep(7);
		}
		else if(x==5)
		{
			Sinais_esperaSinal(sinal);
		}
		else
		{
			Timers_esperaActivacao(timer);	
		}
	}
	return 0x00;
}
void * funcC(void* ptr)
{
	while(1)
	{
		tick();
	}
}
void funcX(void) __attribute__((signal));
void funcX(void)
{
	int x=2;
	return;
}


int main(void)

{
//	funcX();
	char * tmpheap = (char*) malloc(HEAPSIZE);
	ATmega_idleStackptr();
	Sched_inicia();
	Sched_adicionaTarefa(1,400,funcA);
	Sched_adicionaTarefa(2,400,funcB);
	Sched_adicionaTarefa(0,400,funcC);
	listatarefas->prioridades[2]->tarefas[0]->activada = 0;
	free(tmpheap);
	Sched_dispatch();
	
    while(1)
    {

    }
}