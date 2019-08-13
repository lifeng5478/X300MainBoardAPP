#include "waterlevel.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#define  GetWL1_H  HAL_GPIO_ReadPin(WaterLevel1_GPIO_Port,WaterLevel1_Pin)==1
#define  GetWL1_L  HAL_GPIO_ReadPin(WaterLevel1_GPIO_Port,WaterLevel1_Pin)==0
#define  GetWL2_H  HAL_GPIO_ReadPin(WaterLevel2_GPIO_Port,WaterLevel2_Pin)==1
#define  GetWL2_L  HAL_GPIO_ReadPin(WaterLevel2_GPIO_Port,WaterLevel2_Pin)==0

#define const_WL_time 200
#define ShutDownTime 5000

unsigned char ucWLSec=0;   //按键选择
unsigned int  uiWLTimeCnt1=0; 	//按键1去抖时间
unsigned char ucWLLock1=0;   //按键1自锁防止持续触发

//unsigned int  uiWLTimeCnt2=0;  //按键2去抖时间
//unsigned char ucWLLock2=0; //按键2自锁防止持续触发



uint8_t PUMPWL1ON[9]={0x5A, 0xA5, 0x06, 0x82, 0x10, 0x01, 0x00, 0x00, 0x00 };
uint8_t PUMPWL1OFF[9]={0x5A, 0xA5, 0x06, 0x82, 0x10, 0x01, 0x00, 0x01, 0x00 };

uint8_t PUMPWL2ON[9]={0x5A, 0xA5, 0x06, 0x82, 0x10, 0x02, 0x00, 0x00, 0x00 };
uint8_t PUMPWL2OFF[9]={0x5A, 0xA5, 0x06, 0x82, 0x10, 0x02, 0x00, 0x01, 0x00 };

uint8_t ucWLLockIn1=0;
uint8_t ucWLLockOut1=0;
uint16_t uiWLTimeCntOut1=0;
uint16_t uiWLTimeCntIn1=0;

uint8_t ucWLLockIn2=0;
uint8_t ucWLLockOut2=0;
uint16_t uiWLTimeCntOut2=0;
uint16_t uiWLTimeCntIn2=0;

uint8_t WaterFlag;
uint8_t WaterFlag1;
uint8_t FlagAll;


void WL_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	   __HAL_RCC_GPIOB_CLK_ENABLE();
  /*Configure GPIO pins : PA12 PA15 */
  GPIO_InitStruct.Pin = WaterLevel1_Pin|WaterLevel2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void SendWL1ON(void)
{
 HAL_UART_Transmit(&huart1,PUMPWL1ON,9,0X0F);
}


void SendWL1OFF(void)
{
 HAL_UART_Transmit(&huart1,PUMPWL1OFF,9,0X0F);
}

void SendWL2ON(void)
{
 HAL_UART_Transmit(&huart1,PUMPWL2ON,9,0X0F);
}

void SendWL2OFF(void)
{
 HAL_UART_Transmit(&huart1,PUMPWL2OFF,9,0X0F);
}


void WL_scan(void)
{
	
//  if(GetWL1_H)
//  {
//        ucWLLock1=0; 
//        uiWLTimeCnt1=0;
//  }
//  else if(ucWLLock1==0)
//  {
//     uiWLTimeCnt1++;
//     if(uiWLTimeCnt1>const_WL_time)
//     {
//        uiWLTimeCnt1=0; 
//        ucWLLock1=1; 
//        ucWLSec=1;
//     }
//  }
//
//  if(GetWL2_H)																
//  {
//        ucWLLock2=0; 
//        uiWLTimeCnt2=0;														
//  }
//  else if(ucWLLock2==0)
//  {
//     uiWLTimeCnt2++; 
//     if(uiWLTimeCnt2>const_WL_time)
//     {
//        uiWLTimeCnt2=0;
//        ucWLLock2=1; 
//        ucWLSec=2;
//     }
//  }
  
  if(GetWL2_H)				//双向抗抖程序
  {
    WaterFlag=3;
    ucWLLockIn2=0;
    uiWLTimeCntIn2=0;
    if (ucWLLockOut2==0)
    {
      uiWLTimeCntOut2++;
      if (uiWLTimeCntOut2>const_WL_time)
      {
        uiWLTimeCntOut2=0;
        ucWLLockOut2=1;
        WaterFlag=2;
        FlagAll=1;
        SendWL2ON();
        HAL_GPIO_WritePin(GPIOE,LED2_Pin,GPIO_PIN_SET);
      }
    }
    
  }
  else if(ucWLLockIn2==0)
  {
    ucWLLockOut2=0;
    uiWLTimeCntOut2=0;
    uiWLTimeCntIn2++;
    if(uiWLTimeCntIn2>const_WL_time)
    {
      uiWLTimeCntIn2=0;
      ucWLLockIn2=1;
      WaterFlag=1;
      SendWL2OFF();
      HAL_GPIO_WritePin(GPIOE,LED2_Pin,GPIO_PIN_RESET);
    }
  }
  
    if(GetWL1_H)				//双向抗抖程序
  {
    ucWLLockIn1=0;
    uiWLTimeCntIn1=0;
    if (ucWLLockOut1==0)
    {
      uiWLTimeCntOut1++;
      if (uiWLTimeCntOut1>const_WL_time)
      {
        uiWLTimeCntOut1=0;
        ucWLLockOut1=1;
        WaterFlag1=2;
        SendWL1ON();
        HAL_GPIO_WritePin(GPIOE,LED3_Pin,GPIO_PIN_SET);

      }
    }
    
  }
  else if(ucWLLockIn1==0)
  {
    ucWLLockOut1=0;
    uiWLTimeCntOut1=0;
    uiWLTimeCntIn1++;
    if(uiWLTimeCntIn1>const_WL_time)
    {
      uiWLTimeCntIn1=0;
      ucWLLockIn1=1;
      WaterFlag1=1;
      SendWL1OFF();
      HAL_GPIO_WritePin(GPIOE,LED3_Pin,GPIO_PIN_RESET);

    }
  }
  

}

void WLSevice(void)
{
//	 switch(ucWLSec)
//	 {
//		 case 1:
//		 ucWLSec=0;
//		 break;
//	   case 2:
//                  ucWLSec=0;
//		   break;
//	 }

//  switch(WaterFlag)
//  {
//  case 1:
//    WaterFlag=0;
//    HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_RESET);
//    break;
////  case 2:
////    WaterFlag=0;
////    HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_SET);
////    break;
//    case 3:
//    WaterFlag=0;
//    HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_SET);
//    break;
//    
//  }
  
//  	 if(GetWL1_L)
//	 {
//
//		  HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_SET);
//	 }
//	 if(GetWL1_H)
//	 {
//
//		 HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_RESET);
//	 }
//         
//           
//  	 if(GetWL2_L)
//	 {
//
//		  HAL_GPIO_WritePin(GPIOD,JDQ3_Pin, GPIO_PIN_SET);
//	 }
//	 if(GetWL2_H)
//	 {
//
//		 HAL_GPIO_WritePin(GPIOD,JDQ3_Pin, GPIO_PIN_RESET);
//	 }
  /*
WaterFlag1 = 1 无水
WaterFlag1 = 2 有水

GPIO_PIN_SET 关
GPIO_PIN_RESET 开

*/
//static uint16_t time1;
//if(FlagAll == 1)
//{
//    if(WaterFlag1 == 1)
//  {
//    if(WaterFlag!=3)
//    {
//    PumpON
//    time1++;
//    if(time1>ShutDownTime)
//    {
//      time1=0;
//      WaterFlag1=0;
//      FlagAll = 0;
//      PumpOFF
//    }
//    }
//  }
//  if (WaterFlag1 == 2)
//  {
//    time1 = 0;
//  }
//  
//    if(WaterFlag == 2||WaterFlag==3)
//  {
//    PumpOFF
//    WaterFlag=0;
//  }
//
//}
  

static uint16_t time1;
static uint16_t time2;
static uint16_t time3;
static uint8_t flagPump;

  if (FlagAll==1)
  {
    if(WaterFlag == 1)
    {
      time1++;
      if(time1>1000)
      {
        time1=0;
        time2++;
      }
      if(time2>120)
      {
        time2=0;
        PumpON
        WaterFlag = 0;
      }
    }

    if(WaterFlag==2|WaterFlag==3)
    {
      time1=0;
      time2=0;
      PumpOFF
      WaterFlag=0;
    }
    
    if(WaterFlag1 == 1)
    {
      FlagAll=0;
      WaterFlag1 = 0;
    }
  }
  
  

if (FlagAll == 0)
{
  WaterFlag=0;
  WaterFlag1=0;
  MachineSTOP();
}
  
  
  
}
