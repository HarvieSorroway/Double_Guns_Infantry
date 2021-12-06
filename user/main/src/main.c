#include "FreeRTOS.h"
#include "task.h"
#include "sys.h"
#include "delay.h"
#include "arm_math.h"
#include "dbus.h"
#include "usart.h"
#include "can.h"
#include "pid.h"
#include "start_task.h"
#include "pid_task.h"
//	ϵͳʱ�� = HSE(12MHz)*N(180)/(M(6)*P(4)) = 180MHz
//	ClocksTypeDef.SYSCLK_Frequency = 180000000
//	ClocksTypeDef.HCLK_Frequency = 180000000
//	ClocksTypeDef.PCLK1_Frequency = 45000000
//	ClocksTypeDef.PCLK2_Frequency = 90000000
//	APB1 45M
//	APB2 90M
//	PLL_Q = 8
RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4
    delay_init(180);//��ʼ����ʱ����
    RCC_GetClocksFreq(&RCC_Clocks);//��֤����ʱ��
		
		usart1_init();
		can1_init();
		power_init();
		
		int i;
		for(i=0;i<2;i++)
		{
			pid_init(&shoot_speed_pid[i],18,0.5,2,15000,10000);
			pid_init(&shoot_current_pid[i],0.7,0.1,0,15000,10000);
		}
		
		pid_init(&revolver_angle_pid,5,0,1,10000,8000);
		pid_init(&revolver_speed_pid,17,1.5,0,10000,8000);
		
		create_start_task();//������ʼ����	
		vTaskStartScheduler();//�����������

    while(1)
		{
			
		}
}





