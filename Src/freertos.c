/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "key.h"
#include "waterlevel.h"
#include "iwdg.h"
#include "usart.h"
#include "mpu6050.h"
#include "mcp4541.h"
#include "gy25.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern uint8_t IRReceive[3];
float temper;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId WaterLevelTaskHandle;
osThreadId WatchDogTaskHandle;
osThreadId TemperTASKHandle;
osThreadId MenuFunctionTasHandle;
osThreadId MPU6050TaskHandle;
osMessageQId usartQueue01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void WaterLevelScan(void const * argument);
void WatchDogRST(void const * argument);
void ReadTemper(void const * argument);
void MenuFunc(void const * argument);
void ReadMPU6050(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of usartQueue01 */
  osMessageQDef(usartQueue01, 16, uint16_t);
  usartQueue01Handle = osMessageCreate(osMessageQ(usartQueue01), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of WaterLevelTask */
  osThreadDef(WaterLevelTask, WaterLevelScan, osPriorityAboveNormal, 0, 128);
  WaterLevelTaskHandle = osThreadCreate(osThread(WaterLevelTask), NULL);

  /* definition and creation of WatchDogTask */
  osThreadDef(WatchDogTask, WatchDogRST, osPriorityIdle, 0, 128);
  WatchDogTaskHandle = osThreadCreate(osThread(WatchDogTask), NULL);

  /* definition and creation of TemperTASK */
  osThreadDef(TemperTASK, ReadTemper, osPriorityIdle, 0, 128);
  TemperTASKHandle = osThreadCreate(osThread(TemperTASK), NULL);

  /* definition and creation of MenuFunctionTas */
  osThreadDef(MenuFunctionTas, MenuFunc, osPriorityIdle, 0, 128);
  MenuFunctionTasHandle = osThreadCreate(osThread(MenuFunctionTas), NULL);

  /* definition and creation of MPU6050Task */
  osThreadDef(MPU6050Task, ReadMPU6050, osPriorityIdle, 0, 128);
  MPU6050TaskHandle = osThreadCreate(osThread(MPU6050Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
 // display_GB2312_string(0,0,"你哈！");
  for(;;)
  {
    osDelay(100);
    HAL_GPIO_TogglePin(GPIOE,LED1_Pin);
    osDelay(100);
//    HAL_GPIO_TogglePin(GPIOE,LED2_Pin);
//    osDelay(100);
//    HAL_GPIO_TogglePin(GPIOE,LED3_Pin); 
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_WaterLevelScan */
/**
* @brief Function implementing the WaterLevelTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_WaterLevelScan */
void WaterLevelScan(void const * argument)
{
  /* USER CODE BEGIN WaterLevelScan */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    WLSevice();
//    if(WaterFlag)
//    {
//        HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_SET);
//    }
//    else
//    {
//       HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_RESET);
//    }
  }
  /* USER CODE END WaterLevelScan */
}

/* USER CODE BEGIN Header_WatchDogRST */
/**
* @brief Function implementing the WatchDogTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_WatchDogRST */
void WatchDogRST(void const * argument)
{
  /* USER CODE BEGIN WatchDogRST */
  /* Infinite loop */
  for(;;)
  {
 //   KeySevice();
    osDelay(1);
    HAL_IWDG_Refresh(&hiwdg);
  }
  /* USER CODE END WatchDogRST */
}

/* USER CODE BEGIN Header_ReadTemper */
/**
* @brief Function implementing the TemperTASK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ReadTemper */
#include "i2c.h"
void ReadTemper(void const * argument)
{
  /* USER CODE BEGIN ReadTemper */
//  	uint8_t aa;
//    short Accel[3];
//	short Gyro [3];
//	short Temp;
//     if (MPU6050ReadID() == 0)
//	{	
//    printf("检测不到MPU6050，停机");
//	  while(1);
//        }
//SetVolume(0x02,23);    
  /* Infinite loop */
  for(;;)
  {
//    aa++;
//    if(aa>=0x40)
//      aa=0;
//     MCPWriteData(Device_2,0X00,aa);
//     MCPReadData(0x5d,0xc0,aa);
  //  temper=DS18B20_GetTemp_SkipRom();
   // sprintf(aa,"%5.2f",temper);
  //  display_GB2312_string(3,40,aa);
  //  osDelay(200);
//    HAL_UART_Receive(&huart1,IRReceive,3,0xff);
//    xQueueSendToBackFromISR (usartQueue01Handle,IRReceive,&xHigherPriorityTaskWoken);
//    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    
   
//    MPU6050ReadAcc(Accel);
//    printf("\r\n加速度： %8d%8d%8d    ",Accel[0],Accel[1],Accel[2]);
//          MPU6050ReadGyro(Gyro);
//      printf("陀螺仪： %8d%8d%8d    ",Gyro[0],Gyro[1],Gyro[2]);
//      
//      MPU6050_ReturnTemp(&Temp);
//      printf("温度： %d",Temp);
   //   osDelay(200);
   MCP4541Sevice();

 //           osDelay(1);


    osDelay(200);
  }
  /* USER CODE END ReadTemper */
}

/* USER CODE BEGIN Header_MenuFunc */
/**
* @brief Function implementing the MenuFunctionTas thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MenuFunc */
void MenuFunc(void const * argument)
{
  /* USER CODE BEGIN MenuFunc */
  osDelay(1000);
  
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
    USART1_Sevice1();
  }
  /* USER CODE END MenuFunc */
}

/* USER CODE BEGIN Header_ReadMPU6050 */
/**
* @brief Function implementing the MPU6050Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_ReadMPU6050 */
void ReadMPU6050(void const * argument)
{
  static uint16_t timeer1 = 0;
  /* USER CODE BEGIN ReadMPU6050 */
  //HAL_UART_Receive_IT(&huart1,IRReceive,9);
//   printf("开始接收USART数据信号！\n"); 
  /* Infinite loop */
  __HAL_UART_ENABLE_IT(&huart2,UART_IT_RXNE);	
  for(;;)
  {

    timeer1++;
    if(timeer1>=50)
    {
      timeer1=0;
      //Serial_PutByte(&huart2,0x01);
    // GY25_inquiries();
    }
    usart2_sevice();
    osDelay(1);
  }
  /* USER CODE END ReadMPU6050 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
