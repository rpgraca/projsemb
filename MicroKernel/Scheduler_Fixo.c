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

#include <stdio.h>
#include <stdlib.h>



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int Sched_inicia()
{
	// Inicializa o escalonador
	scheduler = (Scheduler_t*) malloc(sizeof(Scheduler_t));
	if (scheduler == NULL)
		return -1;
	
	
	// Cria a lista de tarefas
	scheduler->prioridades = ListaTarefas_cria(MAX_N_PRIORIDADES);
	if (scheduler->prioridades == NULL)
		return -1;
	
	scheduler->stackLivre = MAX_STACK_SIZE;
	

	return 0;
}



int Sched_apaga()
{
	int resultado = 0;
	
	
	// Apaga a lista de tarefas
	resultado += ListaTarefas_apaga(scheduler->prioridades);
	
	free(scheduler);
	
	return resultado;
}



int Sched_adicionaTarefa(int prioridade, int periodo, int stackSize, void* (*funcao)(void *))
{
	int resultado;
	
	
	// Verificacao dos parametros passados a funcao
	if ( (prioridade < 0 || prioridade >= MAX_N_PRIORIDADES) ||
		(periodo < 0) ||
		(stackSize < 0 || stackSize >= MAX_STACK_SIZE) ||
		(funcao == NULL) )
		return -1;


	// Cria a tarefa
	if (stackSize > scheduler->stackLivre)		// Verifica se existe espaco na stack para a tarefa
		return -2;
	
	resultado = ListaTarefas_adicionaTarefa(scheduler->prioridades, prioridade, periodo, stackSize, funcao);
	
	if (resultado < 0)
		return -3;
	
	
	scheduler->stackLivre -= stackSize;
	
	return 0;
}



int Sched_eliminaTarefa(Tarefa_t *tarefa)
{
	int stackSize;
	
	int resultado;
	
	
	// Verificacao dos parametros passados a funcao
	if (tarefa == NULL)
		return -1;
	
	
	// Elimina a tarefa
	stackSize = tarefa->stackSize;
	
	resultado = ListaTarefas_removeTarefa(scheduler->prioridades, tarefa);
	
	if (resultado < 0)
		return -2;
	
	
	scheduler->stackLivre += stackSize;
	return 0;
}
