#ifndef __PID_CACULATE_TASK_H
#define __PID_CACULATE_TASK_H

#include "stm32f4xx_conf.h"

extern float FloatArray_SpeedInit[3];
extern float FloatArray_CurrentInit[3];

void pid_caculate_task(void *pvParameters);
void pid_caculate_init(void);

#endif
