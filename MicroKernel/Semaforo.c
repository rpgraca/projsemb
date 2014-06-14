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
Stack_t* ceilingStack = NULL;


/**************************************************************/
/*						ESTRUTURA  (ceilingStack)			  */
/**************************************************************/

typedef struct
{
	uint8_t* stack;
	uint8_t size;
	uint8_t maxsize;
} Stack_t;

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

	// ceilingStack tem sempre um tamanho máximo igual ao número de semáforos no sistema
	if(ceilingStack == NULL)
	{
		ceilingStack = (Stack_t*) malloc(sizeof(Stack_t));
		ceilingStack->size=0;
		ceilingStack->maxsize=1;
		ceilingStack->stack = (uint8_t*) malloc(sizeof(uint8_t));
	}
	else
	{
		ceilingStack->maxsize++;
		ceilingStack->stack = (uint8_t*) malloc(ceilingStack->stack,  (ceilingStack->maxsize) * sizeof(uint8_t));
	}

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

	ceilingStack->maxsize--;	


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
	if(semaforo->ceiling == System_Ceiling())
	{
		Stack_Pop();
	}
	sei();
}

int8_t Stack_Push(uint8_t var)
{
	if(ceilingStack->size == ceilingStack->maxsize)
	{
		return -1;
	}
	
	ceilingStack->stack[ceilingStack->size] = var;
	ceilingStack->size++;
	return 0;
}

int8_t Stack_Pop(Stack_t stack)
{
	if(ceilingStack == NULL)
	{
		return -1;
	}
	if(ceilingStack->size == 0)
	{
		return -2;
	}
	ceilingStack->size--;
	return ceilingStack[ceilingStack->size];
}

/*
 * Lê valor no topo da stack (ceiling do sistema)
 *
 * @return: ceiling atual do sistema
 */
uint8_t System_Ceiling()
{
	if(ceilingStack == NULL)
	{
		return -1;
	}
	if(ceilingStack->size == 0)
	{
		return -1;
	}
	return ceilingStack->stack[ceilingStack->size - 1];
}

