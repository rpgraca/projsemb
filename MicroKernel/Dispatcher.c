/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                      Dispatcher                                       */
/*****************************************************************************************/


#include "Dispatcher.h"
#include "Context.h"
#include "ListaTarefas.h"
#include <avr/io.h>
#include <stdio.h>

char * stackptrAtual=NULL;
extern ListaTarefas_t * listatarefas;

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

uint8_t Disp_inicia()
{
	// (...)


	return 0;
}



uint8_t Disp_apaga()
{
	// (...)


	return 0;
}



void Disp_Dispatch()//  __attribute__((signal,naked))
{
	/*
	* Verifica se existe alguma tarefa de maior prioridade com activacoes
	* pendentes e, caso haja, activa-a (aloca os recursos do sistema para a
	* tarefa).
	*/
	GUARDARCONTEXTO();

	uint8_t i,j;
	static int16_t prioridadeAtual;
	static Tarefa_t * tarefaAtual=NULL;
	if(tarefaAtual==NULL)
	{
		prioridadeAtual=-1;
	}
	else
	{
		prioridadeAtual = tarefaAtual->prioridade;
		tarefaAtual->stackPtr=stackptrAtual;
	}
	// IMPORTANTE: Falta fazer clear à prioridade atual quando uma tarefa termina
	for(i=listatarefas->nPrioridades-1; i > System_Ceiling() && i > prioridadeAtual ; i--)
	{
		for(j=0; j < listatarefas->prioridades[i]->nTarefas ; j++ )
		{
			if(listatarefas->prioridades[i]->tarefas[j]->nActivacoes > 0)
			{
				tarefaAtual = listatarefas->prioridades[i]->tarefas[j];
				stackptrAtual = tarefaAtual->stackPtr;
				prioridadeAtual=i;
				RECUPERARCONTEXTO();
				asm volatile("reti");
			}
		}
	}
	RECUPERARCONTEXTO();
	asm volatile("reti");
}
