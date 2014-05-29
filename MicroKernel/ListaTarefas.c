/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                     Lista de Tarefas                                  */
/*****************************************************************************************/


#include "ListaTarefas.h"

#include <stdio.h>
#include <stdlib.h>



/**************************************************************/
/*                       FUNCOES AUXLIARES                    */
/**************************************************************/

/*
 * Cria uma nova tarefa.
 * 
 * @param prioridade: 0 < prioridade < MAX_PRIORIDADE
 * @returns: Apontador para a tarefa criada ou NULL em caso de erro.
 */
Tarefa_t* Tarefa_cria(int prioridade, int periodo, int stackSize, void* (*funcao)(void *))
{
	Tarefa_t *tarefa;


	// Cria a tarefa
	tarefa = (Tarefa_t*) malloc(sizeof(Tarefa_t));
	
	if (tarefa == NULL)
		return NULL;


	tarefa->prioridade = prioridade;
	tarefa->periodo = periodo;
	tarefa->stackSize = stackSize;
	tarefa->funcao = funcao;
	tarefa->nActivacoes = 0;

	return tarefa;
}


/*
 * Apaga uma tarefa, libertando toda a memoria alocada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int Tarefa_apaga(Tarefa_t *tarefa)
{
	// Verificacao dos parametros passados a funcao
	if (tarefa == NULL)
		return -1;


	free(tarefa);
	
	return 0;
}



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

ListaTarefas_t* ListaTarefas_cria(int nTarefas)
{
	int i;
	ListaTarefas_t *listaTarefas;
	
	
	// Verificacao dos parametros passados a funcao
	if (nTarefas < 0)
		return NULL;
		
	
	// Cria o vector
	listaTarefas = (ListaTarefas_t*) malloc(nTarefas * sizeof(ListaTarefas_t));
	if (listaTarefas == NULL)
		return NULL;
	
	
	// Inicializa cada lista de tarefas
	for (i=0; i < nTarefas; i++)
	{
		listaTarefas[i].tarefas = NULL;
		listaTarefas[i].nTarefas = 0;
	}
	
	
	
	return listaTarefas;
}


int ListaTarefas_apaga(ListaTarefas_t *listaTarefas)
{
	// Verificacao dos parametros passados a funcao
	if (listaTarefas == NULL)
		return -1;
	
	
	// (...)
	
	
	return 0;
}


int ListaTarefas_adicionaTarefa(ListaTarefas_t *listaTarefas, int prioridade, int periodo, int stackSize, void* (*funcao)(void *))
{
	// Verificacao dos parametros passados a funcao
	if (listaTarefas == NULL)
		return -1;
	
	
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	//
	// REVER !!!
	//
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	
	/*
	// Realocacao de memoria do vector
	listaTarefas->tarefas = (Tarefa_t**) realloc(listaTarefas->tarefas, (listaTarefas->nTarefas + 1) * sizeof(Tarefa_t*));
	if (listaTarefas->tarefas == NULL)
		return -2;
	
	
	// Adiciona a tarefa no vector
	listaTarefas->tarefas[listaTarefas->nTarefas + 1] = tarefa;
	listaTarefas->nTarefas++;
	*/
	
	
	return 0;
}





int ListaTarefas_removeTarefa(ListaTarefas_t *listaTarefas, Tarefa_t *tarefa)
{
	int i;
	int prioridade, nTarefas;
	
	
	// Verificacao dos parametros passados a funcao
	if (listaTarefas == NULL)
		return -1;
	
	
	
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	//
	// REVER !!!
	//
	////////////////////////////////////
	////////////////////////////////////
	////////////////////////////////////
	
	
	
	/*
	// Procura a tarefa
	prioridade = tarefa->prioridade;
	nTarefas = listaTarefas->nTarefas;
	
	
	for (i=0; i < nTarefas; i++)
	{
		// Elimina a tarefa
		if (listaTarefas->tarefas[i] == tarefa)
		{
			
			// (...)
			
			return 0;
		}
		
	}
	*/
	
	// A tarefa nao existe
	return -3;
}




