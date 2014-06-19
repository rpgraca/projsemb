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
#include <stdio.h>
#include "uart.h"
#include <avr/sleep.h>

#define HEAPSIZE	600


Sinal_t *sinal1;
Timer_t *timer;

/*
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
*/

void* func0(void *arg)
{
	//d printf("Entrei na tarefa 0\n");
	int x=0;
	int state=0;
	while(1)
	{
		if(x==(int)arg)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		Timers_esperaActivacao(timer);
		Sinais_sinaliza(sinal1);
	}
}


void* func1(void *arg)
{
	//d printf("Entrei na tarefa 1\n");
	int x=0;
	int state=0;
	while(1)
	{
		if(x==(int)arg)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		delay(2000);
		Sinais_esperaSinal(sinal1);
	}
}


void* func2(void *arg)
{
	//d printf("Entrei na tarefa 2\n");
	int x=0;
	int state=0;
	while(1)
	{
		if(x==(int)arg)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}

void* func3(void *arg)
{
	//d printf("Entrei na tarefa 3\n");
	int x=0;
	int state=0;
	while(1)
	{
		if(x==(int)arg)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}

void* func4(void *arg)
{
	//d printf("Entrei na tarefa 4\n");
	int x=0;
	int state=0;
	while(1)
	{
		if(x==(int)arg)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}

void* func5(void *arg)
{
	//d printf("Entrei na tarefa 5\n");
	int x=0;
	int state=0;
	while(1)
	{
		if(x==(int)arg)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}


/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	Sched_adicionaTarefa(5, 90, func5,(void*)5);
	Sched_adicionaTarefa(5, 90, func4,(void*)4);
	Sched_adicionaTarefa(3, 90, func3,(void*)3);
	Sched_adicionaTarefa(2, 90, func0,(void*)2);
	Sched_adicionaTarefa(2, 90, func2,(void*)1);
	Sched_adicionaTarefa(1, 90, func1,(void*)0);
}




int main()
{
	char * tmpheap = (char *) malloc(HEAPSIZE);
	
	//uart_init();
    //stdout = &uart_output;
    //stdin  = &uart_input;

	//d printf("\n\nolá!\n");
	
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////

	UK_inicializa();
	DDRB = 0xFF;  // Define LED do arduino como saida (PORTB5)
	//if (resultado < 0)
	//{
	//	////d printf("ERRO: a incializar o kernel\n");
	//	exit(-1);
	//}
	
	
	//////////////////// TESTES ////////////////////
	testes();

	timer = Timers_criaTimer(100,6);
	sinal1 = Sinais_criaSinal(6);

	free(tmpheap); /* tmpheap serve para reservar um espaço para a heap das tarefas no inicio da memória
					* o seu tamanho deve ser devidamente calculado e deixado ao critério do programador */

	UK_inicia();	
		
	return 0;
}
