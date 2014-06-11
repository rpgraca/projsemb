/*
 * GccApplication2.c
 *
 * Created: 11-06-2014 00:30:50
 *  Author: Rui Graça
 */ 
#include "Dispatcher.h"
#include "ListaTarefas.h"

#include <avr/io.h>

ListaTarefas_t * listatarefas;

void * funcA(void * ptr)
{
	int x = 0;
	while(1)
	{
		x++;
		if(x==5)
		{
			listatarefas->prioridades[2]->tarefas[0]->nActivacoes = 1;
			Disp_Dispatch();
		}
	}
	return 0x00;

}

void * funcB(void * ptr)
{
	int x=0x43;
	while(1)
	{
		x--;
		listatarefas->prioridades[2]->tarefas[0]->nActivacoes = 0;
		Disp_Dispatch();
	}
	return 0x00;
}
void funcX(void) __attribute__((signal));
void funcX(void)
{
	int x=2;
	return;
}


int main(void)

{
//	funcX();
	listatarefas = ListaTarefas_cria(3);
	ListaTarefas_adicionaTarefa(listatarefas,1,100,funcA);
	ListaTarefas_adicionaTarefa(listatarefas,2,100,funcB);
	listatarefas->prioridades[1]->tarefas[0]->nActivacoes = 1;
	Disp_Dispatch();
	
    while(1)
    {

    }
}