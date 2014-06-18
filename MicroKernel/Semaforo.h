/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                            Semáforos (Stack Resource Protocol)                        */
/*****************************************************************************************/


#ifndef _SEMAFORO_H_
#define _SEMAFORO_H_

#include <avr/io.h>
#include <stdlib.h>

/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/
#define LOCKED		1
#define UNLOCKED	0


/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

typedef struct
{
	uint8_t ceiling;
	uint8_t estado;
} Semaforo_t;

/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
extern uint8_t* ceilingStack;
extern uint8_t ceilingstackSize;

/**************************************************************/
/*                            MACROS                          */
/**************************************************************/
/*
 * Retorna valor no topo da stack (ceiling do sistema)
 *
 */
#define System_Ceiling() (ceilingstackSize == 0?-1:ceilingStack[ceilingstackSize - 1])

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa um semáforo.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Semaforo_init(Semaforo_t* semaforo, uint8_t ceiling);

/*
 * Tranca um semáforo.
 *
 */
void Semaforo_lock(Semaforo_t* semaforo);

/*
 * Liberta um semáforo.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
void Semaforo_unlock(Semaforo_t* semaforo);



#endif
