#include "pid_task.h"
#include "can.h"
#include "dbus.h"
#include "vofa.protocol.h"
#define PID_SHOOT_CACULATE_PERIOD 5

pid_typedef shoot_speed_pid[2];
pid_typedef shoot_current_pid[2];

pid_typedef revolver_angle_pid;
pid_typedef revolver_speed_pid;

void pid_shoot_caculate_task(void *pvParameters)
{
	int i;
	int16_t shoot_current_set[4];
	
	float shoot_speed_set[2];
	float revolver_angle_set;
	
	TickType_t PreviousWakeTime;
	TickType_t mxTimeIncrement=pdMS_TO_TICKS(PID_SHOOT_CACULATE_PERIOD);
	PreviousWakeTime = xTaskGetTickCount();
	
	revolver_angle_set = moto_revolver_info.moto_total_angle;
	
	while(1)
	{
		if(RC_CtrlData.rc.s2==1)
		{
			shoot_speed_set[0] = 1500;
			shoot_speed_set[1] = 1500;
			revolver_angle_set -= 100;
		}
		else if(RC_CtrlData.rc.s2==3)
		{
			shoot_speed_set[0] = 1000;
			shoot_speed_set[1] = 1000;
			revolver_angle_set += 0;
		}
		else if(RC_CtrlData.rc.s2==2)
		{
			shoot_speed_set[0] = 0;
			shoot_speed_set[1] = 0;
			revolver_angle_set += 0;
		}
		
		for(i=0;i<2;i++)
		{
			pid_caculate_delta(&shoot_speed_pid[i],shoot_speed_set[i],moto_shoot_info[i].moto_speed);
			pid_caculate_delta(&shoot_current_pid[i],shoot_speed_pid[i].out,moto_shoot_info[i].moto_current);
			shoot_current_set[i]=shoot_current_pid[i].out;
		}
		
		pid_caculate_delta(&revolver_angle_pid,revolver_angle_set,moto_revolver_info.moto_total_angle);
		pid_caculate_delta(&revolver_speed_pid,revolver_angle_pid.out,moto_revolver_info.moto_speed);
		
		shoot_current_set[2]=revolver_speed_pid.out;
		
		can_mes_send(CAN1,CAN1_TX_MOTO3508_5_6,shoot_current_set);
//		float ch[2];
//		ch[0]=shoot_speed_pid[0].Sv;
//		ch[1]=shoot_speed_pid[0].Av;
//		vofa_justfloat_output(ch,2);
		
		vTaskDelayUntil(&PreviousWakeTime,mxTimeIncrement);
	}
}



