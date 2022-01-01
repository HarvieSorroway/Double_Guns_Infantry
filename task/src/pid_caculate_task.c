//pid计算任务，使用3号led表示正常运行
#define Using_Chassis 0
#define Using_Gimbal 1

#include "FreeRTOS.h"
#include "task.h"
#include "pid_caculate_task.h"

#include "data_stream.h"

#include "mecanum.h"
#include "pid.h"
#include "can.h"
#include "led.h"
#include "gimbal.h"
//#include "usart.h"
#include "gimbal_task.h"

#include "filters.h"

float FloatArray_SpeedInit[3] = {10,0.3,0};
float FloatArray_CurrentInit[3] = {1.2,0.08,0};

first_order_filter_type_t filter2;


void pid_caculate_init(void)
{
	firstOrderFilter_init(&filter2,1,1);
	
	for(int i = 0;i < 4;i++)
	{	
		pid_init(&chassis_speed_pid[i],FloatArray_SpeedInit[0],FloatArray_SpeedInit[1],FloatArray_SpeedInit[2],15000,12000);

		pid_init(&chassis_current_pid[i],FloatArray_CurrentInit[0],FloatArray_CurrentInit[1],FloatArray_CurrentInit[2],15000,12000);
	}
	for(int i = 0;i < 2;i++)
	{
		//
		pid_init(&m2006_position_pid_FollowChassis[i],FloatArray_GimbalCoefficients_position[0],FloatArray_GimbalCoefficients_position[1],FloatArray_GimbalCoefficients_position[2],15000,8000);

		pid_init(&m2006_speed_pid_FollowChassis[i],FloatArray_GimbalCoefficients_speed[0],FloatArray_GimbalCoefficients_speed[1],FloatArray_GimbalCoefficients_speed[2],15000,8000);

		pid_init(&m2006_current_pid_FollowChassis[i],FloatArray_GimbalCoefficients_current[0],FloatArray_GimbalCoefficients_current[1],FloatArray_GimbalCoefficients_current[2],15000,8000);
	}
}

void pid_caculate_task(void *pvParameters)
{
	static portTickType xLastWakeTime_PidCaculateTask;
	xLastWakeTime_PidCaculateTask = xTaskGetTickCount();
	
	for(;;)
	{
		ledX_On(3);
		
		if(Using_Chassis)
		{
			for(int i=0;i<4;i++)
			{
//				pid_caculate_position(&chassis_speed_pid[i],(int)aimSpeed[i],moto_chassis_info[i].moto_speed);
//				pid_caculate_position(&chassis_current_pid[i],chassis_speed_pid[i].OUT,moto_chassis_info[i].moto_current);
				pid_caculate_position(&chassis_speed_pid[i],(int)aimSpeed[i],Data_m3508[i].moto_speed);
				pid_caculate_position(&chassis_current_pid[i],chassis_speed_pid[i].OUT,Data_m3508[i].moto_current);
			}
		}
		
		if(Using_Gimbal)
		{
			for(int i=0;i<2;i++)
			{
				firstOrderFilter_caculate(&filter2,Data_bmi.Angle_Z_total);
				pid_caculate_delta(&m2006_position_pid_FollowChassis[i],FloatArray_SetAngle[i],filter2.out/*moto_m2006_info[i].moto_total_angle*/);
				pid_caculate_delta(&m2006_speed_pid_FollowChassis[i],m2006_position_pid_FollowChassis[i].OUT,Data_bmi.Velocity_Z);
				//pid_caculate_position(&m2006_current_pid_FollowChassis[i],m2006_speed_pid_FollowChassis[i].OUT,Data_m6020[i].moto_current);
			}
		}
		
		set_3508_current(chassis_current_pid[0].OUT,chassis_current_pid[1].OUT,chassis_current_pid[2].OUT,chassis_current_pid[3].OUT);
		
		if(Data_RC.rc.s1 == 1 || 1)
		{
			set_2006_current(m2006_speed_pid_FollowChassis[0].OUT,m2006_current_pid_FollowChassis[1].OUT);
		}

		ledX_Off(3);

		
		vTaskDelayUntil(&xLastWakeTime_PidCaculateTask,pdMS_TO_TICKS(5));
	}
}
