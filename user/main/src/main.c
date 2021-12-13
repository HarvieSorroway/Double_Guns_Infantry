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
		ledX_On(4);
		atest_datas[0].fload_data = 1;//moto_m2006_info.moto_total_angle;
		atest_datas[1].fload_data = 2;//FloatArray_SetAngle[0];
		
		USART_sendFloat(atest_datas,2);
		delay_ms(100);
		ledX_Off(4);
		delay_ms(100);
	}
}
