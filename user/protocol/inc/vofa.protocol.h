#ifndef __VOFA_PROTOCOL_H
#define __VOFA_PROTOCOL_H

#include "stdio.h"
#include "stm32f4xx_conf.h"

void vofa_firewater_output(float data1,float data2,float data3);
void vofa_justfloat_output(float *data,uint8_t num); 

#endif
