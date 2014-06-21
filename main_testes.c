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


//1 void* func0(void *arg)
//1 {
//1 	Timer_t *timer = Timers_criaTimer(50,1);
//1 	int x=0;
//1 	if (timer == NULL)
//1 		return NULL;
//1 
//1 	for(x=0;x<31;x++)	
//1 	{
//1 		PORTB ^= (1<< (int) arg);
//1 		Timers_esperaActivacao(timer);
//1 	}
//1 
//1 	return NULL;
//1 }
//1 
//1 
//1 void* func1(void *arg)
//1 {
//1 	Timer_t *timer = Timers_criaTimer(25,1);
//1 
//1 	while (1)
//1 	{
//1 		PORTB ^= (1<< (int) arg);
//1 		Timers_esperaActivacao(timer);
//1 	}
//1 
//1 	
//1 	return NULL;
//1 }
//1 
//1 
//1 void* func2(void *arg)
//1 {
//1 	while (1)
//1 	{
//1 		PORTB ^= (1<< (int) arg);
//1 		Sinais_esperaSinal(sinal1);
//1 	}
//1 }
//1 
//1 void* func3(void *arg)
//1 {
//1 	while (1)
//1 	{
//1 		Timers_sleep(10);
//1 		PORTB ^= (1<< (int) arg);
//1 	}
//1 }
//1 
//1 void* func4(void *arg)
//1 {
//1 	while (1)
//1 	{
//1 		Timers_sleep(10);
//1 		PORTB ^= (1<< (int) arg);
//1 	}
//1 }
//1 
//1 void* func5(void *arg)
//1 {
//1 
//1 	Timers_sleep(10);
//1 	while (1)
//1 	{
//1 		PORTB ^= (1<< (int) arg);
//1 		Sinais_sinaliza(sinal1);
//1 		Timers_sleep(40);
//1 	}
//1 }
//Semaforo_t* sem;
void* funcHOLD(void *arg)
{
	while(1);
}

void* func0(void *arg)
{
	//d printf("Entrei na tarefa 0\n");
 	Timer_t *timer = Timers_criaTimer(75,1);
	int x=0;
	int state=0;
	PORTB ^= (1<< (int) arg);
	while(1)
	{

		//Semaforo_lock(sem);
		//printf("Tarefa 0\n");
		//Semaforo_unlock(sem);

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

		//Semaforo_lock(sem);
		//printf("Tarefa 0\n");
		//Semaforo_unlock(sem);
		if(x==1)
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


void* func2(void *arg)
{
	//d printf("Entrei na tarefa 2\n");
	int x=0;
	int state=0;
	while(1)
	{

		//Semaforo_lock(sem);
		//printf("Tarefa 2\n");
		//Semaforo_unlock(sem);
		////Semaforo_lock(sem);
		if(x==2)
		{
			PORTB ^= (1<< (int) arg);
		}
		if(state==0) x++;
		else x--;
		if(x==6 || x == 0)
		{
			state=1-state;
		}
		////Semaforo_unlock(sem);
		Sinais_esperaSinal(sinal1);
	}
}

void* func3(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 3\n");
		//Semaforo_unlock(sem);
		if(x==3)
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
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==4)
		{
			PORTB ^= (1<< (uint8_t) arg);
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

void* func55(void *arg)
{
	PORTB ^= (1<< (int) arg);
	return NULL;
}

void* func5(void *arg)
{
	//d printf("Entrei na tarefa 5\n");
	int x=0;
	int state=0;
	while(1)
	{
		//printf("Tarefa 5\n");
		if(x==5)
		{
			ListaTarefas_adicionaTarefa(1, 140, func55,(void*)5);
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
	ListaTarefas_adicionaTarefa(5, 140, func5,(void*)5);
	ListaTarefas_adicionaTarefa(5, 140, func4,(void*)4);
	ListaTarefas_adicionaTarefa(5, 140, func3,(void*)3);
	ListaTarefas_adicionaTarefa(4, 140, func2,(void*)2);
	ListaTarefas_adicionaTarefa(4, 140, func1,(void*)1);
	ListaTarefas_adicionaTarefa(3, 140, func0,(void*)0);
}




int main()
{
	
	//PORTB ^= (1<< (int) 2);

	//////////////////// INICIALIZACAO DO KERNEL ////////////////////
	UK_inicializa();
	
	DDRB = 0xFF; 
	//if (resultado < 0)
	//{
	//	////d printf("ERRO: a incializar o kernel\n");
	//	exit(-1);
	//}
	
	
	//////////////////// TESTES ////////////////////
	testes();

	sinal1 = Sinais_criaSinal(5);
	//Semaforo_init(&sem,4);

	UK_inicia();	
		
	return 0;
}
