//初始化所有需要初始化的函数

#include "init.h"

#include "data_stream.h"

//groundwork初始化
#include "delay.h"
#include "led.h"
#include "dbus.h"
#include "usart.h"
#include "pid.h"
#include "can.h"
#include "pwm.h"
#include "mecanum.h"

//task初始化
#include "pid_caculate_task.h"
#include "bmi_task.h"

void init_all()
{
	
	
	delay_init(180);
	ledX_init();
	RC_Init();
	
	can1_init();
	power_init();
	PWM4_init();
	
//	TIM_SetCompare1(TIM4,1000);
//	TIM_SetCompare2(TIM4,1000);
//	TIM_SetCompare3(TIM4,1000);
//	TIM_SetCompare4(TIM4,1000);
//	delay_ms(3500);
	UART8_init();
	USART6_init();
	pid_caculate_init();
	
	CollectData[0] = CollectData_CAN;
	CollectData[1] = CollectData_DBUS;
	CollectData[2] = CollectData_Mecanum;
	CollectData[3] = CollectData_BMI;
}
