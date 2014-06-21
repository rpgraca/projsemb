/*****************************************************************************************/
/*                             Sistemas Embarcados 2013/2014                             */
/*                                    Micro-kernel RTS                                   */
/*                                                                                       */
/* Eduardo Nuno Moreira Soares de Almeida	201000641                                    */
/* Rui Pedro Zenhas Graca					201004124                                    */
/* Tiago dos Santos Maia Costa				200601289                                    */
/*****************************************************************************************/
/*                                        External Libs                                  */
/*****************************************************************************************/



#ifndef _EXT_LIBS_H_
#define _EXT_LIBS_H_


/**************************************************************/
/*                         DEFINICOES                         */
/**************************************************************/




/**************************************************************/
/*                          ESTRUTURA                         */
/**************************************************************/

/**************************************************************/
/*		              MACROS                          */
/**************************************************************/

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa ADC
 * Source: http://www.embedds.com/adc-on-atmega328-part-1/
 * 
 */
void InitADC();

/*
 * Faz a leitura do ADC no pino especificado por ADCchannel.
 * 
 * @return: valor amostrado pelo ADC
 */
uint16_t ReadADC(uint8_t ADCchannel);

/*
 * Faz a conversão do valor amostrado pelo ADC para graus Celsius
 * 
 * @return: temperatura em graus Celsius
 */
double temperatura(uint16_t ADC_RAW_value, int16_t VREF);


#endif