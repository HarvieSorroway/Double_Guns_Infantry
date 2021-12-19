#include "start_task.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "usart.h"
#include "can.h"
#include "delay.h"
#include "gimbal.h"

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
#define MECANUM_TASK_PRIO 4
#define MECANUM_TASK_STK_SIZE 256
TaskHandle_t mecanum_task_Handler;

//test task
#define TEST_TASK_PRIO 2
#define TEST_TASK_STK_SIZE 128
TaskHandle_t test_task_Handler;

//usart task
#define USART_TASK_PRIO 7
#define USART_TASK_STK_SIZE 128
TaskHandle_t usart_task_Handler;


//shoot task
#include "shoot_task.h"
#define SHOOT_TASK_PRIO 5
#define SHOOT_TASK_STK_SIZE 128
TaskHandle_t shoot_task_Handler;

//gimbal task
#include "gimbal_task.h"
#define GIMBAL_TASK_PRIO 6
#define GIMBAL_TASK_STK_SIZE 128
TaskHandle_t gimbal_task_Handler;

send_float test_datas[2];
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
						
			xTaskCreate((TaskFunction_t)shoot_task,
						(char*         )"shoot_task",
						(uint16_t      )SHOOT_TASK_STK_SIZE,
						(void*         )NULL,
						(UBaseType_t   )SHOOT_TASK_PRIO,
						(TaskHandle_t* )&shoot_task_Handler);
						
			xTaskCreate((TaskFunction_t)gimbal_task,
						(char*         )"gimbal_task",
						(uint16_t      )GIMBAL_TASK_STK_SIZE,
						(void*         )NULL,
						(UBaseType_t   )GIMBAL_TASK_PRIO,
						(TaskHandle_t* )&gimbal_task_Handler);
						
			xTaskCreate((TaskFunction_t)usart_task,
						(char*         )"usart_task",
						(uint16_t      )USART_TASK_STK_SIZE,
						(void*         )NULL,
						(UBaseType_t   )USART_TASK_PRIO,
						(TaskHandle_t* )&usart_task_Handler);

	vTaskDelete(Start_Task_Handler);//删除开始任务
	taskEXIT_CRITICAL();//退出临界区
}

void test_task(void *pvParameters)//led闪烁任务，用于监控系统是否运行正常
{
	for(;;)
	{
		ledX_On(7);
		vTaskDelay(1000);
		ledX_Off(7);
		vTaskDelay(500);
		//test_datas[0].fload_data = FloatArray_SetAngle[0];
		
		
	}
}

void usart_task(void *pvParameters)
{
	
	for(;;)
	{
		test_datas[0].fload_data = moto_m2006_info[0].moto_total_angle;
		test_datas[1].fload_data = FloatArray_SetAngle[0];
		USART_sendFloat(test_datas,2);
		vTaskDelay(2);
	}
}
