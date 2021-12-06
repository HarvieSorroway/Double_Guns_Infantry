#include "FreeRTOS.h"

#include "init.h"

#include "led.h"
#include "delay.h"
#include "dbus.h"
#include "usart.h"


send_float datas[2];

int main(void)
{
	init_all();
	
    while(1)
	{
		datas[0].fload_data = RC_CtrlData.rc.ch0;
		datas[1].fload_data = RC_CtrlData.rc.ch1;
		USART_sendFloat(datas,2);	
		delay_ms(5);
	}
}
