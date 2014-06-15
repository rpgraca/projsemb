/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                      Dispatcher                                       */
/*****************************************************************************************/



#ifndef _DISPATCHER_H_
#define _DISPATCHER_H_



#include "Scheduler_Fixo.h"
#include "Context.h"


/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
* Incializa o dispatcher.
*
* @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
*/
//uint8_t Disp_inicia();


/*
* Apaga o dispatcher, libertando toda a memoria alocada.
*
* @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
*/
//uint8_t Disp_termina();


/*
 * Verifica se existe alguma tarefa de maior prioridade com activacoes
 * pendentes e, caso haja, activa-a (aloca os recursos do sistema para a
 * tarefa).
 */
void Disp_dispatch() __attribute__((naked,signal));



#endif