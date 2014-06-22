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

#define HEAPSIZE	800
#define NTAREFAS	10

extern ListaTarefas_t* listatarefas;
Sinal_t *sinal;
Sinal_t *sinal1;
Timer_t *timer;

void* func2(void *arg)
{
	return NULL;
}

void* func0(void *arg)
{
	while(1)
	{
		if(ListaTarefas_adicionaTarefa(1, 60, func2,(void*)0)== -1) PORTD=0xFF;
		Timers_sleep(3);
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
		ListaTarefas_adicionaTarefa(1, 50, func1,(void*)0);
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
	UK_inicia();	
		
	return 0;
}
