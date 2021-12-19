//usart通讯，包含了VOFA的协议

//UART8:用于VOFA JustFloat协议的发送，不使用中断
//USART6:用于和IMU的通讯，不发送消息[暂时]，使用中断，中断定义在任务函数里，便于处理
//
//USART_sendFloat(send_float * data,int length)提供待发送浮点数数组的指针和数组长度
//使用UART8串口发送
#include "usart.h"
#include "led.h"


void UART8_init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8,ENABLE);
	

	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef UART8_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE,&GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource1,GPIO_AF_UART8);


	UART8_InitStruct.USART_BaudRate = 115200;
	UART8_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	UART8_InitStruct.USART_Mode = USART_Mode_Tx;
	UART8_InitStruct.USART_Parity = USART_Parity_No;
	UART8_InitStruct.USART_StopBits = USART_StopBits_1;
	UART8_InitStruct.USART_WordLength = USART_WordLength_8b;

	
	USART_Init(UART8,&UART8_InitStruct);
	USART_Cmd(UART8,ENABLE);


	NVIC_InitStruct.NVIC_IRQChannel = UART8_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
}

void USART6_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
	

	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART6_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;  

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOG,&GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOG,GPIO_PinSource9,GPIO_AF_USART6);


	USART6_InitStruct.USART_BaudRate = 115200;
	USART6_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART6_InitStruct.USART_Mode = USART_Mode_Rx;
	USART6_InitStruct.USART_Parity = USART_Parity_No;
	USART6_InitStruct.USART_StopBits = USART_StopBits_1;
	USART6_InitStruct.USART_WordLength = USART_WordLength_8b;

	USART_Cmd(USART6,ENABLE);

	USART_ITConfig(USART6,USART_IT_RXNE,ENABLE);
	USART_Init(USART6,&USART6_InitStruct);
	
	
	NVIC_InitStruct.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStruct);
}


void USART_sendFloat(send_float * data,int length)
{
	//ledX_On(8);
	uint8_t tail[4] = {0x00,0x00,0x80,0x7f};

	for(int i = 0;i < length;i++)//send data
	{
		for(int k = 0;k < 4;k++)
		{
			sendD(data[i].bits[k]);
		}
	}

	for(int i = 0;i < 4;i++)
	{
		sendD(tail[i]);
	}
	//ledX_Off(8);
}

void sendD(uint8_t ch)
{
	//ledX_On(7);
	USART_SendData(UART8,ch);  
	while(USART_GetFlagStatus(UART8,USART_FLAG_TXE) == RESET);
	//ledX_Off(7);
	
}
