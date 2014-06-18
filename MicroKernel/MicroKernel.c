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
	Timers_actualizaTimers();
	Sched_Schedule();
	Sched_Dispatch();
}





/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int8_t UK_inicializa()
{
	int8_t resultado = 0;
	
	ATmega_iniciaTick();	
	resultado += Sched_inicia();
	resultado += Timers_inicia();
	sei();	
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
