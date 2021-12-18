#include "FreeRTOS.h"
#include "task.h"
#include "start_task.h"

#include "init.h"

#include "led.h"
#include "delay.h"
#include "dbus.h"
#include "usart.h"
#include "pid.h"


send_float datas[2];

float a = 0;
send_float atest_datas[2];

int main(void)
{
	init_all();
	
	create_start_task();
	vTaskStartScheduler();
	
    while(1)
	{
		ledX_On(5);
		atest_datas[0].fload_data = 0;
		atest_datas[1].fload_data = 1;
		USART_sendFloat(atest_datas,2);
		delay_ms(500);
		ledX_Off(5);
		delay_ms(100);
	}
}
