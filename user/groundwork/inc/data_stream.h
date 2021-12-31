#ifndef __DATA_STREAM_H
#define __DATA_STREAM_H

#include "stm32f4xx_conf.h"
#include "dbus.h"
#include "can.h"
#include "usart.h"

#define DataSource 4

typedef struct data_bmi_struct{
	float Angle_X;
	float Angle_Y;
	float Angle_Z_total;
	float Angle_Z_raw;
	float Acceleration_X;
	float Acceleration_Y;
	float Acceleration_Z;
	float Velocity_X;
	float Velocity_Y;
	float Velocity_Z;
}Data_bmi_struct;

extern Data_bmi_struct Data_bmi;

extern RC_Ctl_t Data_RC;

extern moto_info Data_m3508[4];
extern moto_info Data_m6020[4];
extern moto_info Data_m2006;

extern send_float Data_toVOFA[100];

extern void (*CollectData[DataSource])(void);

#endif
