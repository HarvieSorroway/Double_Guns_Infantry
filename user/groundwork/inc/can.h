#ifndef __CAN_H
#define __CAN_H

#include "stm32f4xx_conf.h"

typedef struct{
	int16_t moto_current;
	int16_t moto_speed;
	int8_t moto_temperature;
	float moto_total_angle;
	
	float moto_raw_angle;
	uint16_t moto_raw_last_angle;
	uint16_t moto_angle;
	uint16_t moto_offset_angle;
	int32_t round_count;
}moto_info;

typedef enum{
	CAN1_TX_MOTO3508_1_4 = 0x200,
 	CAN1_TX_MOTO3508_5_8 = 0x1FF,
	
	CAN1_RX_MOTO3508_1 = 0x201,
	CAN1_RX_MOTO3508_2 = 0x202,
	CAN1_RX_MOTO3508_3 = 0x203,
	CAN1_RX_MOTO3508_4 = 0x204,
	
	CAN1_RX_MOTO2006_5_1 = 0x209,
	CAN1_RX_MOTO2006_5_2 = 0x206,
	//CAN1_RX_MOTO2006_5 = 0x207,
}CAN_Message_ID;

extern moto_info moto_chassis_info[4];
extern moto_info moto_m2006_info[2];

void can1_init(void);
void power_init(void);
void set_3508_current(int16_t i1,int16_t i2,int16_t i3,int16_t i4);
void moto_infomation_process(moto_info *moto_infomation,CanRxMsg *RxMessage);
void set_2006_current(int16_t i1,int16_t i2);
void set_moto_current(int16_t i1,int16_t i2,int16_t i3,int16_t i4);
void CollectData_CAN(void);
	
#endif
