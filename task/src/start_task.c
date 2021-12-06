#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "delay.h"
#include "pid_task.h"

#define START_TASK_PRIO 1
#define START_TASK_STK_SIZE 128
TaskHandle_t Start_Task_Handler;

#define PID_SHOOT_CACULATE_TASK_PRIO 2
#define PID_SHOOT_CACULATE_TASK_STK_SIZE 256
TaskHandle_t Pid_Shoot_Caculate_Handler;

void create_start_task(void)
{
			xTaskCreate((TaskFunction_t)start_task,
                (char*         )"start_task",
                (uint16_t      )START_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )START_TASK_PRIO,
                (TaskHandle_t*)&Start_Task_Handler);
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//进入临界区
	
			xTaskCreate((TaskFunction_t)pid_shoot_caculate_task,
                (char*         )"pid_shoot_caculate_task",
                (uint16_t      )PID_SHOOT_CACULATE_TASK_STK_SIZE,
                (void *        )NULL,
                (UBaseType_t   )PID_SHOOT_CACULATE_TASK_PRIO,
                (TaskHandle_t*)&Pid_Shoot_Caculate_Handler);
	
	vTaskDelete(Start_Task_Handler);//删除开始任务
	taskEXIT_CRITICAL();//退出临界区
}
