/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                        Timers                                         */
/*****************************************************************************************/



#include "Timers.h"

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
// Vector dos timers criados
VectorTimers_t vecTimers;
extern Tarefa_t * tarefaAtual;


/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/


Timer_t* Timers_criaTimer(uint16_t periodo,uint16_t numTarefas)
{
	Timer_t *timer;

	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	// Verificacao dos parametros passados a funcao
	if (numTarefas <= 0 || periodo <= 0)
	{
		SREG = tmpstatus;
		return NULL;
	}



	// Cria o timer
	timer = (Timer_t*)malloc(sizeof(Timer_t));
	if (timer == NULL)
	{
		SREG = tmpstatus;
		return NULL;
	}

	timer->periodo = periodo;
	timer->tActual = 0;
	timer->numTarefas = numTarefas;
	timer->stackSize = 0;

	timer->tarefas = (Tarefa_t**) malloc(sizeof(Tarefa_t*)*numTarefas);

	// Realocacao de memoria do vector
	cli(); // Desativar interrupçoes
	vecTimers.timers = (Timer_t**)realloc(vecTimers.timers, (vecTimers.nTimers + 1) * sizeof(Timer_t*));
	if (vecTimers.timers == NULL)
	{
		SREG = tmpstatus;
		return NULL;
	}


	vecTimers.timers[vecTimers.nTimers] = timer;
	vecTimers.nTimers++;


	SREG = tmpstatus;
	return timer;
}



int8_t Timers_apagaTimer(Timer_t *timer)
{
	uint8_t i, j;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes

	// Verificacao dos parametros passados a funcao
	if (timer == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}


	// Procura o timer
	for (i = 0; i < vecTimers.nTimers; i++)
	{
		if (vecTimers.timers[i] == timer)
		{
			// Elimina o timer
			free(timer->tarefas);
			free(timer);


			// Copia as tarefas para o inicio do vector para deixar o espaco vazio no fim do vector
			for (j = i; j < vecTimers.nTimers - 1; j++)
				vecTimers.timers[j] = vecTimers.timers[j + 1];


			// Realocacao de memoria do vector
			vecTimers.timers = (Timer_t**)realloc(vecTimers.timers, (vecTimers.nTimers - 1) * sizeof(Timer_t*));
			if ((vecTimers.timers == NULL) && (vecTimers.nTimers != 1))	// Se nTimers = 1, entao o vector vai ficar NULL
			{
				SREG = tmpstatus;
				return -1;
			}


			vecTimers.nTimers--;


			SREG = tmpstatus;
			return 0;
		}

	}


	SREG = tmpstatus;

	// O timer nao existe
	return -3;
}


void Timers_actualizaTimers()
{
	int8_t i,j;


	for (i = 0; i < vecTimers.nTimers; i++)
	{
		// Incrementa o timer
		vecTimers.timers[i]->tActual++;


		// Verifica se o timer terminou.
		// Caso tenha, activa a respectiva tarefa e reinicia o timer.
		if (vecTimers.timers[i]->tActual >= vecTimers.timers[i]->periodo)
		{
			vecTimers.timers[i]->tActual=0;
			for(j=0; j < vecTimers.timers[i]->stackSize; j++)
			{
				vecTimers.timers[i]->tarefas[j]->activada = 1;
				printf("\nAT %u",vecTimers.timers[i]->tarefas[j]->prioridade);
			}
			vecTimers.timers[i]->stackSize = 0;
		}
	}

	asm volatile("ret");
}




int8_t Timers_esperaActivacao(Timer_t *timer)
{
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes

	// Verificacao dos parametros passados a funcao
	if (timer == NULL)
	{
//		SREG = tmpstatus;
		return -1;
	}

	if(timer->stackSize >= timer->numTarefas)
	{
//		SREG = tmpstatus;
		return -2;
	}


	
	timer->tarefas[timer->stackSize] = tarefaAtual;
	timer->stackSize++;

	// Limpa a flag de tarefa activa
	tarefaAtual->activada = 0;


	// Invoca o dispatcher para retirar esta tarefa de execucao e dar o CPU a outra tarefa
	Sched_dispatch();
	SREG = tmpstatus;



	return 0;
}








int8_t Timers_sleep(uint16_t periodo)
{
	int8_t resultado;
	Timer_t *timer;


	// Cria o timer
	timer = Timers_criaTimer(periodo,1);

	if (timer == NULL)
		return -1;


	// Suspende a tarefa
	resultado = Timers_esperaActivacao(timer);
	if (resultado < 0)
	{
		Timers_apagaTimer(timer);

		return -2;
	}


	// Apaga o timer
	resultado = Timers_apagaTimer(timer);


	return 0;
}
