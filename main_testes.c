/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                           Programa de testes do micro-kernel                          */
/*****************************************************************************************/




#include "MicroKernel/MicroKernel.h"

#include <stdlib.h>
#include <avr/sleep.h>

#define HEAPSIZE	600


#define LEDA		5
#define LEDB		4

void* funcA(void *arg)
{
	Timer_t *timer = Timers_criaTimer(1000,1);

	if (timer == NULL)
		return NULL;


	while (1)
	{


		PORTB ^= (1<< (int) arg);
		Timers_esperaActivacao(timer);
	}


	return NULL;
}


void* funcB(void *arg)
{
	Timer_t *timer = Timers_criaTimer(250,1);

	if (timer == NULL)
		return NULL;


	while (1)
	{


		PORTB ^= (1<< (int) arg);

		Timers_esperaActivacao(timer);
	}

	
	return NULL;
}


void* funcC(void *arg)
{
	while (1)
	{



	}

	
}


/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	int resultado;


	resultado = Sched_adicionaTarefa(2, 150, funcA,5);
	if (resultado < 0)
		return;


	resultado = Sched_adicionaTarefa(1, 150, funcB,4);
	if (resultado < 0)
		return;
	
//	resultado = Sched_adicionaTarefa(0, 50, funcC);
}




int main()
{
	int resultado;
	char * tmpheap = (char *) malloc(HEAPSIZE);
	
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////

	resultado = UK_inicializa();
	DDRB = 0xFF;  // Define LED do arduino como saida (PORTB5)
	PORTB ^= (1<<3);
	//if (resultado < 0)
	//{
	//	//printf("ERRO: a incializar o kernel\n");
	//	exit(-1);
	//}
	
	
	//////////////////// TESTES ////////////////////
	testes();

	free(tmpheap); /* tmpheap serve para reservar um espaço para a heap das tarefas no inicio da memória
					* o seu tamanho deve ser devidamente calculado e deixado ao critério do programador */

	UK_inicia();	
		PORTB ^= (1<<0);
}
