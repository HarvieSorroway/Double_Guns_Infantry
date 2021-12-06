#ifndef __DBUS_H
#define __DBUS_H

#include "stm32f4xx_conf.h"

typedef __packed struct  
{
	__packed struct 
	{
		uint16_t ch0;
		uint16_t ch1;
		uint16_t ch2;
		uint16_t ch3;
		uint8_t s1;
		uint8_t s2;
	}rc;
	__packed struct 
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t press_l;
		uint8_t press_r;
	}mouse;
	
	__packed struct 
	{
		uint16_t v;
	}key;
	
}RC_Ctl_t;

extern RC_Ctl_t RC_CtrlData;

void RC_Init(void);
void RemoteDataProcess(uint8_t *pData);

#endif
