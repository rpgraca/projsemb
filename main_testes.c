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
#include <stdio.h>
#include "uart.h"
#include "MicroKernel/ListaTarefas.h"
#include <avr/io.h>
#include <avr/sleep.h>

#define HEAPSIZE	600
#define NTAREFAS	4

extern ListaTarefas_t* listatarefas;
Sinal_t *sinal;
Timer_t *timer;

void* func0(void *arg)
{
	while(1)
	{
		Timers_esperaActivacao(timer);
	}
}

void *func1(void *arg)
{
	Sinais_esperaSinal(sinal);
}

/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	int i;
	for(i=1;i<NTAREFAS;i++)
		ListaTarefas_adicionaTarefa(i, 50, func1,(void*)0);
	ListaTarefas_adicionaTarefa(0, 60, func0,(void*)0);
}




int main()
{
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////
	UK_inicializa();
	
	DDRB = 0xFF; 
	DDRD = 0xFF; 
	//////////////////// TESTES ////////////////////
	testes();
	sinal=Sinais_criaSinal(NTAREFAS);
	timer=Timers_criaTimer(1,1);
	UK_inicia();	
		
	return 0;
}
