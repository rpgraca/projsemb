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
extern char *stackptrIdle;
extern Tarefa_t *tarefaAtual;
extern ListaTarefas_t* listatarefas;
extern uint8_t ceilingstackSize;
extern uint8_t* ceilingStack;



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int8_t Sched_inicia()
{
	// Inicializa o escalonador
	
	// Cria a lista de tarefas
	listatarefas = ListaTarefas_cria(MAX_N_PRIORIDADES);
	if (listatarefas == NULL)
		return -1;
	

	// Inicializa as variaveis globais
	stackptrAtual = NULL;


	return 0;
}



int8_t Sched_termina()
{
	uint8_t resultado;
	
	
	// Apaga a lista de tarefas
	resultado = ListaTarefas_apaga(listatarefas);
	
	return resultado;
}



int8_t Sched_adicionaTarefa(uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *))
{
	uint8_t resultado;
	
	resultado = ListaTarefas_adicionaTarefa(listatarefas, prioridade, stackSize, funcao);
	
	return resultado;
}



int8_t Sched_eliminaTarefa(Tarefa_t *tarefa)
{
	uint8_t resultado;
	
	resultado = ListaTarefas_removeTarefa(listatarefas, tarefa);
	
	return resultado;
}



void Sched_Schedule()
{
	// Nao faz nada, porque os timers ja implementam a activacao e desactivacao das tarefas. 
}


void Sched_dispatch()//  __attribute__((signal,naked))
{
	//ListaTarefas_t *listatarefas = scheduler->tarefas;


	GUARDARCONTEXTO();

	uint8_t j;
	int16_t i,prioridadeAtual;

	if (tarefaAtual == NULL)
	{
		prioridadeAtual = -1;
	}

	else
	{
		tarefaAtual->stackPtr = stackptrAtual;
		if(tarefaAtual->activada == 0)
		{
			tarefaAtual = NULL;
			prioridadeAtual = -1;
			//COLOCAR STACKPOINTER NUM while(1) OU MANDAR CPU PARA POUPANCA DE ENERGIA CASO NAO HAJA ATIVACOES
		}
		else
		{
			prioridadeAtual = tarefaAtual->prioridade;
		}
	}

	for (i = listatarefas->nPrioridades - 1; i > System_Ceiling() && i > prioridadeAtual; i--)
	{
		// Dois ciclos para verificar ativacoes de forma Round Robin
		if(listatarefas->prioridades[i]->nTarefas == 0)
		{
			continue;
		}
		
		for (j = listatarefas->prioridades[i]->ultimaTarefa + 1; j < listatarefas->prioridades[i]->nTarefas; j++)
		{
			if (listatarefas->prioridades[i]->tarefas[j]->activada > 0)
			{
				listatarefas->prioridades[i]->ultimaTarefa=j;
				tarefaAtual = listatarefas->prioridades[i]->tarefas[j];
				stackptrAtual = tarefaAtual->stackPtr;
				prioridadeAtual = i;
				RECUPERARCONTEXTO();
				asm volatile("reti");
			}
		}

		for (j = 0; j <= listatarefas->prioridades[i]->ultimaTarefa; j++)
		{
			if (listatarefas->prioridades[i]->tarefas[j]->activada > 0)
			{
				listatarefas->prioridades[i]->ultimaTarefa=j;
				tarefaAtual = listatarefas->prioridades[i]->tarefas[j];
				stackptrAtual = tarefaAtual->stackPtr;
				prioridadeAtual = i;
				RECUPERARCONTEXTO();
				asm volatile("reti");
			}
		}
	}
	if(tarefaAtual == NULL)
	{
		stackptrAtual = stackptrIdle;
		RECUPERARSTACKPTR();
		asm volatile("reti");
	}
	RECUPERARCONTEXTO();
	asm volatile("reti");
}
