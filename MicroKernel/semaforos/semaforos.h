/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                */
/* Rui Pedro Zenhas Graca		        201004124                                */
/* Tiago dos Santos Maia Costa			200601289                                */
/*****************************************************************************************/
/*                                      Semáforos                                        */
/*****************************************************************************************/



#ifndef _SEMAFOROS_H_
#define _SEMAFOROS_H_

/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/
#include <stdint.h>

// este define devera ser alterado conforme o nº maximo de semaforos a serem necessarios em simultaneo
// poderia ser possível alocar os semaforos com malloc mas, uma vez que o nº é conhecido em compile time,
// a memoria nao fica fragmentada se forem alocados logo de inicio
#define numero_semaforos 20

//array que armazena todos os id_semaf a serem criados
uint8_t lista_semaf[numero_semaforos]= {0};

//nao são usadas filas de espera para prevenir busy waiting e para dar hipotese à tarefa
// de continuar mesmo que nao obtenha o semáforo

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
* Incializa (faz reset) a um semáforo em memória.
*
* @return: identificador único do semáforo (valor positivo) ou valor negativo em caso de erro.
*/
int8_t Semaf_inicia(uint8_t id_semaf);


//Função apenas necessária em caso de utilização de malloc/realloc na inicialização de semáforos
/*
* Liberta um semáforo em memória.
*
* @return: identificador único do semáforo libertado (valor positivo) ou valor negativo em caso de erro.
*/
/*uint8_t Semaf_libertar(uint8_t id_semaf);*/


/*
* Bloqueia o semáforo para leitura
*
* @return: número de bloqueios de leitura do semáforo (valor positivo) ou um valor negativo em caso de erro.
*/
int8_t Semaf_ler(uint8_t id_semaf);

/*
* Liberta o semáforo (leitura)
*
* @return: número de bloqueios de leitura do semáforo (valor positivo) ou um valor negativo em caso de erro.
*/
int8_t Semaf_ler_liber(uint8_t id_semaf);

/*
* Bloqueia o semáforo para escrita
*
* @return: 0 em caso de sucesso ou -1 em caso de erro.
*/
int8_t Semaf_escrever(uint8_t id_semaf);

/*
* Liberta o semáforo (escrita)
*
* @return: 0 em caso de sucesso ou -1 em caso de erro.
*/
int8_t Semaf_escrever_liber(uint8_t id_semaf);


/*
* Permite ao scheduler / dispatcher consultar o estado de um semáforo antes de escalonar determinada tarefa
*
* @return: 0       - semáforo livre para leitura ou escrita
*	   {1;127} - semáforo livre para leitura
* 	   -1      - semáforo bloqueado para leitura e escrita
*/
int8_t Semaf_estado(uint8_t id_semaf);

#endif