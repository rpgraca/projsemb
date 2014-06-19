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

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include <avr/interrupt.h>

/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
extern void * (*funcAtual)(void*);
extern char *stackptrAtual;
char * stackptrBak;
void * argumento;



/**************************************************************/
/*                 FUNCOES AUXLIARES - PROTOTIPOS             */
/**************************************************************/
Tarefa_t* Tarefa_cria(uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *), void* arg);
int8_t Tarefa_apaga(Tarefa_t *tarefa);
TarefasPrioridade_t* TarefasPrioridade_cria();
int8_t TarefasPrioridade_apaga(TarefasPrioridade_t* tarefasPrioridade);
int8_t TarefasPrioridade_adicionaTarefa(TarefasPrioridade_t* tarefasPrioridade, uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *), void* arg);
int8_t TarefasPrioridade_removeTarefa(TarefasPrioridade_t* tarefasPrioridade, Tarefa_t *tarefa);



/**************************************************************/
/*                  FUNCOES AUXLIARES - Tarefa_t              */
/**************************************************************/

/*
 * Cria uma nova tarefa.
 * 
 * @param prioridade: 0 < prioridade < MAX_PRIORIDADE
 * @return: Apontador para a tarefa criada ou NULL em caso de erro.
 */
Tarefa_t* Tarefa_cria(uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *), void * arg)
{
	Tarefa_t *tarefa;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	// Cria a tarefa
	tarefa = (Tarefa_t*) malloc(sizeof(Tarefa_t) + stackSize);

	if (tarefa == NULL)
		return NULL;


	tarefa->prioridade = prioridade;
	tarefa->stackSize = stackSize;
	tarefa->funcao = funcao;
	tarefa->activada = 1;
	tarefa->stackPtr = ((char*) tarefa) + stackSize;
	
	argumento = arg;	
	// Cria o contexto da tarefa
	cli(); // Desativar interrupçoes
	GUARDARSTACKPTR();
	stackptrBak = stackptrAtual;
	stackptrAtual = tarefa->stackPtr;
	funcAtual = tarefa->funcao;	
	CRIARCONTEXTO();
	GUARDARSTACKPTR();
	

	// Troca Bak e Atual
	stackptrBak = (char *) ((uint16_t) stackptrAtual ^ (uint16_t) stackptrBak);
	stackptrAtual = (char *) ((uint16_t) stackptrAtual ^ (uint16_t) stackptrBak);
	stackptrBak =  (char *) ((uint16_t) stackptrAtual ^ (uint16_t) stackptrBak);
	
	RECUPERARSTACKPTR();
	tarefa->stackPtr = stackptrBak;
	funcAtual = NULL;
	
	SREG = tmpstatus; // Recuperar estado original das interrupçoes
	
	return tarefa;
}


/*
 * Apaga uma tarefa, libertando toda a memoria alocada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Tarefa_apaga(Tarefa_t *tarefa)
{
	// Verificacao dos parametros passados a funcao
	if (tarefa == NULL)
		return -1;


	free(tarefa);
	
	return 0;
}



/**************************************************************/
/*             FUNCOES AUXLIARES - TarefasPrioridade_t        */
/**************************************************************/

/*
 * Cria um novo TarefasPrioridade_t
 *
 * @return: Apontador para a estrutura TarefasPrioridade_t criada ou NULL em caso de erro.
 */
TarefasPrioridade_t* TarefasPrioridade_cria()
{
	TarefasPrioridade_t *tarefasPrioridade;


	// Cria a estrutura
	tarefasPrioridade = (TarefasPrioridade_t*)malloc(sizeof(TarefasPrioridade_t));
	if (tarefasPrioridade == NULL)
		return NULL;


	
	tarefasPrioridade->tarefas = NULL;
	tarefasPrioridade->nTarefas = 0;
	tarefasPrioridade->ultimaTarefa = 0;


	return tarefasPrioridade;
}


/*
 * Apaga um TarefasPrioridade_t, libertando toda a memoria alocada.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t TarefasPrioridade_apaga(TarefasPrioridade_t* tarefasPrioridade)
{
	int8_t i, resultado;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes

	// Verificacao dos parametros passados a funcao
	if (tarefasPrioridade == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}

	
	// Remove todas as tarefas presentes no vector
	for (i = 0; i < tarefasPrioridade->nTarefas; i++)
	{
		resultado = TarefasPrioridade_removeTarefa(tarefasPrioridade, tarefasPrioridade->tarefas[i]);

		if (resultado < 0)
		{
			SREG = tmpstatus;
			return -2;
		}
	}


	// Apaga a estrutura
	free(tarefasPrioridade);

	SREG = tmpstatus;

	return 0;
}



/*
 * Adiciona uma tarefa ao TarefasPrioridade_t.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t TarefasPrioridade_adicionaTarefa(TarefasPrioridade_t* tarefasPrioridade, uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *),void * arg)
{
	Tarefa_t *tarefa;


	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	cli(); // Desativar interrupçoes

	// Verificacao dos parametros passados a funcao
	if (tarefasPrioridade == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}


	// Cria a tarefa
	tarefa = Tarefa_cria(prioridade, stackSize, funcao, arg);
	if (tarefa == NULL)
	{
		SREG = tmpstatus;
		return -2;
	}


	// Realocacao de memoria do vector
	tarefasPrioridade->tarefas = (Tarefa_t**)realloc(tarefasPrioridade->tarefas, (tarefasPrioridade->nTarefas + 1) * sizeof(Tarefa_t*));
	if (tarefasPrioridade->tarefas == NULL)
	{
		SREG = tmpstatus;
		return -3;
	}


	// Adiciona a tarefa no vector
	tarefasPrioridade->tarefas[tarefasPrioridade->nTarefas] = tarefa;
	tarefasPrioridade->nTarefas++;

	SREG = tmpstatus;

	return 0;
}



/*
 * Remove uma tarefa do TarefasPrioridade_t.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t TarefasPrioridade_removeTarefa(TarefasPrioridade_t* tarefasPrioridade, Tarefa_t *tarefa)
{
	int8_t i, j, resultado;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	
	
	
	cli(); // Desativar interrupçoes
	
	// Verificacao dos parametros passados a funcao
	if (tarefasPrioridade == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}


	// Procura a tarefa
	for (i=0; i < tarefasPrioridade->nTarefas; i++)
	{
		if (tarefasPrioridade->tarefas[i] == tarefa)
		{
			// Elimina a tarefa
			resultado = Tarefa_apaga(tarefa);
			if (resultado < 0)
			{
				SREG = tmpstatus;
				return -2;
			}
			
			// Copia as tarefas para o inicio do vector para deixar o espaco vazio no fim do vector
			for (j = i; j < tarefasPrioridade->nTarefas - 1; j++)
				tarefasPrioridade->tarefas[j] = tarefasPrioridade->tarefas[j + 1];

			
			// Realocacao de memoria do vector
			tarefasPrioridade->tarefas = (Tarefa_t**)realloc(tarefasPrioridade->tarefas, (tarefasPrioridade->nTarefas - 1) * sizeof(Tarefa_t*));
			if ( (tarefasPrioridade->tarefas == NULL) && (tarefasPrioridade->nTarefas != 1) )	// Se nTarefas = 1, entao o vector vai ficar NULL
			{
				SREG = tmpstatus;
				return -3;
			}


			tarefasPrioridade->nTarefas--;

			SREG = tmpstatus;

			return 0;
		}

	}



	// A tarefa nao existe
	return -3;
}





/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int8_t Tarefa_desactivaTarefa(Tarefa_t *tarefa)
{
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	cli(); // Desativar interrupçoes
	
	// Verificacao dos parametros passados a funcao
	if (tarefa == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}

	tarefa->activada = 0;

	SREG = tmpstatus;
	
	return 0;
}


ListaTarefas_t* ListaTarefas_cria(uint8_t nPrioridades)
{
	uint8_t i;
	ListaTarefas_t *listaTarefas;
	
	
	// Verificacao dos parametros passados a funcao
	if (nPrioridades < 0)
		return NULL;
	

	// Cria a estrutura
	listaTarefas = (ListaTarefas_t*)malloc(sizeof(ListaTarefas_t));
	if (listaTarefas == NULL)
		return NULL;


	// Cria o vector de TarefasPrioridade_t
 	listaTarefas->prioridades = (TarefasPrioridade_t**)calloc(nPrioridades, sizeof(TarefasPrioridade_t*));
	if (listaTarefas->prioridades == NULL)
	{
		free(listaTarefas);
		return NULL;
	}


	// Cria os vectores de prioridades
	for (i = 0; i < nPrioridades; i++)
	{
		listaTarefas->prioridades[i] = TarefasPrioridade_cria();
		
		if (listaTarefas->prioridades == NULL)
		{
			free(listaTarefas->prioridades);
			free(listaTarefas);

			return NULL;
		}
	}

	listaTarefas->nPrioridades = nPrioridades;


	return listaTarefas;
}



int8_t ListaTarefas_apaga(ListaTarefas_t *listaTarefas)
{
	int8_t i, resultado;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes


	// Verificacao dos parametros passados a funcao
	if (listaTarefas == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}
	
	
	// Apaga o vector de prioridades
	for (i = 0; i < listaTarefas->nPrioridades; i++)
	{
		if (listaTarefas->prioridades[i] == NULL)
			continue;

		resultado = TarefasPrioridade_apaga(listaTarefas->prioridades[i]);
		
		if (resultado < 0)
		{
			SREG = tmpstatus;
			return -2;
		}
	}


	//free(listaTarefas->prioridades);		// Comentado, porque a funcao "TarefasPrioridade_apaga()" ja apaga a memoria
	free(listaTarefas);
	
	SREG = tmpstatus;
	
	return 0;
}



int8_t ListaTarefas_adicionaTarefa(ListaTarefas_t *listaTarefas, uint8_t prioridade, uint16_t stackSize, void* (*funcao)(void *), void * arg)
{
	int8_t resultado;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes


	// Verificacao dos parametros passados a funcao
	if ((listaTarefas == NULL) || (prioridade < 0 || prioridade >= listaTarefas->nPrioridades) || (stackSize <= 0) || (funcao == NULL) )
	{
		SREG = tmpstatus;
		return -1;
	}

	resultado = TarefasPrioridade_adicionaTarefa(listaTarefas->prioridades[prioridade], prioridade, stackSize, funcao,arg);
	
	SREG = tmpstatus;

	return resultado;
}



int8_t ListaTarefas_removeTarefa(ListaTarefas_t *listaTarefas, Tarefa_t *tarefa)
{
	int8_t resultado;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes
	
	
	// Verificacao dos parametros passados a funcao
	if ( (listaTarefas == NULL) || (tarefa == NULL) )
	{
		SREG = tmpstatus;
		return -1;
	}
	
	resultado = TarefasPrioridade_removeTarefa(listaTarefas->prioridades[tarefa->prioridade], tarefa);


	SREG = tmpstatus;
	return resultado;
}
