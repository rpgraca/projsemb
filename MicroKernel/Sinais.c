/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                        Sinais                                         */
/*****************************************************************************************/



#include "Sinais.h"

#include <avr/io.h>
#include <stdlib.h>



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
// Vector dos sinais criados
extern Tarefa_t * tarefaAtual;


/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/


Sinal_t* Sinais_criaSinal(uint16_t numTarefas)
{
	Sinal_t *sinal;

	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	// Verificacao dos parametros passados a funcao
	if (numTarefas <= 0)
	{
		return NULL;
	}



	// Cria o sinal
	sinal = (Sinal_t*)malloc(sizeof(Sinal_t));
	if (sinal == NULL)
	{
		return NULL;
	}

	sinal->numTarefas = numTarefas;
	sinal->stackSize = 0;

	sinal->tarefas = (Tarefa_t**) malloc(sizeof(Tarefa_t*)*numTarefas);

	cli(); // Desativar interrupçoes

	SREG = tmpstatus;

	return sinal;
}



int8_t Sinais_apagaSinal(Sinal_t *sinal)
{
	uint8_t i, j;

	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	cli(); // Desativar interrupçoes

	// Verificacao dos parametros passados a funcao
	if (sinal == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}


	Sinais_sinaliza(sinal);

	// Elimina o sinal
	free(sinal->tarefas);
	free(sinal);


	return 0;
}




int8_t Sinais_esperaSinal(Sinal_t *sinal)
{
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	// Verificacao dos parametros passados a funcao
	cli(); // Desativar interrupçoes
	if (sinal == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}

	if(sinal->stackSize >= sinal->numTarefas)
	{
		SREG = tmpstatus;
		return -2;
	}

	sinal->tarefas[sinal->stackSize] = tarefaAtual;
	sinal->stackSize++;

	// Limpa a flag de tarefa activa
	tarefaAtual->activada=0;




	// Invoca o dispatcher para retirar esta tarefa de execucao e dar o CPU a outra tarefa
	Sched_dispatch();

	SREG = tmpstatus;


	return 0;
}


int8_t Sinais_sinaliza(Sinal_t *sinal)
{
	int j;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	cli(); // Desativar interrupçoes

	if(sinal == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}

	for(j=0; j < sinal->stackSize; j++)
	{
		sinal->tarefas[j]->activada = 1;
	}
	sinal->stackSize = 0;
	
	SREG = tmpstatus;
	return 0;
}
