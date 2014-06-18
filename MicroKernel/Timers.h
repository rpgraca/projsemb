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



#ifndef _TIMERS_H_
#define _TIMERS_H_

#include "ListaTarefas.h"
#include "Context.h"
#include "Scheduler_Fixo.h"



/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/




/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura do timer
typedef struct
{
	uint16_t periodo;		// Periodo do timer (em ticks)
	uint16_t tActual;		// Tempo actual do timer
	uint8_t numTarefas;		// Numero de tarefas que usam o timer
	uint8_t stackSize;		// Numero de tarefas em espera

	Tarefa_t **tarefas;		// Stack de tarefas em espera	
} Timer_t;


// Vector de timers
typedef struct
{
	Timer_t **timers;
	uint8_t nTimers;
} VectorTimers_t;

/**************************************************************/
/*							  MACROS                          */
/**************************************************************/

/*
* Verifica se um timer ja terminou.
*
* @return: 1 em caso afirmativo e 0 caso contrario.
*/
#define Timers_timerTerminado(timer)	((timer==NULL)?-1:(timer->tActual >= timer->periodo))


/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa vetor de timers.
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
 * Cria um timer com um determinado periodo (em ticks).
 * 
 * @return: Apontador para o timer criado ou NULL em caso de erro.
 */
Timer_t* Timers_criaTimer(uint16_t periodo, uint16_t numTarefas);



/*
* Apaga um timer.
*
* @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
*/
int8_t Timers_apagaTimer(Timer_t *timer);



/*
 * Actualiza os timers em uma unidade.
 * Caso os timers terminem, as respectivas tarefas sao activadas e o timer reiniciado.
 */
void Timers_actualizaTimers() __attribute__((naked,signal));



/*
 * Poe a tarefa no estado de sleep ate o timer indicado terminar a temporizacao.
 * Quando o timer terminar, a tarefa volta a ser activada.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Timers_esperaActivacao(Timer_t *timer);


/*
 * Suspende a tarefa por um periodo estabelecido.
 *
 * @param periodo: Periodo de suspensao da tarefa (em ticks).
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Timers_sleep(uint16_t periodo);


#endif
