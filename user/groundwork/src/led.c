//控制A板板载led灯
//
//ledX_init()初始化led
//
//ledX_On(ledX)点亮编号为ledX的led灯
//ledX_Off(ledX)熄灭
//ledX_Clear(void)熄灭所有的led灯
//ledX_cmd(ledX);点亮ledX的同时熄灭其他led灯

#include "led.h"


void ledX_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);

	GPIO_InitTypeDef GPIO_D_InitStruct;
	
	GPIO_D_InitStruct.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_D_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_D_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_D_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_D_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOD,&GPIO_D_InitStruct);

	GPIO_InitTypeDef GPIO_G_InitStruct;
	
	GPIO_G_InitStruct.GPIO_Pin=GPIO_Pin_2 
							 | GPIO_Pin_3
							 | GPIO_Pin_4
							 | GPIO_Pin_5
							 | GPIO_Pin_6
							 | GPIO_Pin_7
							 | GPIO_Pin_8
							 | GPIO_Pin_9
							 | GPIO_Pin_10;

	GPIO_G_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_G_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_G_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_G_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;

	GPIO_Init(GPIOG,&GPIO_G_InitStruct);
	
	ledX_Clear();
}

void ledX_On(uint16_t ledX)
{
	ledX_light(ledX);
}

void ledX_Off(uint16_t ledX)
{
	if(ledX < 2)
	{
		
		if(ledX == 0)
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_11);
		}
		else 
		{
			GPIO_SetBits(GPIOD,GPIO_Pin_10);
		}	
	}
	else if(ledX >= 2 && ledX < 11)
	{
		GPIO_SetBits(GPIOG,GPIO_Pin_2 * (uint16_t)pow(2,ledX - 2));
	}
}

void ledX_Clear(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_10 | GPIO_Pin_11);
	GPIO_SetBits(GPIOG,GPIO_Pin_2 
						| GPIO_Pin_3
						| GPIO_Pin_4
						| GPIO_Pin_5
						| GPIO_Pin_6
						| GPIO_Pin_7
						| GPIO_Pin_8
						| GPIO_Pin_9
						| GPIO_Pin_10);
}

void ledX_cmd(uint16_t ledX)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_10 | GPIO_Pin_11);
	GPIO_SetBits(GPIOG,GPIO_Pin_2 
						| GPIO_Pin_3
						| GPIO_Pin_4
						| GPIO_Pin_5
						| GPIO_Pin_6
						| GPIO_Pin_7
						| GPIO_Pin_8
						| GPIO_Pin_9
						| GPIO_Pin_10);
	
	ledX_light(ledX);
}

void ledX_light(uint16_t ledX)
{
	if(ledX < 2)
	{
		
		if(ledX == 0)
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		}
		else 
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		}	
	}
	else if(ledX >= 2 && ledX < 11)
	{
		GPIO_ResetBits(GPIOG,GPIO_Pin_2 * (uint16_t)pow(2,ledX - 2));
	}
}
