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
//#include "Timers.h"
#include "Context.h"
#include "Semaforo.h"

/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/

// Numero maximo de prioridades
#define MAX_N_PRIORIDADES 2



/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura do escalonador
/*typedef struct
{
	ListaTarefas_t *tarefas;


	/////////////////////
	/////////////////////
	// ACRESCENTAR INFORMACOES RELEVANTES PARA O SCHEDULER (SE NECESSARIO)
	/////////////////////
	/////////////////////

} Scheduler_t;
*/


/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
//extern Scheduler_t *scheduler;		// Apontador para o scheduler
//extern ListaTarefas_t *listatarefas;




/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa o escalonador.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Sched_inicia();

/*
 * Termina o escalonador, libertando toda a memoria alocada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Sched_termina();


/*
 * Adiciona uma tarefa ao escalonador.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Sched_adicionaTarefa(uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *), void* arg);


/*
 * Elimina a tarefa do escalonador.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Sched_eliminaTarefa(Tarefa_t *tarefa);



/*
 * Verifica os temporizadores relativos a periodização das tarefas do scheduler
 * e, caso algum temporizador tenha terminado, e incrementado o contador de activacoes
 * da respectiva tarefa.
 */
void Sched_schedule();




/*
* Verifica se existe alguma tarefa de maior prioridade com activacoes
* pendentes e, caso haja, activa-a (aloca os recursos do sistema para a
* tarefa).
*/
void Sched_dispatch() __attribute__((naked));



#endif
