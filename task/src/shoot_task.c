#include "FreeRTOS.h"
#include "task.h"

#include "dbus.h"

#include "shoot_task.h"

void shoot_task(void *pvParameters)
{	
	for(;;)
	{
		if(RC_CtrlData.rc.s2==1)
		{
			TIM_SetCompare1(TIM4,1150);
			TIM_SetCompare2(TIM4,1150);
			TIM_SetCompare3(TIM4,1150);
			TIM_SetCompare4(TIM4,1150);
		}
		else if(RC_CtrlData.rc.s2==3)
		{
			TIM_SetCompare1(TIM4,1170);
			TIM_SetCompare2(TIM4,1170);
			TIM_SetCompare3(TIM4,1170);
			TIM_SetCompare4(TIM4,1170);
		}
		else if(RC_CtrlData.rc.s2==2)
		{
			TIM_SetCompare1(TIM4,1000);
			TIM_SetCompare2(TIM4,1000);
			TIM_SetCompare3(TIM4,1000);
			TIM_SetCompare4(TIM4,1000);
		}	
		
		vTaskDelay(100);
	}
}
