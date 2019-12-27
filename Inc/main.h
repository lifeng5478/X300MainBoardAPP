/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "cmsis_os.h"
extern osSemaphoreId Uart1_Semaph;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
typedef struct{
  uint8_t connect;
  uint8_t pumpstatus;
  uint8_t whppower;
  uint8_t fansff;
  uint8_t fansmf;
  uint8_t whpstatus;
  uint8_t water1;
  uint8_t water2;
}machine_strcut;

extern machine_strcut Machine_status_strc;

extern uint8_t MachineSTATUS[13];
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void MachineSTART(void);
void MachineSTOP(void);
void PUMPStart(void);
void PUMPStop(void);
void USART1_Sevice1(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_2
#define LED1_GPIO_Port GPIOE
#define LED2_Pin GPIO_PIN_3
#define LED2_GPIO_Port GPIOE
#define LED3_Pin GPIO_PIN_4
#define LED3_GPIO_Port GPIOE
//#define KEY1_EVQQ7_Pin GPIO_PIN_7
//#define KEY1_EVQQ7_GPIO_Port GPIOA
//#define KEY4_EVQQ7_Pin GPIO_PIN_4
//#define KEY4_EVQQ7_GPIO_Port GPIOC
//#define KEY5_EVQQ7_Pin GPIO_PIN_5
//#define KEY5_EVQQ7_GPIO_Port GPIOC
//#define KEY2_EVQQ7_Pin GPIO_PIN_0
//#define KEY2_EVQQ7_GPIO_Port GPIOB
//#define KEY3_EVQQ7_Pin GPIO_PIN_1
//#define KEY3_EVQQ7_GPIO_Port GPIOB
//#define KNOB1_Pin GPIO_PIN_7
//#define KNOB1_GPIO_Port GPIOE
//#define KNOB2_Pin GPIO_PIN_8
//#define KNOB2_GPIO_Port GPIOE
//#define OLEDCS2_Pin GPIO_PIN_10
//#define OLEDCS2_GPIO_Port GPIOE
//#define OLEDFS0_Pin GPIO_PIN_11
//#define OLEDFS0_GPIO_Port GPIOE
//#define OLEDCS1_Pin GPIO_PIN_12
//#define OLEDCS1_GPIO_Port GPIOE
//#define OLEDDC_Pin GPIO_PIN_13
//#define OLEDDC_GPIO_Port GPIOE
//#define OLEDMOSI_Pin GPIO_PIN_14
//#define OLEDMOSI_GPIO_Port GPIOE
//#define OLEDCLK_Pin GPIO_PIN_15
//#define OLEDCLK_GPIO_Port GPIOE
#define FAN1EN_Pin GPIO_PIN_10
#define FAN1EN_GPIO_Port GPIOD
#define FANS2EN_Pin GPIO_PIN_11
#define FANS2EN_GPIO_Port GPIOD
#define MFCATHODE_Pin GPIO_PIN_13
#define MFCATHODE_GPIO_Port GPIOD
#define FFCATHODE_Pin GPIO_PIN_15
#define FFCATHODE_GPIO_Port GPIOD
#define TemperC_Pin GPIO_PIN_12
#define TemperC_GPIO_Port GPIOC
#define JDQ1_Pin GPIO_PIN_8
#define JDQ1_GPIO_Port GPIOE
#define JDQ2_Pin GPIO_PIN_9
#define JDQ2_GPIO_Port GPIOE
#define JDQ3_Pin GPIO_PIN_10
#define JDQ3_GPIO_Port GPIOE
#define JDQ4_Pin GPIO_PIN_11
#define JDQ4_GPIO_Port GPIOE
#define WaterLevel1_Pin GPIO_PIN_4
#define WaterLevel1_GPIO_Port GPIOC
#define WaterLevel2_Pin GPIO_PIN_5
#define WaterLevel2_GPIO_Port GPIOC
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
