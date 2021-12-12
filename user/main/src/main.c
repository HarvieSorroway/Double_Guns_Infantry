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

int main(void)
{
	init_all();
	
	create_start_task();
	vTaskStartScheduler();
	
    while(1)
	{
		
	}
}
