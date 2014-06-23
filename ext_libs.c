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


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

#include "ext_libs.h"



/**************************************************************/
/*                      VARIAVEIS GLOBAIS                     */
/**************************************************************/

/**************************************************************/
/*                           FUNCOES                          */
/**************************************************************/

/*
 * Incializa ADC
 * Source: http://www.embedds.com/adc-on-atmega328-part-1/
 * 
 */
void InitADC() {
	// Select Vref=AVcc
	ADMUX |= (1<<REFS0);
	//set prescaller to 128 and enable ADC 
	ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN); 
}

/*
 * Faz a leitura do ADC no pino especificado por ADCchannel.
 * Source: http://www.embedds.com/adc-on-atmega328-part-1/
 * @return: valor amostrado pelo ADC
 */
uint16_t ReadADC(uint8_t ADCchannel) {
  
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
	//single conversion mode
	ADCSRA |= (1<<ADSC);
	// wait until ADC conversion is complete
	while( ADCSRA & (1<<ADSC) );
	
	return ADC;
}

/*
 * Faz a conversão do valor amostrado pelo ADC para graus Celsius
 * 
 * @return: temperatura em graus Celsius
 */
double temperatura(uint16_t ADC_RAW_value, int16_t VREF) {
  
  return 100*(double)VREF/1024*(double)ADC_RAW_value;
}

/*
 * Introduz um delay especificado em ms
 * 
 */
void delay_ms(uint16_t ms){
 
  uint16_t i=0;
  uint16_t j=0;
 
  for(i=0;i<(double)ms*0.1;i++) 
   for(j=0;j<8335;j++); 
  
}