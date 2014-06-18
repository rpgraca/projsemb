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

/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/

// Definicoes do timer do microcontrolador
#define	CLOCKTIME	0.001	// Tempo de tick em segundos (= 1 ms)
#define PRESCALAR	8

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Inicia interrupção do tick
 */
void ATmega_iniciaTick();

#endif
