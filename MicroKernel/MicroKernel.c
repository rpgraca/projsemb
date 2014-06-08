/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                       Micro-Kernel                                    */
/*****************************************************************************************/



#include "MicroKernel.h"



int UK_inicializa()
{
	int resultado = 0;
	
	
	resultado += Sched_inicia();
	resultado += Disp_inicia();
	
	//////////////////////////
	//////////////////////////
	//////////////////////////
	//
	// ACRESCENTAR A INICIALIZACAO DOS RESTANTES COMPONENTES
	//
	//////////////////////////
	//////////////////////////
	//////////////////////////
	
	return (resultado == 0 ? 0 : -1);
}


int UK_termina()
{
	int resultado = 0;
	
	
	resultado += Sched_apaga();
	resultado += Disp_apaga();
	
	//////////////////////////
	//////////////////////////
	//////////////////////////
	//
	// ACRESCENTAR A TERMINACAO DOS RESTANTES COMPONENTES
	//
	//////////////////////////
	//////////////////////////
	//////////////////////////
	
	return (resultado == 0 ? 0 : -1);
}
