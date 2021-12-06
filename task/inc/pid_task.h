#ifndef __PID_TASK_H
#define __PID_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "pid.h"

extern pid_typedef shoot_speed_pid[2];
extern pid_typedef shoot_current_pid[2];

extern pid_typedef revolver_angle_pid;
extern pid_typedef revolver_speed_pid;

void pid_shoot_caculate_task(void *pvParameters);

#endif
