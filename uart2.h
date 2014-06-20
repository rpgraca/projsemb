#include <stdio.h>
#include <math.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#define USART_BAUDRATE 2000000
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
void USART0Init(void);
int USART0SendByte(char u8Data, FILE *stream);
int USART0ReceiveByte(FILE *stream);
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, USART0ReceiveByte, _FDEV_SETUP_RW);
