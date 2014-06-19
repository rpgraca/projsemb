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



#ifndef _LISTATAREFAS_H_
#define _LISTATAREFAS_H_

#include <avr/io.h>
#include "Context.h"



/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/
#define N_REGISTOS_CPU	32			// Numero de registos do CPU



/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura de uma tarefa
typedef struct
{
	uint8_t prioridade;
	uint8_t activada;			// Flag que indica que a tarefa esta activa
	
	uint16_t stackSize;
	
	void* (*funcao)(void *);
	char *stackPtr;				// Apontador para a sua stack
} Tarefa_t;


// Vector com as tarefas da mesma prioridade
typedef struct
{
	Tarefa_t **tarefas;			// Vector de apontadores para tarefas
	uint8_t nTarefas;
	uint8_t ultimaTarefa;
} TarefasPrioridade_t;


// Conjunto de todas as tarefas
typedef struct
{
	TarefasPrioridade_t **prioridades;
	uint8_t nPrioridades;
} ListaTarefas_t;

/**************************************************************/
/*							  MACROS                          */
/**************************************************************/
//#define Tarefa_activaTarefa(tarefa) { ((tarefa)==NULL)?(-1):(0 && (tarefa->activada = 1) }
 

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/


// --- TAREFAS --- //

/*
 * Activa uma tarefa.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Tarefa_activaTarefa(Tarefa_t *tarefa);


/*
* Desactiva uma tarefa.
*
* @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
*/
int8_t Tarefa_desactivaTarefa(Tarefa_t *tarefa);


/*
* ELIMINADA não estava a funcionar bem e foi criada variável global tarefaAtual porque dava jeito noutras situações
* Devolve o apontador da estrutura "Tarefa_t" que contem o membro "funcaoPtr".
*
* @return: Apontador da estrutura "Tarefa_t" ou NULL em caso de erro.c
*/
//char* Tarefa_apontadorTarefa(char *funcaoPtr);



// --- LISTA DE TAREFAS --- //


/*
 * Cria uma lista de tarefas.
 * 
 * @return: Apontador para a lista de tarefas criada ou NULL em caso de erro.
 */
ListaTarefas_t* ListaTarefas_cria(uint8_t nPrioridades);


/*
 * Apaga toda a lista de tarefas, libertando toda a memoria alocada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t ListaTarefas_apaga(ListaTarefas_t *listaTarefas);


/*
 * Adiciona uma tarefa a lista de tarefas.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t ListaTarefas_adicionaTarefa(ListaTarefas_t *listaTarefas, uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *));


/*
 * Remove uma tarefa da lista de tarefas.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t ListaTarefas_removeTarefa(ListaTarefas_t *listaTarefas, Tarefa_t *tarefa);



/*
 * Inicializa tarefa 
 */
void funcInit(Tarefa_t tarefa);



#endif
