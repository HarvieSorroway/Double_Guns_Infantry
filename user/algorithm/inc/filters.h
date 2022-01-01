#ifndef __FILTERS_H
#define __FILTERS_H

#include "stm32f4xx_conf.h"
#include "math.h"

typedef struct{
	int Int_Order;
	int _Flag_InitOrNot;
	float Float_Buffer[200];
}meanFilter_typedef;

typedef __packed struct
{
    float input;        //输入数据
    float out;          //滤波输出的数据
    float num;       //滤波参数
    float frame_period; //滤波的时间间隔 单位 s
}first_order_filter_type_t;

void  meanFilter_init(meanFilter_typedef*in,int order);
float meanFilter_caculate(meanFilter_typedef*in,float data_in);

void firstOrderFilter_init(first_order_filter_type_t *first_order_filter_type, float frame_period,float num);
void firstOrderFilter_caculate(first_order_filter_type_t *first_order_filter_type, float input);

#endif
