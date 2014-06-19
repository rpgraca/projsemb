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

/**************************************************************/
/*                       VARIAVEIS GLOBAIS                    */
/**************************************************************/
extern char *stackptrIdle;
extern char *stackptrAtual;
extern char *stackptrBak;
extern void *(*funcAtual)(void*);
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

