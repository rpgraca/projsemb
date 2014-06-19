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

#define HEAPSIZE	1000


#define LEDA		5
#define LEDB		4
Sinal_t *sinal1;

void* func1(void *arg)
{
	Timer_t *timer = Timers_criaTimer(1000,1);
	int x=0;
	if (timer == NULL)
		return NULL;


	for(x=0;x<31;x++)	
	{


		PORTB ^= (1<< (int) arg);
		Timers_esperaActivacao(timer);
	}


	return NULL;
}


void* func2(void *arg)
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


void* func3(void *arg)
{
	Timers_sleep(2000);
	Timer_t *timer = Timers_criaTimer(150,1);
	while (1)
	{
		PORTB ^= (1<< (int) arg);
		Timers_esperaActivacao(timer);
	}
}

void* func4(void *arg)
{
	while (1)
	{
		Timers_sleep(100);
		PORTB ^= (1<< (int) arg);
	}
}

void* func5(void *arg)
{
	while (1)
	{
		Timers_sleep(100);
		PORTB ^= (1<< (int) arg);
	}
}

void* func6(void *arg)
{

	Timers_sleep(75);
	while (1)
	{
		PORTB ^= (1<< (int) arg);
		//Sinais_sinaliza(sinal1);
		Timers_sleep(405);
	}
}


/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	Sched_adicionaTarefa(3, 90, func1,(void*)5);
	Sched_adicionaTarefa(3, 90, func2,(void*)4);
	Sched_adicionaTarefa(0, 90, func3,(void*)3);
	if(Sched_adicionaTarefa(1, 90, func4,(void*)2))
		PORTB ^= (1<< 2);
	Sched_adicionaTarefa(0, 90, func5,(void*)1);
	Sched_adicionaTarefa(0, 90, func6,(void*)0);
}




int main()
{
	char * tmpheap = (char *) malloc(HEAPSIZE);
	
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////

	UK_inicializa();
	DDRB = 0xFF;  // Define LED do arduino como saida (PORTB5)
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
		
	return 0;
}
