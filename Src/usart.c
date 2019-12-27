/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
uint8_t SendLock = 0;
uint8_t CntSend = 0;
uint8_t SendUpdate = 0;
uint8_t RxMFlag = 0;

uint8_t ReceiveBuffer2[20]={0};
uint8_t bufcount = 0;


//串口协议编制
/*
起始	地址	连接状态	水泵状态	雾化片JDQ	风扇FF状态	风扇MF状态	雾化片状态	水位传感器1状态	水位传感器2状态	结束
Byte1-2	Byte3-4	Byte5	        Byte6	        Byte7	        Byte8	        Byte9	        Byte10	        Byte11	        Byte12	        Byte13
uint8_t MashineSTATUS = {1,2,3,4,5,6,7,8,9,10,11,12,13};
起始设置 0x5A 0xA5
地址默认设置为：0x80
连接状态默认为:0x00
水泵状态默认为:0x00
雾化片JDQ默认为:0x00
风扇FF状态默认为:0x00
风扇MF状态默认为:0x00
雾化片状态默认为:0x00
水位传感器1状态默认为:0x00
水位传感器2状态默认为:0x00
结束位默认为0xA5
*/

uint8_t MachineSTATUS[13]={0x5A,0xA5,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xA5};
machine_strcut Machine_status_strc = {0,0,0,0,0,0,0,0}; 
/* USER CODE END 0 */ 

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel5;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_NORMAL;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel4;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(uartHandle,hdmatx,hdma_usart1_tx);

  /* USER CODE BEGIN USART1_MspInit 1 */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
//int fputc(int ch, FILE *f){
//    while((USART1->SR&0X40)==0);
//    USART1->DR = (uint8_t) ch;
//    return ch;
//}


HAL_StatusTypeDef Serial_PutByte(UART_HandleTypeDef *huart,uint8_t param )
{
	huart->Instance->DR = param;
	while(__HAL_UART_GET_FLAG(huart,UART_FLAG_TC)==RESET);
        return HAL_OK;
}

void Serial_PutString(UART_HandleTypeDef *huart,uint8_t *p_string,uint8_t len)
{
	uint8_t i;
		for (i = 0;i<len;i++)
		Serial_PutByte(huart,p_string[i]);
}


void TimUart(void)
{
  if (SendUpdate==1)                              //数据接收时锁死！
  {
    //HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_RESET);
    SendLock = 1;
    ++CntSend;
    if(CntSend>= 20)                              //超过20ms没有数据进来进入处理数据环节
    {
      //      HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin,GPIO_PIN_SET);
      CntSend = 0;
      SendUpdate = 0;
    }
  }
  
  else if (SendLock == 1)                       //锁死数据，准备处理数据
  {
    bufcount = 0;
    SendLock = 0;
    RxMFlag = 1;
  }
}

double tempHXtemp = 0;
double tempFYtemp = 0;
double tempHGtemp = 0;
void usart2_sevice(void)
{
  double tempHX = 0;
  double tempFY = 0;
  double tempHG = 0;
  if(RxMFlag == 1)
  {
    //Serial_PutString(&huart2,ReceiveBuffer2,sizeof(ReceiveBuffer2));
    RxMFlag = 0;
    if(ReceiveBuffer2[0]==0XAA&&ReceiveBuffer2[7]==0x55)
    {

      tempHX = (double)(ReceiveBuffer2[1]<<8|ReceiveBuffer2[2]) / 100.0;
      if(tempHX>180)
      {
        tempHX = -(655.36-tempHX);
      }
      if((tempHX-tempHXtemp>1)||(tempHXtemp-tempHX>1))
      {
        printf("航向角：%f\r\n",tempHX);
        tempHXtemp = tempHX;
      }
      tempFY = (double)(ReceiveBuffer2[3]<<8|ReceiveBuffer2[4]) / 100.0;
      if(tempFY>180)
      {
        tempFY = -(655.36-tempFY);
      }
      if((tempFY-tempFYtemp>1)||(tempFYtemp-tempFY>1))
      {
        printf("俯仰角：%f\r\n",tempFY);
        tempFYtemp = tempFY;
      }
      tempHG = (double)(ReceiveBuffer2[5]<<8|ReceiveBuffer2[6]) / 100.0;
      if(tempHG>180)
      {
        tempHG = -(655.36-tempHG);
      }
      if((tempHG-tempHGtemp>1)||(tempHGtemp-tempHG>1))
      {
        printf("横滚角：%f\r\n",tempHG);
        tempHGtemp = tempHG;
      }

    }
    memset (ReceiveBuffer2,0,sizeof(ReceiveBuffer2));
    bufcount = 0;
  }
}


void machine_date_update(void)
{
  if (Machine_status_strc.connect!=MachineSTATUS[4])
  {
   MachineSTATUS[4] = Machine_status_strc.connect;
  }
    if (Machine_status_strc.pumpstatus!=MachineSTATUS[5])
  {
    MachineSTATUS[5] = Machine_status_strc.pumpstatus;
  }
    if (Machine_status_strc.whppower!=MachineSTATUS[6])
  {
    MachineSTATUS[6] = Machine_status_strc.whppower;
  }
    if (Machine_status_strc.fansff!=MachineSTATUS[7])
  {
    MachineSTATUS[7] = Machine_status_strc.fansff;
  }
    if (Machine_status_strc.fansmf!=MachineSTATUS[8])
  {
    MachineSTATUS[8] = Machine_status_strc.fansmf;
  }
    if (Machine_status_strc.whpstatus!=MachineSTATUS[9])
  {
    MachineSTATUS[9] = Machine_status_strc.whpstatus;
  }
    if (Machine_status_strc.water1!=MachineSTATUS[10])
  {
    MachineSTATUS[10] = Machine_status_strc.water1;
  }
    if (Machine_status_strc.water2!=MachineSTATUS[11])
  {
    MachineSTATUS[11] = Machine_status_strc.water2;
  }
}

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    //具体哪个串口可以更改huart1为其它串口
    HAL_UART_Transmit(&huart2 , (uint8_t *)&ch, 1 , 0xffff);
    return ch;
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
