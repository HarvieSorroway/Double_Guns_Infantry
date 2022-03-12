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

float Float_bmiDirection = 0;
float Float_bmiZSpeed = 0;
float Float_bmiDirection_lastFrame = 0;

void gimbal_task(void *pvParameters)
{
	static portTickType xLastWakeTime_MecanumTask;
	xLastWakeTime_MecanumTask = xTaskGetTickCount();
	
	SetAngles(0,0);
	
	for(;;)
	{
		SetAngles(0,(float)(RC_CtrlData.rc.ch3 - 1024)/10);
		
		//pid test function
//		m2006_position_pid[0].Kp = FloatArray_GimbalCoefficients_position[0];
//		m2006_position_pid[0].Ki = FloatArray_GimbalCoefficients_position[1];
//		m2006_position_pid[0].Kd = FloatArray_GimbalCoefficients_position[2];
//		
//		m2006_speed_pid[0].Kp = FloatArray_GimbalCoefficients_speed[0];
//		m2006_speed_pid[0].Ki = FloatArray_GimbalCoefficients_speed[1];
//		m2006_speed_pid[0].Kd = FloatArray_GimbalCoefficients_speed[2];
//		
//		m2006_current_pid[0].Kp = FloatArray_GimbalCoefficients_current[0];
//		m2006_current_pid[0].Ki = FloatArray_GimbalCoefficients_current[1];
//		m2006_current_pid[0].Kd = FloatArray_GimbalCoefficients_current[2];
		
		vTaskDelayUntil(&xLastWakeTime_MecanumTask,pdMS_TO_TICKS(5));
	}
}
