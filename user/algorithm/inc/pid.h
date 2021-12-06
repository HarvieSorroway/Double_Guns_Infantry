#ifndef __PID_H
#define __PID_H

#include "can.h"

typedef struct
{
	float Sv;
	float Av;

	float Kp;
	float Ki;
	float Kd;

	float err;
	float err_last;
	float err_next;
	float total_err;
	float del_err;
	
	float pout;
	float iout;
	float dout;

	float Pid_out_limit;
	float Pid_integral_limit;
		
	float OUT;
}pid_typedef;

extern pid_typedef chassis_current_pid[4];
extern pid_typedef chassis_speed_pid[4];
extern pid_typedef m2006_current_pid;
extern pid_typedef m2006_speed_pid;
extern pid_typedef m2006_position_pid;

void pid_abs_limit(float *a,float abs_max);
void pid_init(pid_typedef*pid,float kp,float ki,float kd,float pid_out_limit,float pid_integral_limit);
void pid_caculate_delta(pid_typedef*pid,float Sv,float Av);
void pid_caculate_position(pid_typedef*pid,float Sv,float Av);
void pid_caculate_position_2(pid_typedef*pid,float Sv,float Av);

#endif 
