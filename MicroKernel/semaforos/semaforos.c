/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                      Semáforos                                       */
/*****************************************************************************************/


//#include <avr/io.h>
#include <stdio.h>
#include "semaforos.h"


/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/


int8_t Semaf_inicia(uint8_t id_semaf) {
 
  if(lista_semaf[id_semaf] == 0)
    return (int8_t) id_semaf;
  else
    return -1;
}


/*
uint8_t Semaf_libertar(uint8_t id_semaf){
  
    return 0;
}
*/

int8_t Semaf_ler(uint8_t id_semaf){
 
  if(lista_semaf[id_semaf] > 127){
   return -1; //semaforo bloqueado para escrita
  }
  
  if(lista_semaf[id_semaf] < 127){
    lista_semaf[id_semaf]++;
  }
  return (int8_t) lista_semaf[id_semaf];
}


int8_t Semaf_ler_liber(uint8_t id_semaf)
{
 if((lista_semaf[id_semaf] > 0) && (lista_semaf[id_semaf] != 128)){  //lista_semaf[id_semaf] & 0b10000000
   
   lista_semaf[id_semaf] = lista_semaf[id_semaf] -1;
        
   if(lista_semaf[id_semaf] < 128)
      return (int8_t) lista_semaf[id_semaf];
   else
     return (int8_t) (lista_semaf[id_semaf]-128);
}
 else{
    return -1;
 }
}

//neste momento só permite bloquear para escrita caso não haja bloqueios de leitura
//pode ser alterado para dar prioridade à operação de escrita
//ou em alternativa, pode antes ser usado semaf_inicia() para fazer reset ao semáforo
int8_t Semaf_escrever(uint8_t id_semaf){
  
  if((lista_semaf[id_semaf] == 0)){      
   
    lista_semaf[id_semaf] = 128;
    
    return 0;
 }
 else
   return -1;
}

int8_t Semaf_escrever_liber(uint8_t id_semaf){
 
  if((lista_semaf[id_semaf] > 127)){      
   
    lista_semaf[id_semaf] = lista_semaf[id_semaf] - 128;
    
    return 0;
 }
 else
   return -1;
}


/*
* Permite ao scheduler / dispatcher consultar o estado de um semáforo antes de escalonar determinada tarefa
*
* @return: 0       - semáforo livre para leitura ou escrita
*	   {1;127} - semáforo livre para leitura
* 	   >128    - semáforo bloqueado para leitura e escrita
*/
int8_t Semaf_estado(uint8_t id_semaf){
  
  if(lista_semaf[id_semaf] < 128)
    return (int8_t) lista_semaf[id_semaf];
  else 
    return -1;
    
}
