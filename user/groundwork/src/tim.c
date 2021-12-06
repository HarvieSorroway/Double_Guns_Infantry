#include "tim.h"

int counter = 0;
int nvic_flag = 0;


#define ADVANCE_TIM TIM1

void TIM3_PWM_Init()
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; //��������ģʽΪͨ���������
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
 
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
   GPIO_Init(GPIOE, &GPIO_InitStruct); //���ÿ⺯������ʼ��GPIOC

	
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //����TIM1ʱ��
 
//ʱ���ṹ������
  TIM_TimeBaseStructure.TIM_Period = 1000-1;     //��0��ʼ���� һ������1000��
  TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //������Ƶ��Ϊ10kHz  ��ʱ��ʱ�ӣ�72MHz/7200=10kHz ���ڣ���1/10kHz��*1000=100ms
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����Ҫ��Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ʽ ���ϼ���
  TIM_TimeBaseStructure.TIM_RepetitionCounter=0; //�ظ�������
  TIM_TimeBaseInit(ADVANCE_TIM, &TIM_TimeBaseStructure); //���ÿ⺯������ʼ��TIM1
 
//����ȽϽṹ������
  TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;//ѡ��PWM1ģʽ
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�ź����ʹ��
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//�����ź����ʹ��
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 

 
//��ʼ��TIM1ͨ����
  TIM_OCInitStructure.TIM_Pulse = 100; //ռ�ձ�=600/1000=60%
  TIM_OC2Init(ADVANCE_TIM,&TIM_OCInitStructure);
  TIM_OC2PreloadConfig(ADVANCE_TIM,TIM_OCPreload_Enable);
 
//�����Ͷ�·�ṹ������
  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;
  TIM_BDTRInitStructure.TIM_DeadTime = 0x80;
  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;
  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_Low;//�͵�ƽ��Ч��������ż�⵽�ߵ�ƽ���ֹͣPWM���������������κβ���
  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
  TIM_BDTRConfig(ADVANCE_TIM,&TIM_BDTRInitStructure);
 
//ʹ�ܶ�ʱ������������ʼ����
  TIM_Cmd(ADVANCE_TIM, ENABLE);  
//�������ʹ��
  TIM_CtrlPWMOutputs(ADVANCE_TIM,ENABLE);


}

void TIM3_IRQHandler()
{
	 if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	 {
		counter++;
		if(counter == 100)
		{
			if(nvic_flag)GPIO_ResetBits(GPIOE,GPIO_Pin_11);
			else GPIO_SetBits(GPIOE,GPIO_Pin_11); 
			nvic_flag = !nvic_flag;
			counter = 0;
		}
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
	 }
}