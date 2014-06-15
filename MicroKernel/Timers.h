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





///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
//
// FALTA VER COMO E QUE O APONTADOR DA TAREFA VAI SE PASSADO A FUNCAO
//
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////









#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "ListaTarefas.h"



/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/

// Definicoes do timer do microcontrolador
#define	CLOCKTIME	0.001	// Tempo de tick em segundos (= 1 ms)
#define PRESCALAR	8




/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura do timer
typedef struct
{
	uint16_t periodo;		// Periodo do timer (em mili-segundos)
	uint16_t tActual;		// Tempo actual do timer

	Tarefa_t *tarefa;		// Apontador para a tarefa a que este timer pertence
} Timer_t;


// Vector de timers
typedef struct
{
	Timer_t **timers;
	uint8_t nTimers;
} VectorTimers_t;


/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/

// Vector dos timers criados
extern VectorTimers_t vecTimers;



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa o timer do kernel (ticks).
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Timers_inicia();

/*
 * Termina a actividade do timer do kernel (ticks).
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Timers_termina();



/*
 * Cria um timer com um determinado periodo (em mili-segundos).
 * 
 * @return: Apontador para o timer criado ou NULL em caso de erro.
 */
Timer_t* Timers_criaTimer(Tarefa_t *tarefa, uint16_t periodo);



/*
* Apaga um timer.
*
* @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
*/
int8_t Timers_apagaTimer(Timer_t *timer);



/*
 * Poe a tarefa no estado de sleep ate o timer indicado terminar a temporizacao.
 * Quando o timer terminar, a tarefa volta a ser activada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Timers_esperaActivacao(Timer_t *timer);



/*
* Verifica se um timer ja terminou.
*
* @return: 1 em caso afirmativo e 0 caso contrario.
*/
int8_t Timers_timerTerminado(Timer_t *timer);



#endif
