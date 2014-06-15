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

/**************************************************************/
/*                      FUNCOES AUXILIARES                    */
/**************************************************************/
int8_t Stack_Push(uint8_t var);
int8_t Stack_Pop();



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/
uint8_t* ceilingStack = NULL;
uint8_t stackSize=0;
uint8_t stackMaxsize=0;



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
	cli();
	if(semaforo != NULL)
	{
		sei();
		return 1;
	}

	semaforo = (Semaforo_t *) malloc(sizeof(Semaforo_t));

	if(semaforo == NULL)
	{
		sei();
		return -1;
	}	

	stackMaxsize++;
	ceilingStack = (uint8_t*) realloc(ceilingStack,  stackMaxsize * sizeof(uint8_t));

	if (ceilingStack == NULL)
	{
		free(semaforo);
		sei();
		return -2;
	}

	semaforo->estado = UNLOCKED;
	semaforo->ceiling = ceiling;

	sei();
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

	cli();

	// Verificacao dos parametros passados a funcao
	if (semaforo == NULL)
	{
		sei();
		return -1;
	}

	// Não deixa apagar semáforo trancado
	if(semaforo->estado == LOCKED)
	{
		sei();
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
	sei();

	return 0;
}

/*
 * Tranca um semáforo.
 *
 */
void Semaforo_lock(Semaforo_t* semaforo)
{
	cli();
	semaforo->estado = LOCKED;
	if(semaforo->ceiling >= System_Ceiling())
	{
		Stack_Push(semaforo->ceiling);
	}
	else
	{
		Stack_Push(System_Ceiling());
	}
	sei();
}
/*
 * Liberta um semáforo.
 *
 */
void Semaforo_unlock(Semaforo_t* semaforo)
{
	cli();
	semaforo->estado = UNLOCKED;
	Stack_Pop();
	sei();
}

int8_t Stack_Push(uint8_t var)
{
	if(stackSize == stackMaxsize)
	{
		return -1;
	}
	
	ceilingStack[stackSize] = var;
	stackSize++;
	return 0;
}

int8_t Stack_Pop()
{
	if(stackSize == 0)
	{
		return -2;
	}
	stackSize--;
	return ceilingStack[stackSize];
}

/*
 * Lê valor no topo da stack (ceiling do sistema)
 *
 * @return: ceiling atual do sistema
 */
uint8_t System_Ceiling()
{
	if(stackSize == 0)
	{
		return -1;
	}
	return ceilingStack[stackSize - 1];
}

