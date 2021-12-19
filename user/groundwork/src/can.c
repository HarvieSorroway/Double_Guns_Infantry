#include "can.h"


moto_info moto_chassis_info[4];
moto_info moto_m2006_info[2];

CanRxMsg RxMessage;

void can1_init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	CAN_InitTypeDef CAN1_Initstruct;
	CAN_FilterInitTypeDef CAN1_FilterInitstruct;
	NVIC_InitTypeDef NVIC_Initstruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_CAN1);
	
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_Initstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD,&GPIO_Initstruct);
	
	CAN1_Initstruct.CAN_Prescaler=5;
	CAN1_Initstruct.CAN_BS1=CAN_BS1_3tq;
	CAN1_Initstruct.CAN_BS2=CAN_BS2_5tq;
	CAN1_Initstruct.CAN_SJW=CAN_SJW_1tq;
	CAN1_Initstruct.CAN_Mode=CAN_Mode_Normal;
	CAN1_Initstruct.CAN_ABOM=ENABLE;
	CAN1_Initstruct.CAN_AWUM=DISABLE;
	CAN1_Initstruct.CAN_NART=DISABLE;
	CAN1_Initstruct.CAN_RFLM=DISABLE;
	CAN1_Initstruct.CAN_TTCM=DISABLE;
	CAN1_Initstruct.CAN_TXFP=DISABLE;
	
	CAN_Init(CAN1,&CAN1_Initstruct);
	
	CAN1_FilterInitstruct.CAN_FilterIdHigh=(0x205<<21&0xFFFF0000)>>16;//Î´½â
	CAN1_FilterInitstruct.CAN_FilterIdLow=0;//Î´½â
	CAN1_FilterInitstruct.CAN_FilterMaskIdHigh=0x0000;
	CAN1_FilterInitstruct.CAN_FilterMaskIdLow=0x0000;
	CAN1_FilterInitstruct.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN1_FilterInitstruct.CAN_FilterNumber=0;
	CAN1_FilterInitstruct.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN1_FilterInitstruct.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN1_FilterInitstruct.CAN_FilterActivation=ENABLE;
	
	CAN_FilterInit(&CAN1_FilterInitstruct);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	CAN_ITConfig(CAN1,CAN_IT_TME,ENABLE); 
	
	NVIC_Initstruct.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Initstruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_Initstruct);
}

void power_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	GPIO_InitTypeDef GPIO_Initstruct;
    GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstruct.GPIO_Speed=GPIO_Low_Speed;
	GPIO_Initstruct.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOH,&GPIO_Initstruct);
	
	GPIO_WriteBit(GPIOH,GPIO_Pin_2,Bit_RESET);
	GPIO_WriteBit(GPIOH,GPIO_Pin_3,Bit_RESET);
	GPIO_WriteBit(GPIOH,GPIO_Pin_4,Bit_RESET);
	GPIO_WriteBit(GPIOH,GPIO_Pin_5,Bit_RESET);
	
	GPIO_SetBits(GPIOH, GPIO_Pin_2);
	GPIO_SetBits(GPIOH, GPIO_Pin_3);
	GPIO_SetBits(GPIOH, GPIO_Pin_4);
	GPIO_SetBits(GPIOH, GPIO_Pin_5);
}

void set_3508_current(int16_t i1,int16_t i2,int16_t i3,int16_t i4)
{
	CanTxMsg TxMessage;
	TxMessage.StdId= CAN1_TX_MOTO3508_1_4;
	TxMessage.IDE = 0;
	TxMessage.RTR = 0;
	TxMessage.DLC = 8;
	TxMessage.Data[0] = i1 >> 8;
	TxMessage.Data[1] = i1;
	TxMessage.Data[2] = i2 >> 8;
	TxMessage.Data[3] = i2;
	TxMessage.Data[4] = i3 >> 8;
	TxMessage.Data[5] = i3;
	TxMessage.Data[6] = i4 >> 8;
	TxMessage.Data[7] = i4;
	CAN_Transmit(CAN1, &TxMessage);
}

void set_2006_current(int16_t i1,int16_t i2)
{
	CanTxMsg TxMessage;
	TxMessage.StdId= CAN1_TX_MOTO3508_5_8;
	TxMessage.IDE = 0;
	TxMessage.RTR = 0;
	TxMessage.DLC = 8;
	TxMessage.Data[0] = i1 >> 8;
	TxMessage.Data[1] = i1;
	TxMessage.Data[2] = i2 >> 8;
	TxMessage.Data[3] = i2;
	CAN_Transmit(CAN1, &TxMessage);
}

void set_moto_current(int16_t i1,int16_t i2,int16_t i3,int16_t i4)
{
	CanTxMsg TxMessage;
	TxMessage.StdId= CAN1_TX_MOTO3508_5_8;
	TxMessage.IDE = 0;
	TxMessage.RTR = 0;
	TxMessage.DLC = 8;
	TxMessage.Data[0] = i1 >> 8;
	TxMessage.Data[1] = i1;
	TxMessage.Data[2] = i2 >> 8;
	TxMessage.Data[3] = i2;
	TxMessage.Data[4] = i3 >> 8;
	TxMessage.Data[5] = i3;
	TxMessage.Data[6] = i4 >> 8;
	TxMessage.Data[7] = i4;
	CAN_Transmit(CAN1, &TxMessage);
}

void moto_infomation_process(moto_info *moto_infomation,CanRxMsg *RxMessage)
{
	moto_infomation->moto_raw_last_angle=moto_infomation->moto_raw_angle;
	moto_infomation->moto_raw_angle=((RxMessage->Data[0]<<8)|RxMessage->Data[1]);
	moto_infomation->moto_angle=(float)moto_infomation->moto_raw_angle*(float)360/(float)8192;
	if(moto_infomation->moto_raw_angle-moto_infomation->moto_raw_last_angle>4096)
		moto_infomation->round_count--;
	else if(moto_infomation->moto_raw_angle-moto_infomation->moto_raw_last_angle<-4096)
		moto_infomation->round_count++;
	moto_infomation->moto_total_angle=moto_infomation->round_count*360+(moto_infomation->moto_raw_angle-(float)moto_infomation->moto_offset_angle)*(float)360/(float)8192;
	
	moto_infomation->moto_speed=((RxMessage->Data[2]<<8)|RxMessage->Data[3]);
	moto_infomation->moto_current=((RxMessage->Data[4]<<8)|RxMessage->Data[5]);
	moto_infomation->moto_temperature=RxMessage->Data[6];
}

void CAN1_RX0_IRQHandler(void)
{
	int i;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) != RESET)
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FF0);
		CAN_ClearFlag(CAN1, CAN_FLAG_FF0); 
		CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
		switch (RxMessage.StdId)
		{
			case CAN1_RX_MOTO3508_1:
			case CAN1_RX_MOTO3508_2:
			case CAN1_RX_MOTO3508_3:
			case CAN1_RX_MOTO3508_4:
			{
				i=RxMessage.StdId-CAN1_RX_MOTO3508_1;
				moto_infomation_process(&moto_chassis_info[i],&RxMessage);
			}break;
			case CAN1_RX_MOTO2006_5_1:
			case CAN1_RX_MOTO2006_5_2:
			{
				i=RxMessage.StdId-CAN1_RX_MOTO2006_5_1;
				moto_infomation_process(&moto_m2006_info[i],&RxMessage);
			}break;
		}	
	}
}
