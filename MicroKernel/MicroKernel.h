/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                       Micro-Kernel                                    */
/*****************************************************************************************/



#ifndef _MICROKERNEL_H_
#define _MICROKERNEL_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include "Scheduler_Fixo.h"
#include "Timers.h"
#include "Sinais.h"
#include "Semaforo.h"
#include "ATmega.h"


//////////////////////////
//////////////////////////
//////////////////////////
//
// ACRESCENTAR OS INCLUDES DOS RESTANTES COMPONENTES
//
//////////////////////////
//////////////////////////
//////////////////////////


/**************************************************************/
/*							DEFINICOES                        */
/**************************************************************/

#define UK_inicializa() char * tmpheap = (char *) malloc(HEAPSIZE); ATmega_iniciaTick();	Sched_inicia()
#define UK_inicia()	free(tmpheap); Sched_dispatch()

/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/

//Scheduler_t *scheduler;		// Apontador para o scheduler
//VectorTimers_t vecTimers;	// Vector dos timers criados




/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Inicializa o micro-kernel.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
//int8_t UK_inicializa();
	

/*
 * Termina o micro-kernel.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t UK_termina();


//void UK_inicia();


#endif
