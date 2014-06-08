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
	uint16_t stackSize;
	
	uint8_t nActivacoes;
	
	void* (*funcao)(void *);
	char *stackPtr;				// Apontador para a sua stack
} Tarefa_t;


// Vector com as tarefas da mesma prioridade
typedef struct
{
	Tarefa_t **tarefas;			// Vector de apontadores para tarefas
	uint8_t nTarefas;
} TarefasPrioridade_t;


// Conjunto de todas as tarefas
typedef struct
{
	TarefasPrioridade_t **prioridades;
	uint8_t nPrioridades;
} ListaTarefas_t;



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

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
int ListaTarefas_apaga(ListaTarefas_t *listaTarefas);


/*
 * Adiciona uma tarefa a lista de tarefas.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int ListaTarefas_adicionaTarefa(ListaTarefas_t *listaTarefas, uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *));


/*
 * Remove uma tarefa da lista de tarefas.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int ListaTarefas_removeTarefa(ListaTarefas_t *listaTarefas, Tarefa_t *tarefa);


#endif