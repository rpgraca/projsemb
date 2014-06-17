/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                            Escalonador (prioridades fixas)                            */
/*****************************************************************************************/


#include "Scheduler_Fixo.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
extern char *stackptrAtual;





/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int8_t Sched_inicia()
{
	// Inicializa o escalonador
	scheduler = (Scheduler_t*) malloc(sizeof(Scheduler_t));
	if (scheduler == NULL)
		return -1;
	
	
	// Cria a lista de tarefas
	scheduler->tarefas = ListaTarefas_cria(MAX_N_PRIORIDADES);
	if (scheduler->tarefas == NULL)
		return -1;
	

	// Inicializa as variaveis globais
	stackptrAtual = NULL;


	return 0;
}



int8_t Sched_termina()
{
	uint8_t resultado;
	
	
	// Apaga a lista de tarefas
	resultado = ListaTarefas_apaga(scheduler->tarefas);
	
	free(scheduler);
	
	return resultado;
}



int8_t Sched_adicionaTarefa(uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *))
{
	uint8_t resultado;
	
	resultado = ListaTarefas_adicionaTarefa(scheduler->tarefas, prioridade, stackSize, funcao);
	
	return resultado;
}



int8_t Sched_eliminaTarefa(Tarefa_t *tarefa)
{
	uint8_t resultado;
	
	resultado = ListaTarefas_removeTarefa(scheduler->tarefas, tarefa);
	
	return resultado;
}



void Sched_Schedule()
{
	// Nao faz nada, porque os timers ja implementam a activacao e desactivacao das tarefas. 
}




void Sched_dispatch()//  __attribute__((signal,naked))
{
	ListaTarefas_t *listatarefas = scheduler->tarefas;


	GUARDARCONTEXTO();

	uint8_t i, j;
	static int16_t prioridadeAtual;
	static Tarefa_t * tarefaAtual = NULL;
	if (tarefaAtual == NULL)
	{
		prioridadeAtual = -1;
	}
	else
	{
		prioridadeAtual = tarefaAtual->prioridade;
		tarefaAtual->stackPtr = stackptrAtual;
	}
	// IMPORTANTE: Falta fazer clear a prioridade atual quando uma tarefa termina
	for (i = listatarefas->nPrioridades - 1; i > System_Ceiling() && i > prioridadeAtual; i--)
	{
		for (j = 0; j < listatarefas->prioridades[i]->nTarefas; j++)
		{
			if (listatarefas->prioridades[i]->tarefas[j]->nActivacoes > 0)
			{
				tarefaAtual = listatarefas->prioridades[i]->tarefas[j];
				stackptrAtual = tarefaAtual->stackPtr;
				prioridadeAtual = i;
				RECUPERARCONTEXTO();
				asm volatile("reti");
			}
		}
	}
	RECUPERARCONTEXTO();
	asm volatile("reti");
}
