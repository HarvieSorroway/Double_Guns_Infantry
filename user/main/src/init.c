//��ʼ��������Ҫ��ʼ���ĺ���

#include "init.h"

#include "delay.h"
#include "led.h"
#include "dbus.h"
#include "usart.h"


void init_all()
{
	delay_init(180);
	ledX_init();
	RC_Init();
	UART8_init();
}
