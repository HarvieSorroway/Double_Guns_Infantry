//底盘运算算法，使用4号led表示正常运行
#include "mecanum_task.h"

#include "FreeRTOS.h"
#include "task.h"

#include "mecanum.h"
#include "led.h"

void mecanum_task(void *pvParameters)
{
	static portTickType xLastWakeTime_MecanumTask;
	xLastWakeTime_MecanumTask = xTaskGetTickCount();
	
	for(;;)
	{
		ledX_On(4);
		get_aimSpeed();
		ledX_Off(4);
		vTaskDelayUntil(&xLastWakeTime_MecanumTask,pdMS_TO_TICKS(5));
	}
}
