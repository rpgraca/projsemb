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

#include <stdio.h>
#include <stdlib.h>




void* funcA(void *arg)
{
	/*
	static int i = 0;

	i++;
	
	if (i == 100)
	{
		PORTB ^= (1 << LEDA);
		i = 0;
	}
	*/


	return NULL;
}

void* funcB(void *arg)
{
	/*
	static int i = 99;
	i++;
	if (i == 100)
	{
		PORTB ^= (1 << LEDB);
		i = 0;
	}
	*/

	
	return NULL;
}




/**************************************************************/
/*                            MAIN                            */
/**************************************************************/
void testes()
{
	int resultado;


	resultado = Sched_adicionaTarefa(0, 100, funcA);
	if (resultado < 0)
		return;


	resultado = Sched_adicionaTarefa(1, 50, funcB);
	if (resultado < 0)
		return;





	/*
	resultado = Sched_removeTarefa();
	if (resultado < 0)
		return;


	resultado = Sched_removeTarefa(1, 50, funcB);
	if (resultado < 0)
		return;
	*/
}




int main()
{
	int resultado;
	
	//////////////////// INICIALIZACAO DO KERNEL ////////////////////

	resultado = UK_inicializa();
	if (resultado < 0)
	{
		printf("ERRO: a incializar o kernel\n");
		exit(-1);
	}
	
	
	//////////////////// TESTES ////////////////////
	testes();
	

	//////////////////// TERMINACAO DO KERNEL ////////////////////

	resultado = UK_termina();
	if (resultado < 0)
	{
		printf("ERRO: a terminar o kernel\n");
		exit(-1);
	}
	
	return 0;
}
