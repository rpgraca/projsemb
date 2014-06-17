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
/*                           FUNCOES                          */
/**************************************************************/

int8_t Timers_inicia()
{
	// Configuracao do timer do microcontrolador


	//////////////////////////////////////////////////////////////////////////////////////////


	/*
	// Desactiva as interrupcoes
	cli();

	DDRB = (1<<LEDA) | (1<<LEDB);  // Define LED do arduino como saida (PORTB5)
	OCR1A = (unsigned int) ((F_CPU/PRESCALAR)*CLOCKTIME);

	TCCR1B |= (1 << WGM12);  // Mode 4, CTC on OCR1A

	TIMSK1 |= (1 << OCIE1A); //Set interrupt on compare match

	// Iniciar timer com prescaler definido devidamente
	switch(PRESCALAR)
	{
	case 1:		TCCR1B |= (1 << CS10);
	break;
	case 8:		TCCR1B |= (1 << CS11);
	break;
	case 16:	TCCR1B |= (1 << CS11) | (1 << CS10);
	break;
	case 256:	TCCR1B |= (1 << CS12);
	break;
	case 1024:	TCCR1B |= (1 << CS12) | (1 << CS10);
	break;
	}
	

	// Activa as interrupcoes
	sei();
	*/

	//////////////////////////////////////////////////////////////////////////////////////////




	// Inicializa o vector de timers
	vecTimers.timers = NULL;
	vecTimers.nTimers = 0;


	return 0;
}



int8_t Timers_termina()
{
	int8_t i, resultado;


	// Desactiva o timer do microcontrolador
	
	/////////////////////////////////////////////////////////////////
	//
	// (...)
	//
	/////////////////////////////////////////////////////////////////



	// Apaga todos os timers activos
	for (i = 0; i < vecTimers.nTimers; i++)
	{
		resultado = Timers_apagaTimer(vecTimers.timers[i]);

		if (resultado < 0)
			return -1;
	}


	//free(vecTimers.timers);			// Comentado, porque a funcao "Timers_apagaTimer()" ja apaga o vector


	return 0;
}



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
	timer->tarefa = Tarefa_apontadorTarefa(funcAtual);


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




int8_t Timers_reiniciaTimer(Timer_t *timer)
{



	return 0;
}




void Timers_actualizaTimers()
{
	int8_t i, resultado;


	for (i = 0; i < vecTimers.nTimers; i++)
	{
		// Incrementa o timer
		vecTimers.timers[i]->tActual++;


		// Verifica se o timer terminou.
		// Caso tenha, activa a respectiva tarefa e reinicia o timer.
		if (Timers_timerTerminado(vecTimers.timers[i]))
		{
			resultado = Timers_reiniciaTimer(vecTimers.timers[i]);

			if (resultado < 0)
				return -1;

			resultado = Tarefa_activaTarefa(vecTimers.timers[i]->tarefa);

			if (resultado < 0)
				return -2;
		}
	}


	return 0;
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
		resultado = Tarefa_activaTarefa(timer->tarefa);

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



int8_t Timers_timerTerminado(Timer_t *timer)
{
	// Verificacao dos parametros passados a funcao
	if (timer == NULL)
		return -1;

	return (timer->tActual >= timer->periodo);
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