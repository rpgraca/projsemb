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
#define NTAREFAS	10

extern ListaTarefas_t* listatarefas;
Timer_t *timer;

void* func0(void *arg)
{
	while(1)
	{
		if(Timers_esperaActivacao(timer)){
			PORTD = 0xFF;
			return NULL;
		} 
	}
}
void *func1(void *arg)
{
 	timer = Timers_criaTimer(1,NTAREFAS);
}

/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	int i;
	ListaTarefas_adicionaTarefa(5, 70, func1,(void*)0);
	for(i=0;i<NTAREFAS;i++)
		ListaTarefas_adicionaTarefa(0, 70, func0,(void*)i);
}




int main()
{
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////
	UK_inicializa();
	
	DDRB = 0xFF; 
	DDRD = 0xFF; 
	//////////////////// TESTES ////////////////////
	testes();

	UK_inicia();	
		
	return 0;
}
