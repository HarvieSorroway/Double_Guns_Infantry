//��ʼ��������Ҫ��ʼ���ĺ���

#include "init.h"

//groundwork��ʼ��
#include "delay.h"
#include "led.h"
#include "dbus.h"
#include "usart.h"
#include "pid.h"
#include "can.h"
#include "pwm.h"

//task��ʼ��
#include "pid_caculate_task.h"

void init_all()
{
	
	
	delay_init(180);
	ledX_init();
	RC_Init();
	UART8_init();
	USART6_init();
	can1_init();
	power_init();
	PWM4_init();
	
//	TIM_SetCompare1(TIM4,1000);
//	TIM_SetCompare2(TIM4,1000);
//	TIM_SetCompare3(TIM4,1000);
//	TIM_SetCompare4(TIM4,1000);
//	delay_ms(3500);
	
	pid_caculate_init();
}
