#ifndef __USART_H
#define __USART_H

#include "stm32f4xx_conf.h"


typedef union send
{
	float fload_data;
	uint8_t bits[4];
}send_float;

void UART8_init(void);
void USART6_init(void);

void USART_sendFloat(send_float * ,int);
void sendD(uint8_t ch);

#endif
