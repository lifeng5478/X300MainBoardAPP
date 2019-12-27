#include "waterlevel.h"
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#define  GetWL1_H  HAL_GPIO_ReadPin(WaterLevel1_GPIO_Port,WaterLevel1_Pin)==1
#define  GetWL1_L  HAL_GPIO_ReadPin(WaterLevel1_GPIO_Port,WaterLevel1_Pin)==0
#define  GetWL2_H  HAL_GPIO_ReadPin(WaterLevel2_GPIO_Port,WaterLevel2_Pin)==1
#define  GetWL2_L  HAL_GPIO_ReadPin(WaterLevel2_GPIO_Port,WaterLevel2_Pin)==0

#define const_WL_time 500
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

uint8_t WaterFlag = 1;
uint8_t WaterFlag1 = 1;
uint8_t PumpFlag = 0;
uint8_t PumpFlag1 = 0;
extern uint8_t STFlag; 

uint8_t FlagAll = 0;


void WL_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	   __HAL_RCC_GPIOC_CLK_ENABLE();
  /*Configure GPIO pins : PC4 PC5 */
  GPIO_InitStruct.Pin = WaterLevel1_Pin|WaterLevel2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
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
  
  if(GetWL2_H)				//双向抗抖程序
  {
//    WaterFlag=3;
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
        Machine_status_strc.water2 = 0x00;
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
      Machine_status_strc.water2 = 0x01;
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
        Machine_status_strc.water1 = 0x00;
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
      Machine_status_strc.water1 = 0x01;
    HAL_GPIO_WritePin(GPIOE,LED3_Pin,GPIO_PIN_RESET);
//
    }
  }
  

}

void WLSevice(void)
{

  

static uint16_t time1;
static uint16_t time2;
//static uint16_t time3;
if(STFlag == 0)
{
  if (FlagAll==1)
  {

    if(PumpFlag1 == 1)
    {
      PumpOFF;
      Machine_status_strc.pumpstatus = 0x00;
      PumpFlag1 =0;
    }
    
    if(WaterFlag == 1)
    {
      time1++;
      if(time1>=1000)
      {
        time1=0;
        time2++;
      }
      if(time2>120)
      {
        time2=0;
        PumpON;
        Machine_status_strc.pumpstatus = 0x01;
        PumpFlag =1;
        //WaterFlag = 0;
      }
    }
    if(PumpFlag ==1)
    {
//      time3++;
//      if(time3>10000)
//      {
//        time3 = 0;
//        time2 = 0;
//        PumpFlag=0;
//        PumpOFF;
//        Machine_status_strc.pumpstatus = 0x00;
//      }
      if(WaterFlag == 2)                              //方案二：加注水以上水位为基准
      {
        time2 = 0;
        PumpFlag=0;
        PumpOFF;
        Machine_status_strc.pumpstatus = 0x00;
      }
    }
  }
  
  if(WaterFlag1 == 1)
  {
    FlagAll=0;
    //  WaterFlag1 = 0;
  }

if (FlagAll == 0)
{
  MachineSTOP();
}
}
  
  
  
}
