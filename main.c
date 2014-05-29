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


/**************************************************************/
/*                            MAIN                            */
/**************************************************************/

int main()
{
	int resultado;
	
	resultado = UK_inicializa();
	if (resultado < 0)
	{
		printf("ERRO: a incializar o kernel\n");
		exit(-1);
	}
	
	
	
	
	// (...)
	
	
	
	resultado = UK_termina();
	if (resultado < 0)
	{
		printf("ERRO: a terminar o kernel\n");
		exit(-1);
	}
	
	return 0;
}
