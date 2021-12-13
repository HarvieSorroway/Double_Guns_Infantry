//��̨���ԣ���ʱ��������5��led��ʾ����
#include "gimbal_task.h"


#include "gimbal.h"
#include "led.h"
#include "pid.h"
#include "usart.h"
#include "can.h"
#include "dbus.h"

float lastframe[20] = {0,};

void gimbal_task(void *pvParameters)
{
	static portTickType xLastWakeTime_MecanumTask;
	xLastWakeTime_MecanumTask = xTaskGetTickCount();
	for(;;)
	{
		float total = 0;
		for(int i = 0;i < 20;i++)
		{
			total += lastframe[i];
		}
		total += RC_CtrlData.rc.ch3;
		
		SetAngles(((float)total)/(21 * (RC_CtrlData.rc.s1 + 1)) ,0);
		ledX_Off(5);
		for(int i = 0;i < 19;i++)
		{
			lastframe[i] = lastframe[i + 1];
		}
		lastframe[19] = RC_CtrlData.rc.ch3;
		
		
		//test function
//		m2006_position_pid.Kp = FloatArray_GimbalCoefficients_position[0];
//		m2006_position_pid.Ki = FloatArray_GimbalCoefficients_position[1];
//		m2006_position_pid.Kd = FloatArray_GimbalCoefficients_position[2];
//		
//		m2006_speed_pid.Kp = FloatArray_GimbalCoefficients_speed[0];
//		m2006_speed_pid.Ki = FloatArray_GimbalCoefficients_speed[1];
//		m2006_speed_pid.Kd = FloatArray_GimbalCoefficients_speed[2];
//		
//		m2006_current_pid.Kp = FloatArray_GimbalCoefficients_current[0];
//		m2006_current_pid.Ki = FloatArray_GimbalCoefficients_current[1];
//		m2006_current_pid.Kd = FloatArray_GimbalCoefficients_current[2];
		
		vTaskDelayUntil(&xLastWakeTime_MecanumTask,pdMS_TO_TICKS(5));
	}
}
