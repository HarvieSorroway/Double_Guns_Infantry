//#include "usart.h"
//#include "dbus.h"

//uint8_t USART1_RX_BUF[2][BSP_USART1_DMA_RX_BUF_LEN];
//u16 length;

///*DBUS串口1初始化*/
//void usart6_init(void)
//{
//		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6,ENABLE);
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

//    USART_InitTypeDef USART_InitStructure;
//    GPIO_InitTypeDef GPIO_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStruct;
//    DMA_InitTypeDef DMA_InitStruct;

//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
//    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
//    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
//    GPIO_InitStructure.GPIO_Speed=GPIO_Low_Speed;
//    GPIO_Init(GPIOB,&GPIO_InitStructure);

//    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

//    USART_InitStructure.USART_BaudRate=100000;
//    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
//    USART_InitStructure.USART_Mode=USART_Mode_Rx;
//    USART_InitStructure.USART_StopBits=USART_StopBits_1;
//    USART_InitStructure.USART_Parity=USART_Parity_Even;
//    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
//    USART_Init(USART1,&USART_InitStructure);

//    USART_Cmd(USART1,ENABLE);

//    DMA_DeInit(DMA2_Stream2);

//    while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE) {}

//    DMA_InitStruct.DMA_Channel=DMA_Channel_4;
//    DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&(USART1->DR);
//    DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)&USART1_RX_BUF[0][0];
//    DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
//    DMA_InitStruct.DMA_BufferSize=BSP_USART1_DMA_RX_BUF_LEN;
//    DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
//    DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
//    DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
//    DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
//    DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
//    DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
//    DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
//    DMA_InitStruct.DMA_FIFOThreshold=DMA_FIFOThreshold_1QuarterFull;
//    DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
//    DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
//    DMA_Init(DMA2_Stream2,&DMA_InitStruct);

//    DMA_DoubleBufferModeConfig(DMA2_Stream2,(uint32_t)&USART1_RX_BUF[1][0],DMA_Memory_0);
//    DMA_DoubleBufferModeCmd(DMA2_Stream2,ENABLE);

//    DMA_Cmd(DMA2_Stream2,ENABLE);

//    NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
//    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
//    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
//    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//    NVIC_Init(&NVIC_InitStruct);

//    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
//    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
//}

//void USART1_IRQHandler(void)
//{
//    static uint32_t this_time_rx_len = 0;
//    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
//        {
//            //clear the idle pending flag
//            (void)USART1->SR;
//            (void)USART1->DR;
//            if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
//                {
//                    DMA_Cmd(DMA2_Stream2, DISABLE);
//                    this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
//                    DMA2_Stream2->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
//                    DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);
//                    DMA_Cmd(DMA2_Stream2, ENABLE);
//                    if(this_time_rx_len == RC_FRAME_LENGTH)
//                        {
//                            dbus_data_process(USART1_RX_BUF[0]);
//                        }
//                }
//            else
//                {
//                    DMA_Cmd(DMA2_Stream2, DISABLE);
//                    this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
//                    DMA2_Stream2->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
//                    DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);
//                    DMA_Cmd(DMA2_Stream2, ENABLE);
//                    if(this_time_rx_len == RC_FRAME_LENGTH)
//                        {
//                            dbus_data_process(USART1_RX_BUF[1]);
//                        }
//                }
//        }
//}

#include "usart.h"
#include "dbus.h"



void usart6_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
//	NVIC_InitTypeDef NVIC_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOG,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed=GPIO_High_Speed;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_UP;
	
	GPIO_Init(GPIOG,&GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
	
	USART_InitStruct.USART_BaudRate=115200;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;//bit byte
	
	
	USART_Init(USART6,&USART_InitStruct);
	USART_Cmd(USART6,ENABLE);
	
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	
//	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
//	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
//	NVIC_Init(&NVIC_InitStruct);
}

void usart_send(uint8_t ch)
{
	USART_SendData(USART6,ch);//用串口6传送数据
	while(USART_GetFlagStatus(USART6,USART_FLAG_TXE)==RESET);

}


uint8_t USART1_RX_BUF[2][BSP_USART1_DMA_RX_BUF_LEN];
u16 length;

/*DBUS遥控器串口1初始化*/
void usart1_init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef usart;
	  NVIC_InitTypeDef NVIC_InitStructure;    
		DMA_InitTypeDef DMA_InitStructure;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
    
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
    
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    USART_DeInit(USART1);
	
    USART_StructInit(&usart);
    usart.USART_BaudRate = 100000; //波特率设置
    usart.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
    usart.USART_StopBits = USART_StopBits_1;//一个停止位
    usart.USART_Parity = USART_Parity_Even;//
    usart.USART_Mode = USART_Mode_Rx;	//接收模式
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
    USART_Init(USART1, &usart);//开始初始化串口1
    
		USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE); //使能串口1的DMA发送  
    DMA_DeInit(DMA2_Stream5); //收是数据流5，发是数据流7
		
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;  //选择通道4
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);//DMA外设地址为串口1
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART1_RX_BUF[0];//DMA 存储器0地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//外设到存储器模式
    DMA_InitStructure.DMA_BufferSize = BSP_USART1_DMA_RX_BUF_LEN;//设置数据传输量
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设非增量模式
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//存储器增量模式
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据长度:8位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//存储器数据长度:8位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// 使用 ？？模式 
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//存储器突发单次传输
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//外设突发单次传输
    DMA_Init(DMA2_Stream5, &DMA_InitStructure);//初始化DMA Stream
    
    //配置Memory1,Memory0是第一个使用的Memory
    DMA_DoubleBufferModeConfig(DMA2_Stream5, (uint32_t)USART1_RX_BUF[1], DMA_Memory_0);   //first used memory configuration
    DMA_DoubleBufferModeCmd(DMA2_Stream5, ENABLE);
    
    DMA_Cmd(DMA2_Stream5, ENABLE);
    
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;                          
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //pre-emption priority 
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		    //subpriority 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
		NVIC_Init(&NVIC_InitStructure);	
    
		USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);        //usart rx idle interrupt  enabled
    USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void)
{
    static uint32_t this_time_rx_len = 0;
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
        {
            //clear the idle pending flag
            (void)USART1->SR;
            (void)USART1->DR;
//            RC_CtrlData.online_flag=1;
					length=BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream5);
            if(DMA_GetCurrentMemoryTarget(DMA2_Stream5) == 0)
                {
                    DMA_Cmd(DMA2_Stream5, DISABLE);
                    this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream5);
                    DMA2_Stream5->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
                    DMA2_Stream5->CR |= (uint32_t)(DMA_SxCR_CT);
                    DMA_Cmd(DMA2_Stream5, ENABLE);
                    if(this_time_rx_len == RC_FRAME_LENGTH)
                        {
														dbus_data_process(USART1_RX_BUF[0]);
                        }
                }
            else
                {
                    DMA_Cmd(DMA2_Stream5, DISABLE);
                    this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream5);
                    DMA2_Stream5->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
                    DMA2_Stream5->CR &= ~(uint32_t)(DMA_SxCR_CT);
                    DMA_Cmd(DMA2_Stream5, ENABLE);
                    if(this_time_rx_len == RC_FRAME_LENGTH)
                            
												{
														dbus_data_process(USART1_RX_BUF[1]);
												}  
                }
        }
}
