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




/**************************************************************/
/*                  INTERRUPT HANDLER DO TIMER                */
/**************************************************************/

ISR(TIMER1_COMPA_vect)
{
	// Actualiza os timers

	// NAO ESQUECER QUE SE OS TIMERS CHEGAREM AO FIM TEM DE NOTIFICAR AS TAREFAS
	// A ESPERA E FAZER UM RESET.



	//Sched_Schedule();
	//Disp_Dispatch();
}





/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int8_t UK_inicializa()
{
	int8_t resultado = 0;
	
	
	resultado += Sched_inicia();
	//resultado += Disp_inicia();
	resultado += Timers_inicia();
	
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


int8_t UK_termina()
{
	int8_t resultado = 0;
	
	
	resultado += Sched_apaga();
	//resultado += Disp_apaga();
	resultado += Timers_apaga();

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
