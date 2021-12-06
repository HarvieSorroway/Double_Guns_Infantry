#ifndef __LED_H
#define __LED_H

#include "stm32f4xx_conf.h"
#include "math.h"
#include "delay.h"

void ledX_init(void);
void ledX_On(uint16_t);
void ledX_Off(uint16_t);
void ledX_Clear(void);
void ledX_cmd(uint16_t);

void ledX_light(uint16_t);

#endif
