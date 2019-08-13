/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "knob.h"
#include "18B20.H"
#include "FlashEEPROM.H"
#include "waterlevel.h"
#include <string.h>
#include "FreeRTOS.h"
#include "mpu6050.h"
#include "mcp4541.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BUFFERSIZE 9

uint8_t ReceiveBuffer[BUFFERSIZE] = {0};

uint8_t IRReceive[9]={0};

uint8_t FlashRemember[10];
/*
Flash分布：FlashRemember[0]为CCR1即风扇1的值
          FlashRemember[1]为CCR2即风扇2的值
          FlashRemember[2]为所有雾化片的雾量
          FlashRemember[3]为雾化区1的雾量
          FlashRemember[4]为雾化区2的雾量
*/

uint8_t SpeedToSend[9]={0x5A,0xA5,0x06,0x82,0x10,0x09,0x00,0x10,0x00};
uint8_t RxEndFlag=0;
uint8_t RxLen=0;
extern osMessageQId usartQueue01Handle;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void InitAllPeriph(void);
void PrintInfo(uint8_t *String, uint32_t Size);
void SendMashineComond(uint8_t *x);
void USART1_Sevice1(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_TIM4_Init();
  MX_IWDG_Init();
//  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_Delay(100);
  InitAllPeriph();

  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enables the Clock Security System 
  */
  HAL_RCC_EnableCSS();
}

/* USER CODE BEGIN 4 */
void InitAllPeriph(void)
{
//  uint8_t i;
   HAL_GPIO_WritePin(TemperC_GPIO_Port, TemperC_Pin, GPIO_PIN_RESET);
  DS18B20_Init();
  WL_Init();
  if (HAL_TIM_Base_Start_IT(&htim1) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
//   printf("TIM1 Key扫描开始！\n"); 
//  printf("JDQ初始化完成！\n"); 
//  FFSTART_EN_DISABLE();
//  MFSTART_EN_DISABLE();
  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);		//风扇3
//  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
//  printf("PWM初始化完成！\n"); 
   // MPU6050_Init();  
//    printf("MPU6050初始化完成!\n");
 //STMFLASH_Write(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
  STMFLASH_Read(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
//  for(i=0;i<sizeof(FlashRemember);i++)
//  {
//    printf("Flash预存%d：%d\n",i,FlashRemember[i]);
//  }
  
  HAL_UART_Transmit(&huart1 , SpeedToSend, 9 , 0xffff);
  __HAL_UART_ENABLE_IT(&huart1,UART_IT_IDLE);
 // HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
        
//        HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);		//风扇3
//        HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
//        HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
//        HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
}


void MachineSTART(void)
{
  //    SendMashineComond(StopK);
  FFSTART_EN_ENABLE();
  MFSTART_EN_ENABLE();
  HAL_GPIO_WritePin(GPIOD,JDQ3_Pin|JDQ2_Pin|JDQ1_Pin, GPIO_PIN_RESET);
  
  TIM4->CCR1=FlashRemember[0]*10;
  TIM4->CCR3=FlashRemember[1]*10;
}

void MachineSTOP(void)
{
  MFSTART_EN_DISABLE();
  FFSTART_EN_DISABLE();
  HAL_GPIO_WritePin(GPIOD,JDQ3_Pin|JDQ2_Pin|JDQ1_Pin, GPIO_PIN_SET);
}

void PUMPStart(void)
{
  HAL_GPIO_WritePin(GPIOD, JDQ4_Pin, GPIO_PIN_RESET);
}

void PUMPStop(void)
{
  HAL_GPIO_WritePin(GPIOD, JDQ4_Pin, GPIO_PIN_SET);
}

void WHPStart(void)
{
  HAL_GPIO_WritePin(GPIOD,JDQ3_Pin, GPIO_PIN_RESET);
}

void WHPStop(void)
{
  HAL_GPIO_WritePin(GPIOD,JDQ3_Pin, GPIO_PIN_SET);
}

void FANStart(void)
{
  FFSTART_EN_ENABLE();
  MFSTART_EN_ENABLE();
  TIM4->CCR1=FlashRemember[0]*10;
  TIM4->CCR3=FlashRemember[1]*10;
}

void FANStop(void)
{
  MFSTART_EN_DISABLE();
  FFSTART_EN_DISABLE();
}

void WHPInit(void)
{
  WHPStop();
  osDelay(100);
  WHPStart();
  osDelay(300);
 // SetVolume(0x02,0x01);
  MCPWriteData(0x5e,0x00,0x01);
  osDelay(500);
 // SetVolume(0x02,0x80);
  MCPWriteData(0x5e,0x00,0x80);
  osDelay(500);
  MCPWriteData(0x5e,0x00,0x01);
  //  SetVolume(0x02,0x01);

}

//void SendMashineComond(uint8_t *x)
//{
//	 HAL_UART_Transmit(&huart1 , x, 9 , 0xffff);
//}
//
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle) 
//{
////  uint8_t i;
//  //    BaseType_t xHigherPriorityTaskWoken;
//  //   xHigherPriorityTaskWoken = pdFALSE;
//  if(UartHandle->Instance == USART1)  
//  {
//
//    HAL_UART_Receive_IT(&huart1,IRReceive,sizeof(IRReceive));
//    HAL_UART_Transmit(&huart1 , IRReceive, 9 , 0xffff);
////    for(i=0;i<sizeof(IRReceive);i++)
////    {
////      //printf("收到的数据为%d：%c\n",i,IRReceive[i]);
////      	 
////    }
//    if(IRReceive[0]==0x5A&&IRReceive[1]==0xA5)
//    {
//      if(IRReceive[4]==0x10&&IRReceive[5]==0x01)
//      {
//          UartReciveFlag=2;
//      }
//      else if(IRReceive[4]==0x10&&IRReceive[5]==0x02)
//      {
//          UartReciveFlag=1;
//      }
//      
//      else if(IRReceive[4]==0x10&&IRReceive[5]==0x03)
//      {
//           if(IRReceive[8]==0x01)
//           {
//              FFSTART_EN_ENABLE();
//              MFSTART_EN_ENABLE();
//           }
//           if(IRReceive[8]==0x00)
//           {
//              FFSTART_EN_DISABLE();
//              MFSTART_EN_DISABLE();
//           }
//      }
//      
//      else if(IRReceive[4]==0x10&&IRReceive[5]==0x04)
//      {
//           if(IRReceive[8]==0x01)
//           {
//            WHPStart();
//           }
//           if(IRReceive[8]==0x00)
//           {
//            WHPStop();
//           }
//      }
//      
//      else if(IRReceive[4]==0x10&&IRReceive[5]==0x05)
//      {
//           if(IRReceive[8]==0x01)
//           {
//            PumpON
//           }
//           if(IRReceive[8]==0x00)
//           {
//            PumpOFF
//           }
//      }
//      else if(IRReceive[4]==0x11&&IRReceive[5]==0x01)
//      {
//        TIM4->CCR1=IRReceive[7]*10;
//        FlashRemember[0] = IRReceive[7];
//      }
//      else if(IRReceive[4]==0x11&&IRReceive[5]==0x02)
//      {
//        TIM4->CCR3=IRReceive[7]*10;
//        FlashRemember[1] = IRReceive[7];
//      }
//      
//      else if(IRReceive[4]==0x11&&IRReceive[5]==0x03)
//      {
//        FlashRemember[3] = IRReceive[7];
//      }
//      
//      else if(IRReceive[4]==0x11&&IRReceive[5]==0x04)
//      {
//        FlashRemember[4] = IRReceive[7];
//      }
//      
//      else if(IRReceive[4]==0x11&&IRReceive[5]==0x05)
//      {
//        FlashRemember[2] = IRReceive[7];
//      }
//
//
//    HAL_UART_Receive_IT(&huart1,IRReceive,sizeof(IRReceive));
//
//  }
//     memset(IRReceive,0,sizeof(IRReceive));
//}
//}


//void HAL_UART_RxCpltCallback(UART_HandleTypeDef*UartHandle) 
//{
//  uint8_t temp;
//  if (UartHandle->Instance == USART1)
//  {
//    if(__HAL_UART_GET_FLAG(UartHandle,UART_FLAG_IDLE)!= RESET)
//    {
//      __HAL_UART_CLEAR_IDLEFLAG(UartHandle);
//      HAL_UART_DMAStop(UartHandle);
//      temp = __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);
//      RxLen = BUFFERSIZE - temp;
//      UartReciveFlag = 1;
//      HAL_UART_DMAResume(UartHandle);
//    }
//  }
//}

// void HAL_UART_ErrorCallback(UART_HandleTypeDef*UartHandle)
// {
//      if(UartHandle->Instance == USART1)  
//  {
//      MX_USART1_UART_Init();
//      HAL_UART_Receive_IT(&huart1,IRReceive,sizeof(IRReceive));
//  }
// }


void USART1_Sevice1(void)
{
  if (RxEndFlag == 1)
  {
 //   HAL_UART_Transmit(&huart1 , ReceiveBuffer, 9 , 0xffff);
    if(ReceiveBuffer[0]==0x5A&&ReceiveBuffer[1]==0xA5)
    {
      if(ReceiveBuffer[4]==0x10&&ReceiveBuffer[5]==0x01)                //设备总开关
      {
           MachineSTART();
      }
      else if(ReceiveBuffer[4]==0x10&&ReceiveBuffer[5]==0x02)
      {
           MachineSTOP();
      }
      
      else if(ReceiveBuffer[4]==0x10&&ReceiveBuffer[5]==0x03)   //风扇开关
      {
           if(ReceiveBuffer[8]==0x01)
           {
              FANStart();
           }
           if(ReceiveBuffer[8]==0x00)
           {
              FANStop();
           }
      }
      
      else if(ReceiveBuffer[4]==0x10&&ReceiveBuffer[5]==0x04)   //雾化片开关
      {
           if(ReceiveBuffer[8]==0x01)
           {
            WHPStart();
           }
           if(ReceiveBuffer[8]==0x00)
           {
            WHPStop();
           }
      }
      
      else if(ReceiveBuffer[4]==0x10&&ReceiveBuffer[5]==0x05)   //水泵开关
      {
           if(ReceiveBuffer[8]==0x01)
           {
            PumpON
           }
           if(ReceiveBuffer[8]==0x00)
           {
            PumpOFF
           }
      }
      else if(ReceiveBuffer[4]==0x11&&ReceiveBuffer[5]==0x01)   //FF的功率
      {
        TIM4->CCR1=ReceiveBuffer[7]*10;
        FlashRemember[0] = ReceiveBuffer[7];
      }
      else if(ReceiveBuffer[4]==0x11&&ReceiveBuffer[5]==0x02)   //MF的功率
      {
        TIM4->CCR3=ReceiveBuffer[7]*10;
        FlashRemember[1] = ReceiveBuffer[7];
      }
      
      else if(ReceiveBuffer[4]==0x11&&ReceiveBuffer[5]==0x03)    //雾化分区1的雾化功率
      {
        FlashRemember[3] = ReceiveBuffer[7];
      }
      
      else if(ReceiveBuffer[4]==0x11&&ReceiveBuffer[5]==0x04)   //雾化分区2的雾化功率
      {
        FlashRemember[4] = ReceiveBuffer[7];
      }
      
      else if(ReceiveBuffer[4]==0x11&&ReceiveBuffer[5]==0x05)   //雾化所有分区的雾化功率
      {
        FlashRemember[2] = ReceiveBuffer[7];
      }
      else if(ReceiveBuffer[4]==0x11&&ReceiveBuffer[5]==0x06)   //雾化重置
      {
        WHPInit();
      }
    }
  RxEndFlag = 0;
  }
  HAL_UART_Receive_DMA(&huart1,(uint8_t*)ReceiveBuffer,BUFFERSIZE);
}


//void USART_CharReception_Callback(void)
//{
// uint8_t received_char;
// // LL_USART_ClearFlag_RXNE(USART1);
//    received_char= LL_USART_ReceiveData8(USART1);
//
//    LL_USART_TransmitData8(USART1,received_char);  
//
//}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM1) {
//    key_scan();
//    Knob_covered_Votage();
    WL_scan();
  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
