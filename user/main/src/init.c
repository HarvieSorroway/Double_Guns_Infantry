//初始化所有需要初始化的函数

#include "init.h"

//groundwork初始化
#include "delay.h"
#include "led.h"
#include "dbus.h"
#include "usart.h"
#include "pid.h"
#include "can.h"

//task初始化
#include "pid_caculate_task.h"

void init_all()
{
	delay_init(180);
	ledX_init();
	RC_Init();
	UART8_init();
	can1_init();
	power_init();
	
	pid_caculate_init();
}
