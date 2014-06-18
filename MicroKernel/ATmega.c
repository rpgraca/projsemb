/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                        ATmega                                         */
/*****************************************************************************************/

#include "ATmega.h"

void * ATmega_idleMode(void *);


/**************************************************************/
/*                       VARIAVEIS GLOBAIS                    */
/**************************************************************/
extern char *stackptrIdle;
extern char *stackptrAtual;
extern char *stackptrBak;
/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/
void ATmega_iniciaTick()
{
	OCR1A = (unsigned int) ((F_CPU/PRESCALAR)*CLOCKTIME);

	TCCR1B |= (1 << WGM12);  // Mode 4, CTC on OCR1A

	TIMSK1 |= (1 << OCIE1A); //Set interrupt on compare match

	// Iniciar timer com prescaler definido devidamente
	switch(PRESCALAR)
	{
	case 1:		TCCR1B |= (1 << CS10);
	break;
	case 8:		TCCR1B |= (1 << CS11);
	break;
	case 16:	TCCR1B |= (1 << CS11) | (1 << CS10);
	break;
	case 256:	TCCR1B |= (1 << CS12);
	break;
	case 1024:	TCCR1B |= (1 << CS12) | (1 << CS10);
	break;
	}
}

int8_t ATmega_idleStackptr()
{
	stackptrIdle = (char *) malloc(sizeof(char*));

	// Cria o contexto da tarefa
	GUARDARSTACKPTR();
	stackptrBak = stackptrAtual;
	stackptrAtual = stackptrIdle;
	funcAtual = ATmega_idleMode;	
	CRIARCONTEXTO();

	// Troca Bak e Atual
	stackptrBak = (char *) ((uint16_t) stackptrAtual ^ (uint16_t) stackptrBak);
	stackptrAtual = (char *) ((uint16_t) stackptrAtual ^ (uint16_t) stackptrBak);
	stackptrBak =  (char *) ((uint16_t) stackptrAtual ^ (uint16_t) stackptrBak);
	
	RECUPERARSTACKPTR();
	stackptrIdle = stackptrBak-2;
	return 0;
}

void * ATmega_idleMode(void * x)
{
	// Põe CPU em Idle Mode
	while(1)
	{
		MCUCR &= ~(1 << SM2) & ~(1 << SM1) & ~(1 << SM0); 
	}
}
