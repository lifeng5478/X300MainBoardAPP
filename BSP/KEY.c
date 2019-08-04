#include "key.h"
#include "lcd_zk.h"
#include "menu.h"
#include "i2c.h"
#include "gpio.h"
#include "FlashEEPROM.h"

#define  GetKey1_H  HAL_GPIO_ReadPin(KEY1_EVQQ7_GPIO_Port,KEY1_EVQQ7_Pin)==1
#define  GetKey1_L  HAL_GPIO_ReadPin(KEY1_EVQQ7_GPIO_Port,KEY1_EVQQ7_Pin)==0
#define  GetKey2_H  HAL_GPIO_ReadPin(GPIOB,KEY2_EVQQ7_Pin)==1
#define  GetKey2_L  HAL_GPIO_ReadPin(GPIOB,KEY2_EVQQ7_Pin)==0
#define  GetKey3_H  HAL_GPIO_ReadPin(GPIOB,KEY3_EVQQ7_Pin)==1
#define  GetKey3_L  HAL_GPIO_ReadPin(GPIOB,KEY3_EVQQ7_Pin)==0
#define  GetKey4_H  HAL_GPIO_ReadPin(GPIOC,KEY4_EVQQ7_Pin)==1
#define  GetKey4_L  HAL_GPIO_ReadPin(GPIOC,KEY4_EVQQ7_Pin)==0
#define  GetKey5_H  HAL_GPIO_ReadPin(GPIOC,KEY5_EVQQ7_Pin)==1
#define  GetKey5_L  HAL_GPIO_ReadPin(GPIOC,KEY5_EVQQ7_Pin)==0

#define const_key_time1  30
#define const_key_time2  20
#define const_key_time3  20
#define const_key_time4  20
#define const_key_time5  20

unsigned char ucKeySec=0;   //按键选择
unsigned char ucKey1Num=0;   //按键1次数
unsigned char ucKey2Num=0;//按键2次数
unsigned char ucKey3Num=0;//按键3次数
unsigned int  uiKeyTimeCnt1=0; 	//按键1去抖时间
unsigned char ucKeyLock1=0;   //按键1自锁防止持续触发

unsigned int  uiKeyTimeCnt2=0;  //按键2去抖时间
unsigned char ucKeyLock2=0; //按键2自锁防止持续触发

unsigned int  uiKeyTimeCnt3=0;  //按键3去抖时间
unsigned char ucKeyLock3=0; //按键3自锁防止持续触发

unsigned int  uiKeyTimeCnt4=0;  //按键4去抖时间
unsigned char ucKeyLock4=0; //按键4自锁防止持续触发

unsigned int  uiKeyTimeCnt5=0;  //按键5去抖时间
unsigned char ucKeyLock5=0; //按键5自锁防止持续触发

uint8_t MenuIndex=0;


extern void WHPInit(void);

typedef struct
{
	uint8_t current;
	uint8_t Key_UP;
	uint8_t Key_DOWN;
	uint8_t Key_LEFT;
	uint8_t Key_RIGHT;
	uint8_t Key_ENTER;
	void (*current_fun_index)();
}Key_Table;

//const Key_Table table[30]=
//{
//	{0,0,0,0,0,1,(*RootMenu)},
//	{1,3,2,1,4,4,(*Menu1_1)},//设备开关
//	{2,1,3,2,6,6,(*Menu1_2)},//水泵开关
//	{3,2,1,3,8,8,(*Menu1_3)},//风扇速度
//	{4,5,5,1,4,1,(*Menu2_1)},//设备开关子
//	{5,4,4,1,5,1,(*Menu2_2)},
//	{6,7,7,2,6,2,(*Menu3_1)},//水泵开关子
//	{7,6,6,2,7,2,(*Menu3_2)},
//	{8,9,9,3,10,10,(*Menu4_1)},//风扇速度调节
//	{9,8,8,3,11,11,(*Menu4_2)},
//	{10,10,10,8,10,12,(*Menu4_1_1)},//风扇速度调节
//	{11,11,11,9,11,12,(*Menu4_2_1)},
//	{12,1,1,1,1,1,(*KeepDate)},
//};


const Key_Table table[30]=
{
	{0,0,0,0,0,1,(*RootMenu)},
	{1,5,2,1,6,6,(*Menu1_1)},//设备开关
	{2,1,3,2,8,8,(*Menu1_2)},//水泵开关
	{3,2,4,3,10,10,(*Menu1_3)},//风扇速度
	{4,3,5,4,14,14,(*Menu1_4)},//雾化初始化
	{5,4,1,5,15,15,(*Menu1_5)},//雾化功率
	{6,7,7,1,6,1,(*Menu2_1)},//设备开关选择
	{7,6,6,1,7,1,(*Menu2_2)},//设备开关选择
	{8,9,9,2,8,2,(*Menu3_1)},//水泵开关选择
	{9,8,8,2,9,2,(*Menu3_2)},//水泵开关选择
	{10,11,11,3,12,12,(*Menu4_1)},//风扇速度调节
	{11,10,10,3,13,13,(*Menu4_2)},//风扇速度调节
        {12,12,12,10,12,21,(*Menu4_1_1)},//风扇速度调节
	{13,13,13,11,13,21,(*Menu4_2_1)},//风扇速度调节
	{14,1,1,1,1,1,(*Menu5_1)},//雾化片初始化
	{15,17,16,5,18,18,(*Menu6_1)},//雾化片功率调节
	{16,15,17,5,19,19,(*Menu6_2)},//雾化片功率调节
	{17,16,15,5,20,20,(*Menu6_3)},//雾化片功率调节
	{18,18,18,15,18,21,(*Menu6_1_1)},//雾化片功率调节
	{19,19,19,16,19,21,(*Menu6_2_1)},//雾化片功率调节
	{20,20,20,17,20,21,(*Menu6_3_1)},//雾化片功率调节
	{21,1,1,1,1,1,(*KeepDate)},
};

void (*Current_Menu_Func)();
void Key_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	  __HAL_RCC_GPIOA_CLK_ENABLE();
          __HAL_RCC_GPIOC_CLK_ENABLE();
          __HAL_RCC_GPIOB_CLK_ENABLE();
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY1_EVQQ7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY1_EVQQ7_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PCPin PCPin */
  GPIO_InitStruct.Pin = KEY4_EVQQ7_Pin|KEY5_EVQQ7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PBPin PBPin */
  GPIO_InitStruct.Pin = KEY2_EVQQ7_Pin|KEY3_EVQQ7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void key_scan(void)
{
	
  if(GetKey1_H)																
  {
        ucKeyLock1=0; 
        uiKeyTimeCnt1=0;
  }
  else if(ucKeyLock1==0)
  {
     uiKeyTimeCnt1++;
     if(uiKeyTimeCnt1>const_key_time1)
     {
        uiKeyTimeCnt1=0; 
        ucKeyLock1=1; 
        ucKeySec=1;
     }
  }

  if(GetKey2_H)																
  {
        ucKeyLock2=0; 
        uiKeyTimeCnt2=0;														
  }
  else if(ucKeyLock2==0)
  {
     uiKeyTimeCnt2++; 
     if(uiKeyTimeCnt2>const_key_time2)
     {
        uiKeyTimeCnt2=0;
        ucKeyLock2=1; 
        ucKeySec=2;
     }
  }
	
	  if(GetKey3_H)													
  {
     ucKeyLock3=0; 
     uiKeyTimeCnt3=0;													
  }
  else if(ucKeyLock3==0)
  {
     uiKeyTimeCnt3++;
     if(uiKeyTimeCnt3>const_key_time3)
     {
        uiKeyTimeCnt3=0; 
        ucKeyLock3=1; 
        ucKeySec=3;
     }
  }
	
	if(GetKey4_H)													
  {
     ucKeyLock4=0; 
     uiKeyTimeCnt4=0;													
  }
  else if(ucKeyLock4==0)
  {
     uiKeyTimeCnt4++;
     if(uiKeyTimeCnt4>const_key_time4)
     {
        uiKeyTimeCnt4=0; 
        ucKeyLock4=1; 
        ucKeySec=4;
     }
  }
	
		  if(GetKey5_H)													
  {
     ucKeyLock5=0; 
     uiKeyTimeCnt5=0;													
  }
  else if(ucKeyLock5==0)
  {
     uiKeyTimeCnt5++;
     if(uiKeyTimeCnt5>const_key_time5)
     {
        uiKeyTimeCnt5=0; 
        ucKeyLock5=1; 
        ucKeySec=5;
     }
  }

}

#include "usart.h"
uint8_t ucKeyNum5=0;

void KeySevice(void)
{
	 switch(ucKeySec)
	 {
		 case 1:
			 display_GB2312_string(0,0,"UP!     ");
		 ucKeySec=0;
		   break;
		 case 2:
			 display_GB2312_string(0,0,"DOWN!    ");
		 ucKeySec=0;
		   break;
		 case 3:
			 display_GB2312_string(0,0,"MIDDLE!    ");
		 ucKeySec=0;
		   break;
		 case 4:
			 display_GB2312_string(0,0,"LEFT!     ");
		 ucKeySec=0;
		   break;
		 case 5:
			 display_GB2312_string(0,0,"RIGHT!   ");
				ucKeyNum5++;
			if(ucKeyNum5==1)
			{
				display_GB2312_string(5,0,"开!   ");
			}
			if(ucKeyNum5==2)
			{
				display_GB2312_string(5,0,"关!   ");
				ucKeyNum5=0;
			}
		 ucKeySec=0;
		   break;
		 default:
		 	 break;
	 }
}

extern uint8_t FlashRemember[10];
uint8_t temp=1;
uint8_t MFANtemp=0;
uint8_t FFANtemp=0;
#include "knob.h"
void MenuSevice(void)
{
		uint8_t aa[10];
	switch(ucKeySec)
	{
		case 1:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_UP;
			break;
		case 2:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_DOWN;
			break;
		case 3:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_ENTER;
			break;
		case 4:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_LEFT;
			break;
		case 5:
			ucKeySec=0;
			MenuIndex=table[MenuIndex].Key_RIGHT;
			break;
	}
	

		 	 	if(temp!=MenuIndex)
	{
	 Current_Menu_Func=table[MenuIndex].current_fun_index;
	 (*Current_Menu_Func)();
	 	temp = MenuIndex;
	}

	if(MenuIndex==12)						//调速MF
	 {
                TIM4->CCR1=temp1*10;
		sprintf(aa,"%3d",temp1);					//格式化输出字符串
		display_GB2312_string(5,30,aa);
		display_GB2312_string(5,60,"％");
                FlashRemember[0]=temp1;
	 }
	 if(MenuIndex==13)					//调速FF
	 {
                 TIM4->CCR3=temp1*10;
		sprintf(aa,"%3d",temp1);					//格式化输出字符串 
		display_GB2312_string(5,30,aa);
		display_GB2312_string(5,60,"％");
		FlashRemember[1]=temp1;
	 }
//const Key_Table table[30]=
//{
//	{0,0,0,0,0,1,(*RootMenu)},
//	{1,5,2,1,6,6,(*Menu1_1)},//设备开关
//	{2,1,3,2,8,8,(*Menu1_2)},//水泵开关
//	{3,2,4,3,10,10,(*Menu1_3)},//风扇速度
//	{4,3,5,4,14,14,(*Menu1_4)},//雾化初始化
//	{5,4,1,5,15,15,(*Menu1_5)},//雾化功率
//	{6,7,7,1,6,1,(*Menu2_1)},//设备开关选择
//	{7,6,6,1,7,1,(*Menu2_2)},//设备开关选择
//	{8,9,9,2,8,2,(*Menu3_1)},//水泵开关选择
//	{9,8,8,2,9,2,(*Menu3_2)},//水泵开关选择
//	{10,11,11,3,12,12,(*Menu4_1)},//风扇速度调节
//	{11,10,10,3,13,13,(*Menu4_2)},//风扇速度调节
//        {12,12,12,10,12,21,(*Menu4_1_1)},//风扇速度调节
//	{13,13,13,11,13,21,(*Menu4_2_1)},//风扇速度调节
//	{14,1,1,1,1,1,(*Menu5_1)},//雾化片初始化
//	{15,17,16,5,18,18,(*Menu6_1)},//雾化片功率调节
//	{16,15,17,5,19,19,(*Menu6_2)},//雾化片功率调节
//	{17,16,15,5,20,20,(*Menu6_3)},//雾化片功率调节
//	{18,18,18,15,18,21,(*Menu6_1_1)},//雾化片功率调节
//	{19,19,19,16,19,21,(*Menu6_2_1)},//雾化片功率调节
//	{20,20,20,17,20,21,(*Menu6_3_1)},//雾化片功率调节
//	{21,1,1,1,1,1,(*KeepDate)},
//};

        
          if(MenuIndex==18)						//雾化片全功率
	 {
		sprintf(aa,"%3d",temp1);					//格式化输出字符串
		display_GB2312_string(5,30,aa);
		display_GB2312_string(5,60,"％");
                FlashRemember[2]=temp1;
                MCPWriteData(0x5e,0x00,FlashRemember[2]);
	 }
          if(MenuIndex==19)					//分区1功率
	 {
		sprintf(aa,"%3d",temp1);					//格式化输出字符串 
		display_GB2312_string(5,30,aa);
		display_GB2312_string(5,60,"％");
		FlashRemember[3]=temp1;
	 }
        
        	 if(MenuIndex==20)					//分区2功率
	 {
		sprintf(aa,"%3d",temp1);					//格式化输出字符串 
		display_GB2312_string(5,30,aa);
		display_GB2312_string(5,60,"％");
		FlashRemember[4]=temp1;
	 }
        
	 if(MenuIndex==14)				//雾化片初始化
	 {
           WHPInit();
          MenuIndex=0;
	 }
	
	 	 if(MenuIndex==21)				//保存数据
	 {
                       //    MCPWriteData(0x5e,0x00,FlashRemember[2]);

		 STMFLASH_Write(0, (uint16_t*)FlashRemember, sizeof(FlashRemember));
		 HAL_Delay(500);
			MenuIndex=0;
	 }
	 

}
