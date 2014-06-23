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

void *func0(void *arg);
void *func1(void *arg);
void *func2(void *arg);
void *func3(void *arg);
void *func4(void *arg);
void *func5(void *arg);
void *func6(void *arg);
void *func7(void *arg);
void *func8(void *arg);
void *func9(void *arg);
void *func10(void *arg);
void *func11(void *arg);
void *func12(void *arg);
void *func13(void *arg);
void *func132(void *arg);


void* func0(void *arg)
{
	//d printf("Entrei na tarefa 0\n");
 	Timer_t *timer = Timers_criaTimer(20,1);
	int x=0;
	int state=0;
	PORTB ^= (1<< (int) arg);
	ListaTarefas_adicionaTarefa(5, 70, func11,(void*)2);
	ListaTarefas_adicionaTarefa(3, 70, func12,(void*)1);
	ListaTarefas_adicionaTarefa(4, 70, func13,(void*)0);
	while(1)
	{

		//Semaforo_lock(sem);
		//printf("Tarefa 0\n");
		//Semaforo_unlock(sem);

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
			PORTB ^= (1<< (int)arg);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
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
			PORTB ^= (1<< 3);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
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
			PORTB ^= (1<<2);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
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
			PORTB ^= (1<< (uint8_t) 1);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
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
		//printf("Tarefa 5\n");
		if(x==5)
		{
			PORTB ^= (1<< 0);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}

void* func6(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==6)
		{
			PORTD ^= (1<< (uint8_t) 7);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}
void* func7(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==7)
		{
			PORTD ^= (1<< 6);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}
void* func8(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==8)
		{
			PORTD ^= (1<< 5);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}
void* func9(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==9)
		{
			PORTD ^= (1<< 4);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state; } Sinais_esperaSinal(sinal1); } }
void* func10(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==10)
		{
			PORTD ^= (1<< 3);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}
void* func11(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==11)
		{
			PORTD ^= (1<< 2);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}
void* func12(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==12)
		{
			PORTD ^= (1<< 1);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}
void* func13(void *arg)
{
	int x=0;
	int state=0;
	while(1)
	{
		//Semaforo_lock(sem);
		//printf("Tarefa 4\n");
		//Semaforo_unlock(sem);
		if(x==13)
		{
			ListaTarefas_adicionaTarefa(4,50,func132,NULL);
		}
		if(state==0) x++;
		else x--;
		if(x==14 || x == 0)
		{
			state=1-state;
		}
		Sinais_esperaSinal(sinal1);
	}
}

void * func132(void *arg)
{
			PORTD ^= (1<< 0);
}


/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	ListaTarefas_adicionaTarefa(5, 70, func0,(void*)5);
	ListaTarefas_adicionaTarefa(3, 70, func1,(void*)4);
	ListaTarefas_adicionaTarefa(4, 70, func2,(void*)3);
	ListaTarefas_adicionaTarefa(5, 70, func3,(void*)2);
	ListaTarefas_adicionaTarefa(5, 70, func4,(void*)1);
	ListaTarefas_adicionaTarefa(5, 70, func5,(void*)0);
	ListaTarefas_adicionaTarefa(3, 70, func6,(void*)7);
	ListaTarefas_adicionaTarefa(4, 70, func7,(void*)6);
	ListaTarefas_adicionaTarefa(4, 70, func8,(void*)5);
	ListaTarefas_adicionaTarefa(5, 70, func9,(void*)4);
	ListaTarefas_adicionaTarefa(5, 70, func10,(void*)3);
}




int main()
{
	
	//PORTB ^= (1<< (int) 2);

	//////////////////// INICIALIZACAO DO KERNEL ////////////////////
	UK_inicializa();
	
	DDRB = 0xFF; 
	DDRD = 0xFF; 
	//if (resultado < 0)
	//{
	//	////d printf("ERRO: a incializar o kernel\n");
	//	exit(-1);
	//}
	
	
	//////////////////// TESTES ////////////////////
	testes();

	sinal1 = Sinais_criaSinal(14);
	//Semaforo_init(&sem,4);

	UK_inicia();	
		
	return 0;
}
