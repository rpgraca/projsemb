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
	// (...)
}
