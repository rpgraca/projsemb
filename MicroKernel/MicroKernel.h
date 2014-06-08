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



#include "Scheduler_Fixo.h"
#include "Dispatcher.h"


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
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Inicializa o micro-kernel.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
uint8_t UK_inicializa();


/*
 * Termina o micro-kernel.
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
uint8_t UK_termina();


#endif