//云台测试（暂时）任务，用5号led表示正常

#include "gimbal_task.h"


#include "gimbal.h"
#include "led.h"
#include "pid.h"
#include "usart.h"
#include "can.h"
#include "dbus.h"

volatile int Using_Delta = 0;
float lastframe[2][20] = {0,};

void gimbal_task(void *pvParameters)
{
	static portTickType xLastWakeTime_MecanumTask;
	xLastWakeTime_MecanumTask = xTaskGetTickCount();
	for(;;)
	{
		Using_Delta = RC_CtrlData.rc.s1 - 1;
		float total_1 = 0,total_2 = 0;
		for(int i = 0;i < 20;i++)
		{
			total_1 += lastframe[0][i];
			total_2 += lastframe[1][i];
		}
		total_1 += (RC_CtrlData.rc.ch2 - 1024);
		total_1 /= (21 * 10);
		total_2 += (RC_CtrlData.rc.ch3 - 1024);
		total_2 /= (21 * 10);

		if(!Using_Delta)SetAngles(/*(float)-(RC_CtrlData.rc.ch2 - 1024)/(float)6*/total_1,/*(float)(RC_CtrlData.rc.ch3 - 1024)/(float)6*/total_2);
		else SetAngles_delta((float)(RC_CtrlData.rc.ch2 - 1024)/(float)600,(float)(RC_CtrlData.rc.ch3 - 1024)/(float)600);
		ledX_Off(5);
		for(int i = 0;i < 19;i++)
		{
			lastframe[0][i] = lastframe[0][i + 1];
			lastframe[1][i] = lastframe[1][i + 1];
		}
		lastframe[0][19] = RC_CtrlData.rc.ch2 - 1024;
		lastframe[1][19] = RC_CtrlData.rc.ch3 - 1024;
		
		//test function
		m2006_position_pid[0].Kp = FloatArray_GimbalCoefficients_position[0];
		m2006_position_pid[0].Ki = FloatArray_GimbalCoefficients_position[1];
		m2006_position_pid[0].Kd = FloatArray_GimbalCoefficients_position[2];
		
		m2006_speed_pid[0].Kp = FloatArray_GimbalCoefficients_speed[0];
		m2006_speed_pid[0].Ki = FloatArray_GimbalCoefficients_speed[1];
		m2006_speed_pid[0].Kd = FloatArray_GimbalCoefficients_speed[2];
		
		m2006_current_pid[0].Kp = FloatArray_GimbalCoefficients_current[0];
		m2006_current_pid[0].Ki = FloatArray_GimbalCoefficients_current[1];
		m2006_current_pid[0].Kd = FloatArray_GimbalCoefficients_current[2];
		
		vTaskDelayUntil(&xLastWakeTime_MecanumTask,pdMS_TO_TICKS(5));
	}
}
