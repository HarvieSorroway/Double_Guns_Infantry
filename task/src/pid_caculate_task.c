//pid计算任务，使用3号led表示正常运行

#include "FreeRTOS.h"
#include "task.h"
#include "pid_caculate_task.h"


#include "mecanum.h"
#include "pid.h"
#include "can.h"
#include "led.h"
#include "gimbal.h"
#include "usart.h"


float FloatArray_SpeedInit[3] = {18,0.5,5};
float FloatArray_CurrentInit[3] = {0.95,0.08,0.1};


void pid_caculate_init(void)
{
	for(int i = 0;i < 4;i++)
	{	
		pid_init(&chassis_speed_pid[i],FloatArray_SpeedInit[0],FloatArray_SpeedInit[1],FloatArray_SpeedInit[2],4000,3000);
		pid_init(&chassis_current_pid[i],FloatArray_CurrentInit[0],FloatArray_CurrentInit[1],FloatArray_CurrentInit[2],4000,3000);
	}
	
	pid_init(&m2006_position_pid,FloatArray_GimbalCoefficients_position[0],FloatArray_GimbalCoefficients_position[1],FloatArray_GimbalCoefficients_position[2],20000,15000);
	pid_init(&m2006_speed_pid,FloatArray_GimbalCoefficients_speed[0],FloatArray_GimbalCoefficients_speed[1],FloatArray_GimbalCoefficients_speed[2],20000,15000);
	pid_init(&m2006_current_pid,FloatArray_GimbalCoefficients_current[0],FloatArray_GimbalCoefficients_current[1],FloatArray_GimbalCoefficients_current[2],20000,15000);
}

void pid_caculate_task(void *pvParameters)
{
	static portTickType xLastWakeTime_PidCaculateTask;
	xLastWakeTime_PidCaculateTask = xTaskGetTickCount();
	
	
	
	for(;;)
	{
		ledX_On(3);
		for(int i=0;i<4;i++)
		{
//			pid_caculate_position(&chassis_speed_pid[i],(int)aimSpeed[i],moto_chassis_info[i].moto_speed);
//			pid_caculate_position(&chassis_current_pid[i],chassis_speed_pid[i].OUT,moto_chassis_info[i].moto_current);
		}
		
		pid_caculate_position(&m2006_position_pid,FloatArray_SetAngle[0],moto_m2006_info.moto_total_angle);
		pid_caculate_position(&m2006_speed_pid,m2006_position_pid.OUT,moto_m2006_info.moto_speed);
		pid_caculate_position(&m2006_current_pid,m2006_speed_pid.OUT,moto_m2006_info.moto_current);
		
		set_3508_current(chassis_current_pid[0].OUT,chassis_current_pid[1].OUT,chassis_current_pid[2].OUT,chassis_current_pid[3].OUT);
		set_2006_current(m2006_current_pid.OUT);
		
		ledX_Off(3);
		
		
		
		
		
		
		vTaskDelayUntil(&xLastWakeTime_PidCaculateTask,pdMS_TO_TICKS(5));

	}
}
