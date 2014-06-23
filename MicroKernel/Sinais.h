/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                        Sinais                                         */
/*****************************************************************************************/



#ifndef _SINAIS_H_
#define _SINAIS_H_

#include "ListaTarefas.h"
#include "Scheduler_Fixo.h"



/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/




/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

// Estrutura do sinal
typedef struct
{
	uint8_t numTarefas;		// Numero de tarefas que usam o sinal
	uint8_t stackSize;		// Numero de tarefas em espera

	Tarefa_t **tarefas;		// Stack de tarefas em espera	
} Sinal_t;



/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/


/*
 * Cria um sinal 
 * 
 * @return: Apontador para o sinal criado ou NULL em caso de erro.
 */
Sinal_t* Sinais_criaSinal(uint16_t numTarefas);


/*
* Apaga um sinal.
*
* @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
*/
int8_t Sinais_apagaSinal(Sinal_t *sinal);

/*
 * Poe a tarefa no estado de sleep ate ser sinalizada 
 * 
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Sinais_esperaSinal(Sinal_t *sinal);

/* 
 * Sinaliza 
 *
 */  
int8_t Sinais_sinaliza(Sinal_t *sinal);

#endif
