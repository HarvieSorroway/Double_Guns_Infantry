#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "delay.h"

#define START_TASK_PRIO 1
#define START_TASK_STK_SIZE 128
TaskHandle_t Start_Task_Handler;

//tasks:
//	pid_caculate_task
#include "pid_caculate_task.h"
#define PID_CACULATE_TASK_PRIO 3
#define PID_CACULATE_TASK_STK_SIZE 256
TaskHandle_t pid_caculate_Handler;

//	mecanum_task
#include "mecanum_task.h"
#define MECANUM_TASK_PRIO 5
#define MECANUM_TASK_STK_SIZE 256
TaskHandle_t mecanum_task_Handler;

//test task
#define TEST_TASK_PRIO 2
#define TEST_TASK_STK_SIZE 128
TaskHandle_t test_task_Handler;




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
	
			xTaskCreate((TaskFunction_t)pid_caculate_task,
						(char*         )"pid_caculate_task",
						(uint16_t      )PID_CACULATE_TASK_STK_SIZE,
						(void *        )NULL,
						(UBaseType_t   )PID_CACULATE_TASK_PRIO,
						(TaskHandle_t* )&pid_caculate_Handler);
				
			xTaskCreate((TaskFunction_t)mecanum_task,
						(char*         )"mecanum_task",
						(uint16_t      )MECANUM_TASK_STK_SIZE,
						(void*         )NULL,
						(UBaseType_t   )MECANUM_TASK_PRIO,
						(TaskHandle_t* )&mecanum_task_Handler);
			xTaskCreate((TaskFunction_t)test_task,
						(char*         )"test_task",
						(uint16_t      )TEST_TASK_STK_SIZE,
						(void*         )NULL,
						(UBaseType_t   )TEST_TASK_PRIO,
						(TaskHandle_t* )&test_task_Handler);

	vTaskDelete(Start_Task_Handler);//删除开始任务
	taskEXIT_CRITICAL();//退出临界区
}

void test_task(void *pvParameters)
{
	for(;;)
	{
		ledX_On(7);
		vTaskDelay(500);
		ledX_Off(7);
		vTaskDelay(500);
	}
}
