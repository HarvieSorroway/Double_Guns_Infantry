#include "filters.h"

//均值滤波初始化与计算
void  meanFilter_init(meanFilter_typedef*in,int order)
{
	in->Int_Order = order;
	in->_Flag_InitOrNot = 0;
}

float meanFilter_caculate(meanFilter_typedef * in,float data_in)
{
	float output = 0;
	if(in->_Flag_InitOrNot)
	{
		for(int i =1;i < in->Int_Order;i++)
		{
			in->Float_Buffer[i - 1] = in->Float_Buffer[i];
			output += in->Float_Buffer[i];
		}
		in->Float_Buffer[in->Int_Order - 1] = data_in;
		output += data_in;
		
		output /= in->Int_Order;
		return output;
	}
	else
	{	
		for(int i =0;i < in->Int_Order;i++)
		{
			in->Float_Buffer[i] = data_in;
		}
		in->_Flag_InitOrNot = 1;
		
		return data_in;
	}
}

void firstOrderFilter_init(first_order_filter_type_t *first_order_filter_type, float frame_period,float num)
{
    first_order_filter_type->frame_period = frame_period;
    first_order_filter_type->num = num;
    first_order_filter_type->input = 0.0f;
    first_order_filter_type->out = 0.0f;
}

void firstOrderFilter_caculate(first_order_filter_type_t *first_order_filter_type, float input)
{
    first_order_filter_type->input = input;
    first_order_filter_type->out =
		first_order_filter_type->num / (first_order_filter_type->num + first_order_filter_type->frame_period) * first_order_filter_type->out + 
		first_order_filter_type->frame_period / (first_order_filter_type->num + first_order_filter_type->frame_period) * first_order_filter_type->input;
}
