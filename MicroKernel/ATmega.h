/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                        ATmega                                         */
/*****************************************************************************************/

#ifndef _ATMEGA_H_
#define _ATMEGA_H_

#include "Context.h"
#include <stdlib.h>
#include <avr/io.h>

/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/

// Definicoes do timer do microcontrolador
#define	CLOCKTIME	0.005	// Tempo de tick em segundos 
#define PRESCALAR	16
//#define F_CPU		16000000
/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Inicia interrupção do tick
 */
void ATmega_iniciaTick();

#endif
