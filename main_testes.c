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

#define HEAPSIZE	600


#define LEDA		5
#define LEDB		4

void* funcA(void *arg)
{
	Timer_t *timer = Timers_criaTimer(50,1);

	if (timer == NULL)
		return NULL;


	while (1)
	{


		PORTB ^= (1<<LEDA);
		Timers_esperaActivacao(timer);
	}


	return NULL;
}


void* funcB(void *arg)
{
	Timer_t *timer = Timers_criaTimer(25,1);

	if (timer == NULL)
		return NULL;


	while (1)
	{


		PORTB ^= (1<<LEDB);

		Timers_esperaActivacao(timer);
	}

	
	return NULL;
}




/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	int resultado;


	resultado = Sched_adicionaTarefa(0, 150, funcA);
	if (resultado < 0)
		return;


	resultado = Sched_adicionaTarefa(1, 150, funcB);
	if (resultado < 0)
		return;
}




int main()
{
	int resultado;
	char * tmpheap = (char *) malloc(HEAPSIZE);
	
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////

	resultado = UK_inicializa();
	//if (resultado < 0)
	//{
	//	//printf("ERRO: a incializar o kernel\n");
	//	exit(-1);
	//}
	
	
	//////////////////// TESTES ////////////////////
	DDRB = (1<<LEDA) | (1<<LEDB);  // Define LED do arduino como saida (PORTB5)
	testes();

	free(tmpheap); /* tmpheap serve para reservar um espaço para a heap das tarefas no inicio da memória
					* o seu tamanho deve ser devidamente calculado e deixado ao critério do programador */

	sei();

	while(1);
	//////////////////// TERMINACAO DO KERNEL ////////////////////

	//resultado = UK_termina();
	//if (resultado < 0)
	//{
	//	//printf("ERRO: a terminar o kernel\n");
	//	exit(-1);
	//}
	
	return 0;
}
