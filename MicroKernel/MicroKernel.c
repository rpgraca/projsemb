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


ListaTarefas_t * listatarefas;

Tarefa_t * tarefaAtual = NULL;
char *stackptrAtual = NULL;
char *stackptrIdle = NULL;
void * (*funcAtual)(void*) = NULL;
 
uint8_t* ceilingStack = NULL;
uint8_t ceilingstackSize = 0;


/**************************************************************/
/*                  INTERRUPT HANDLER DO TIMER                */
/**************************************************************/

ISR(TIMER1_COMPA_vect,ISR_NAKED)
{
	cli();
	Timers_actualizaTimers();
	Sched_dispatch();
	asm volatile("reti");
}





/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

int8_t UK_inicializa()
{
	int8_t resultado = 0;

	
	ATmega_iniciaTick();	
	resultado += ATmega_idleStackptr();
	resultado += Sched_inicia();
	//resultado += Timers_inicia();
	
					
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

void UK_inicia()
{
	Sched_dispatch();
}


int8_t UK_termina()
{
	int8_t resultado = 0;
	
	
	resultado += Sched_termina();

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
