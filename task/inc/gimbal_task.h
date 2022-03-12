#ifndef GIMBAL_TASK_H
#define GIMBAL_TASK_H

#include "stm32f4xx_conf.h"

#include "FreeRTOS.h"
#include "task.h"

extern float Float_bmiDirection;
extern float Float_bmiZSpeed;
extern float Float_bmiDirection_lastFrame;

void gimbal_task(void *pvParameters);


#endif
