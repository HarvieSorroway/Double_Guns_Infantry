#include "dbus.h"
#include "stddef.h"
#include "led.h"

/* ----------------------- RC Channel Definition---------------------------- */
#define RC_CH_VALUE_MIN ((uint16_t)364 )
#define RC_CH_VALUE_OFFSET ((uint16_t)1024)
#define RC_CH_VALUE_MAX ((uint16_t)1684)
/* ----------------------- RC Switch Definition----------------------------- */
#define RC_SW_UP ((uint16_t)1)
#define RC_SW_MID ((uint16_t)3)
#define RC_SW_DOWN ((uint16_t)2)
/* ----------------------- PC Key Definition-------------------------------- */
#define KEY_PRESSED_OFFSET_W ((uint16_t)0x01<<0)
#define KEY_PRESSED_OFFSET_S ((uint16_t)0x01<<1)
#define KEY_PRESSED_OFFSET_A ((uint16_t)0x01<<2)
#define KEY_PRESSED_OFFSET_D ((uint16_t)0x01<<3)
#define KEY_PRESSED_OFFSET_Q ((uint16_t)0x01<<4)
#define KEY_PRESSED_OFFSET_E ((uint16_t)0x01<<5)
#define KEY_PRESSED_OFFSET_SHIFT ((uint16_t)0x01<<6)
#define KEY_PRESSED_OFFSET_CTRL ((uint16_t)0x01<<7)
#define RC_FRAME_LENGTH 18
#define BSP_USART1_DMA_RX_BUF_LEN 19
/* ----------------------- Data Struct ------------------------------------- */


/* ----------------------- Internal Data ----------------------------------- */
uint8_t USART1_RX_BUF[2][BSP_USART1_DMA_RX_BUF_LEN]; //double sbus rx buffer to save data
RC_Ctl_t RC_CtrlData;
/* ----------------------- Function Implements ---------------------------- */
/******************************************************************************
* @fn RC_Init
* 
* @brief configure stm32 usart2 port
* - USART Parameters
* - 100Kbps
* - 8-N-1
* - DMA Mode
* 
* @return None.
* 
* @note This code is fully tested on STM32F405RGT6 Platform, You can port 
it
* to the other platform. Using doube buffer to receive data prevent 
losing data.
*/
void RC_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStruct;
    DMA_InitTypeDef DMA_InitStruct;

    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Low_Speed;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

    USART_InitStructure.USART_BaudRate=100000;
    USART_InitStructure.USART_WordLength=USART_WordLength_8b;
    USART_InitStructure.USART_Mode=USART_Mode_Rx;
    USART_InitStructure.USART_StopBits=USART_StopBits_1;
    USART_InitStructure.USART_Parity=USART_Parity_Even;
    USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init(USART1,&USART_InitStructure);

    USART_Cmd(USART1,ENABLE);

    DMA_DeInit(DMA2_Stream2);

    while (DMA_GetCmdStatus(DMA2_Stream2) != DISABLE) {}

    DMA_InitStruct.DMA_Channel=DMA_Channel_4;
    DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)&(USART1->DR);
    DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)&USART1_RX_BUF[0][0];
    DMA_InitStruct.DMA_DIR=DMA_DIR_PeripheralToMemory;
    DMA_InitStruct.DMA_BufferSize=BSP_USART1_DMA_RX_BUF_LEN;
    DMA_InitStruct.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
    DMA_InitStruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_Mode=DMA_Mode_Circular;
    DMA_InitStruct.DMA_Priority=DMA_Priority_Medium;
    DMA_InitStruct.DMA_FIFOMode=DMA_FIFOMode_Disable;
    DMA_InitStruct.DMA_FIFOThreshold=DMA_FIFOThreshold_1QuarterFull;
    DMA_InitStruct.DMA_MemoryBurst=DMA_MemoryBurst_Single;
    DMA_InitStruct.DMA_PeripheralBurst=DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream2,&DMA_InitStruct);

    DMA_DoubleBufferModeConfig(DMA2_Stream2,(uint32_t)&USART1_RX_BUF[1][0],DMA_Memory_0);
    DMA_DoubleBufferModeCmd(DMA2_Stream2,ENABLE);

    DMA_Cmd(DMA2_Stream2,ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
    USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	
	RC_CtrlData.rc.ch0 = 0;
	RC_CtrlData.rc.ch1 = 0;
	RC_CtrlData.rc.ch2 = 0;
	RC_CtrlData.rc.ch3 = 0;
	 
	RC_CtrlData.rc.s1 = 0;
	RC_CtrlData.rc.s2 = 0;
	RC_CtrlData.mouse.x = 0;
	RC_CtrlData.mouse.y = 0;
	RC_CtrlData.mouse.z = 0;
	RC_CtrlData.mouse.press_l = 0;
	RC_CtrlData.mouse.press_r = 0;
	RC_CtrlData.key.v = 0;
}

/******************************************************************************
* @fn RemoteDataProcess
* 
* @brief resolution rc protocol data.
* @pData a point to rc receive buffer.
* @return None.
* @note RC_CtrlData is a global variable.you can deal with it in other place.
*/
void RemoteDataProcess(uint8_t *pData)
{
	if(pData == NULL)
	{
		return;
	}
 
	 RC_CtrlData.rc.ch0 = ((int16_t)pData[0] | ((int16_t)pData[1] << 8)) & 0x07FF; 
	 RC_CtrlData.rc.ch1 = (((int16_t)pData[1] >> 3) | ((int16_t)pData[2] << 5)) & 0x07FF;
	 RC_CtrlData.rc.ch2 = (((int16_t)pData[2] >> 6) | ((int16_t)pData[3] << 2) | ((int16_t)pData[4] << 10)) & 0x07FF;
	 RC_CtrlData.rc.ch3 = (((int16_t)pData[4] >> 1) | ((int16_t)pData[5]<<7)) & 0x07FF;
	 
	 RC_CtrlData.rc.s1 = ((pData[5] >> 4) & 0x000C) >> 2;
	 RC_CtrlData.rc.s2 = ((pData[5] >> 4) & 0x0003);
	 RC_CtrlData.mouse.x = ((int16_t)pData[6]) | ((int16_t)pData[7] << 8);
	 RC_CtrlData.mouse.y = ((int16_t)pData[8]) | ((int16_t)pData[9] << 8);
	 RC_CtrlData.mouse.z = ((int16_t)pData[10]) | ((int16_t)pData[11] << 8); 
	 RC_CtrlData.mouse.press_l = pData[12];
	 RC_CtrlData.mouse.press_r = pData[13];
	 RC_CtrlData.key.v = ((int16_t)pData[14]);// | ((int16_t)pData[15] << 8);
	 //your control code бн.

	 //USART_sendStrFromRemote(&RC_CtrlData);
}
/******************************************************************************
* @fn USART2_IRQHandler
* 
* @brief USART2 irq, we are care of ilde interrupt that means receiving the 
one frame datas is finished.
*
* @return None.
*
* @note This code is fully tested on STM32F405RGT6 Platform, You can port 
it
* to the other platform.
*/
void USART1_IRQHandler (void)
{
	static uint32_t this_time_rx_len = 0;
    if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
    {
		//clear the idle pending flag
        (void)USART1->SR;
        (void)USART1->DR;
        //RC_CtrlData.online_flag=1;
        if(DMA_GetCurrentMemoryTarget(DMA2_Stream2) == 0)
        {
			DMA_Cmd(DMA2_Stream2, DISABLE);
            this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
            DMA2_Stream2->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
            DMA2_Stream2->CR |= (uint32_t)(DMA_SxCR_CT);
            DMA_Cmd(DMA2_Stream2, ENABLE);
            if(this_time_rx_len == RC_FRAME_LENGTH)
            {
				RemoteDataProcess(USART1_RX_BUF[0]);
            }
        }
        else
        {
			DMA_Cmd(DMA2_Stream2, DISABLE);
            this_time_rx_len = BSP_USART1_DMA_RX_BUF_LEN - DMA_GetCurrDataCounter(DMA2_Stream2);
            DMA2_Stream2->NDTR = (uint16_t)BSP_USART1_DMA_RX_BUF_LEN;
            DMA2_Stream2->CR &= ~(uint32_t)(DMA_SxCR_CT);
            DMA_Cmd(DMA2_Stream2, ENABLE);
            if(this_time_rx_len == RC_FRAME_LENGTH)
            {
				RemoteDataProcess(USART1_RX_BUF[1]);
            }
        }
	}
}	
