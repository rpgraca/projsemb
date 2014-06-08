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


#ifndef _SCHEDULER_FIXO_H_
#define _SCHEDULER_FIXO_H_


#include "ListaTarefas.h"


/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/
// Maximo tamanho da stack
//#define MAX_STACK_SIZE	2048

// Numero maximo de prioridades
#define MAX_N_PRIORIDADES 20



/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura do escalonador
typedef struct
{
	ListaTarefas_t *tarefas;


	/////////////////////
	/////////////////////
	// ACRESCENTAR INFORMACOES RELEVANTES PARA O SCHEDULER (SE NECESSARIO)
	/////////////////////
	/////////////////////

} Scheduler_t;



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
Scheduler_t *scheduler;		// Apontador para o scheduler



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa o escalonador.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int Sched_inicia();

/*
 * Apaga o escalonador, libertando toda a memoria alocada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int Sched_apaga();


/*
 * Adiciona uma tarefa ao escalonador.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int Sched_adicionaTarefa(int prioridade, int stackSize, void* (*funcao)(void *));


/*
 * Elimina a tarefa do escalonador.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int Sched_eliminaTarefa(Tarefa_t *tarefa);



/*
 * 
 * 
 */
void Sched_Schedule();



#endif