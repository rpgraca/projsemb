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


Timer_t* Timers_criaTimer(uint16_t periodo)
{
	Timer_t *timer;


	// Verificacao dos parametros passados a funcao
	if (periodo <= 0)
		return NULL;



	// Cria o timer
	timer = (Timer_t*)malloc(sizeof(Timer_t));
	if (timer == NULL)
		return NULL;

	timer->periodo = periodo;
	timer->tActual = 0;
	timer->tarefa = tarefaAtual;


	// Realocacao de memoria do vector
	vecTimers.timers = (Timer_t**)realloc(vecTimers.timers, (vecTimers.nTimers + 1) * sizeof(Timer_t*));
	if (vecTimers.timers == NULL)
		return NULL;


	vecTimers.timers[vecTimers.nTimers] = timer;
	vecTimers.nTimers++;


	return timer;
}



int8_t Timers_apagaTimer(Timer_t *timer)
{
	uint8_t i, j;


	// Verificacao dos parametros passados a funcao
	if (timer == NULL)
		return -1;


	// Procura o timer
	for (i = 0; i < vecTimers.nTimers; i++)
	{
		if (vecTimers.timers[i] == timer)
		{
			// Elimina o timer
			free(timer);


			// Copia as tarefas para o inicio do vector para deixar o espaco vazio no fim do vector
			for (j = i; j < vecTimers.nTimers - 1; j++)
				vecTimers.timers[j] = vecTimers.timers[j + 1];


			// Realocacao de memoria do vector
			vecTimers.timers = (Timer_t**)realloc(vecTimers.timers, (vecTimers.nTimers - 1) * sizeof(Timer_t*));
			if ((vecTimers.timers == NULL) && (vecTimers.nTimers != 1))	// Se nTimers = 1, entao o vector vai ficar NULL
				return -2;


			vecTimers.nTimers--;


			return 0;
		}

	}



	// O timer nao existe
	return -3;
}


void Timers_actualizaTimers()
{
	int8_t i;


	for (i = 0; i < vecTimers.nTimers; i++)
	{
		// Incrementa o timer
		vecTimers.timers[i]->tActual++;


		// Verifica se o timer terminou.
		// Caso tenha, activa a respectiva tarefa e reinicia o timer.
		if (vecTimers.timers[i]->tActual >= vecTimers.timers[i]->periodo)
		{
			vecTimers.timers[i]->tActual=0;
			vecTimers.timers[i]->tarefa->activada = 1;
		}
	}


	asm volatile("reti");
}




int8_t Timers_esperaActivacao(Timer_t *timer)
{
	int8_t resultado;


	// Verificacao dos parametros passados a funcao
	if (timer == NULL)
		return -1;



	// Verifica se o timer ja terminou.
	// Se ainda nao terminou, nao faz nada, pois quando terminar o interrupt handler
	// dos ticks vai activa-la.
	if (Timers_timerTerminado(timer))
	{
		timer->tarefa->activada = 1;

		if (resultado < 0)
			return -2;
	}


	// Limpa a flag de tarefa activa
	resultado = Tarefa_desactivaTarefa(timer->tarefa);

	if (resultado < 0)
		return -2;


	// Invoca o dispatcher para retirar esta tarefa de execucao e dar o CPU a outra tarefa
	Sched_dispatch();



	return 0;
}








int8_t Timers_sleep(uint16_t periodo)
{
	int8_t resultado;
	Timer_t *timer;


	// Cria o timer
	timer = Timers_criaTimer(periodo);

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
