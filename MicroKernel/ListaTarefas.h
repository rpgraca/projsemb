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




/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/




/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura de uma tarefa
typedef struct
{
	int prioridade;
	int periodo;
	
	int stackSize;
	
	void* (*funcao)(void *);
	int nActivacoes;
	
} Tarefa_t;


// Estrutura de uma lista de tarefas
typedef struct
{
	Tarefa_t **tarefas;
	int nTarefas;
} ListaTarefas_t;



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Cria uma lista de tarefas.
 * 
 * @return: Apontador para a lista de tarefas criada ou NULL em caso de erro.
 */
ListaTarefas_t* ListaTarefas_cria();


/*
 * Apaga toda a lista de tarefas, libertando toda a memoria alocada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int ListaTarefas_apaga(ListaTarefas_t *listaTarefas);


/*
 * Adiciona uma tarefa a lista de tarefas.
 * 
 * @param prioridade: 0 < prioridade < MAX_PRIORIDADE
 * @returns: Apontador para a tarefa criada ou NULL em caso de erro.
 */
int ListaTarefas_adicionaTarefa(ListaTarefas_t *listaTarefas, int prioridade, int periodo, int stackSize, void* (*funcao)(void *));


/*
 * Remove uma tarefa da lista de tarefas.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int ListaTarefas_removeTarefa(ListaTarefas_t *listaTarefas, Tarefa_t *tarefa);
