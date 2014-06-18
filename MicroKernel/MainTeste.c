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

extern ListaTarefas_t * listatarefas;
void tick() __attribute__((naked,signal));
void tick()
{
	Timers_actualizaTimers();
	Sched_dispatch();
	asm volatile("reti");
}
Timer_t *timer;
void * funcA(void * ptr)
{
	//timer = Timers_criaTimer(3);
	int x = 0;
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
		Timers_esperaActivacao(timer);
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
int * x = (int*) malloc(sizeof(int));
int * z = (int*) malloc(sizeof(int));
	ATmega_idleStackptr();
	listatarefas = ListaTarefas_cria(3);
	ListaTarefas_adicionaTarefa(listatarefas,1,400,funcA);
	ListaTarefas_adicionaTarefa(listatarefas,2,400,funcB);
	ListaTarefas_adicionaTarefa(listatarefas,0,400,funcC);
	listatarefas->prioridades[2]->tarefas[0]->activada = 0;
	timer=Timers_criaTimer(7,2);
	Sched_dispatch();
	
    while(1)
    {

    }
}