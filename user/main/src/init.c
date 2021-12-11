//��ʼ��������Ҫ��ʼ���ĺ���

#include "init.h"

//groundwork��ʼ��
#include "delay.h"
#include "led.h"
#include "dbus.h"
#include "usart.h"
#include "pid.h"
#include "can.h"

//task��ʼ��
#include "pid_caculate_task.h"

void init_all()
{
	delay_init(180);
	ledX_init();
	RC_Init();
	UART8_init();
	can1_init();
	pid_init(&chassis_current_pid[0],0.8,0.3,0.02,3000,2000);
}
