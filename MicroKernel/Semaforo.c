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

#include "Semaforo.h"
#include <stdlib.h>

/**************************************************************/
/*                      FUNCOES AUXILIARES                    */
/**************************************************************/
int8_t Stack_Push(uint8_t var);
int8_t Stack_Pop();

/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
//extern uint8_t* ceilingStack = NULL;
//extern uint8_t ceilingstackSize=0;
uint8_t stackMaxsize;

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa um semáforo.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Semaforo_init(Semaforo_t* semaforo, uint8_t ceiling)
{
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	cli(); // Desativar interrupçoes

	if(semaforo != NULL)
	{
		SREG = tmpstatus;
		return 1;
	}

	semaforo = (Semaforo_t *) malloc(sizeof(Semaforo_t));

	if(semaforo == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}	

	stackMaxsize++;
	ceilingStack = (uint8_t*) realloc(ceilingStack,  stackMaxsize * sizeof(uint8_t));

	if (ceilingStack == NULL)
	{
		free(semaforo);
		SREG = tmpstatus;
		return -2;
	}

	semaforo->estado = UNLOCKED;
	semaforo->ceiling = ceiling;

	SREG = tmpstatus;
	
	return 0;
}


/*
 * Apaga um Semaforo_t, libertando toda a memoria alocada.
 *
 * @return: 0 em caso de sucesso ou um valor negativo em caso de erro.
 */
int8_t Semaforo_apaga(Semaforo_t* semaforo)
{
	uint8_t i, resultado;
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes

	cli(); // Desativar interrupçoes

	// Verificacao dos parametros passados a funcao
	if (semaforo == NULL)
	{
		SREG = tmpstatus;
		return -1;
	}

	// Não deixa apagar semáforo trancado
	if(semaforo->estado == LOCKED)
	{
		SREG = tmpstatus;
		return -1;
	}

	stackMaxsize--;
	if(stackMaxsize == 0)
	{
		free(ceilingStack);
	}	
	else
	{
		ceilingStack = (uint8_t*) realloc(ceilingStack,  stackMaxsize * sizeof(uint8_t));
	}


	// Apaga a estrutura
	free(semaforo);
	SREG = tmpstatus;

	return 0;
}

/*
 * Tranca um semáforo.
 *
 */
void Semaforo_lock(Semaforo_t* semaforo)
{
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	
	cli(); // Desativar interrupçoes
	
	semaforo->estado = LOCKED;
	if(semaforo->ceiling >= System_Ceiling())
	{
		Stack_Push(semaforo->ceiling);
	}
	else
	{
		Stack_Push(System_Ceiling());

	}
	SREG = tmpstatus;
}
/*
 * Liberta um semáforo.
 *
 */
void Semaforo_unlock(Semaforo_t* semaforo)
{
	uint8_t tmpstatus = SREG;	// Guardar estado de interrupçoes
	cli(); // Desativar interrupçoes
	
	semaforo->estado = UNLOCKED;
	Stack_Pop();

	SREG = tmpstatus;
}

int8_t Stack_Push(uint8_t var)
{
	if(ceilingstackSize == stackMaxsize)
	{
		return -1;
	}
	
	ceilingStack[ceilingstackSize] = var;
	ceilingstackSize++;
	return 0;
}

int8_t Stack_Pop()
{
	if(ceilingstackSize == 0)
	{
		return -2;
	}
	ceilingstackSize--;
	return ceilingStack[ceilingstackSize];
}




