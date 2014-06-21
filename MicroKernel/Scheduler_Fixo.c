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
#include <avr/sleep.h>



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
extern char *stackptrAtual;
extern char *stackptrIdle;
extern Tarefa_t *tarefaAtual;
extern ListaTarefas_t* listatarefas;
extern uint8_t ceilingstackSize;
extern uint8_t* ceilingStack;
extern Tarefa_t ** tarefasStack;



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
	uint8_t j, FLAG_INATIVO;
	int16_t i,prioridadeAtual;

	if (tarefaAtual == NULL)
	{
		FLAG_INATIVO = 1;
		prioridadeAtual = -1;
	}

	else
	{
		FLAG_INATIVO = 0;
		if(tarefaAtual->activada == 0)
		{
			GUARDARCONTEXTO();
			tarefaAtual->stackPtr = stackptrAtual;
			tarefaAtual = NULL;
			prioridadeAtual = -1;
		}

		else
		{
			prioridadeAtual = tarefaAtual->prioridade;
		}

	}

	for (i = listatarefas->nPrioridades - 1; i > System_Ceiling() && i > prioridadeAtual; i--)
	{
		if(listatarefas->prioridades[i]->nTarefas == 0)
		{
			continue;
		}
		
		// Dois ciclos para verificar ativacoes de forma Round Robin
		for (j = listatarefas->prioridades[i]->ultimaTarefa + 1; j < listatarefas->prioridades[i]->nTarefas; j++)
		{
			if (listatarefas->prioridades[i]->tarefas[j]->activada > 0)
			{
				listatarefas->prioridades[i]->ultimaTarefa=j;
				if(tarefaAtual != NULL)
				{
					GUARDARCONTEXTO();
					tarefaAtual->stackPtr = stackptrAtual;
				}
				tarefaAtual = listatarefas->prioridades[i]->tarefas[j];
				stackptrAtual = tarefaAtual->stackPtr;
				RECUPERARCONTEXTO();
				printf("\nExecutar: %u |",listatarefas->prioridades[i]->tarefas[j]->prioridade);
				asm volatile("ret");
			}
		}

		for (j = 0; j <= listatarefas->prioridades[i]->ultimaTarefa; j++)
		{
			if (listatarefas->prioridades[i]->tarefas[j]->activada > 0)
			{
				listatarefas->prioridades[i]->ultimaTarefa=j;
				if(tarefaAtual != NULL)
				{
					GUARDARCONTEXTO();
					tarefaAtual->stackPtr = stackptrAtual;
				}
				tarefaAtual = listatarefas->prioridades[i]->tarefas[j];
				stackptrAtual = tarefaAtual->stackPtr;
				RECUPERARCONTEXTO();
				printf("\nExecutar: %u |",listatarefas->prioridades[i]->tarefas[j]->prioridade);
				asm volatile("ret");
			}
		}
	}

	if(tarefaAtual == NULL)
	{
		// Verificar se há tarefas com semáforos
		if(System_Ceiling() > -1)
		{
			tarefaAtual = Stack_Top(); 
			stackptrAtual = tarefaAtual->stackPtr;
			RECUPERARCONTEXTO();
			asm volatile("ret");
		}
		// Caso nao haja tarefas a executar, limpa PC de retorno da stack e vai para sleepmode
		// FLAG_INATIVO indica se a o CPU já estava inativo antes, só nesse caso é que é preciso limpar
		// endereço de retorno da stack
		if(FLAG_INATIVO == 1)
		{
			RECUPERARSTACKPTR();
			stackptrAtual -= 2;
			GUARDARSTACKPTR();
			printf("\nSleep");
		}
		sei();
		sleep_mode();
	}
	asm volatile("ret");
}
