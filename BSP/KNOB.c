#include "stm32f1xx_hal.h"
#include "knob.h"
#include "gpio.h"
char str3[4];
int temp1;
unsigned int tmp;		//全局变量，具有很强的记忆效应，注意使用
unsigned char Aold,Bold;
unsigned char st;

int LimitH,LimitL,Step1;

void encoder_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct;
	 __HAL_RCC_GPIOE_CLK_ENABLE();
  GPIO_InitStruct.Pin = KNOB1_Pin|KNOB2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
}
int encodingWitchPolling(void)
{
		if(A_ON&&B_ON)	  //两个引脚都高电平
				st=1;
		
		if(st)												//锁定并执行下面的扫描
		{
			if(A_OFF&&B_OFF)		//如果两个脚都变低电平了
			{
				if(Bold)										//如果B脚高就将TMP++
				{
					st=0;
					if(tmp==LimitH)
						tmp=LimitH;
					else
						tmp+=Step1;
				}
				if(Aold)										//如果A脚高就将TMP--
				{
					st=0;
				if(tmp==LimitL)
					tmp=LimitL;
				else
					tmp-=Step1;
				}
			}
		}
		Aold=HAL_GPIO_ReadPin(GPIOE,KNOB1_Pin);			//重新读取A。B。脚数据
		Bold=HAL_GPIO_ReadPin(GPIOE,KNOB2_Pin);
		return tmp;
}
void Knob_covered_Votage(void)			//三种加延时与抓取次数公用
{
	temp1=encodingWitchPolling();
	str3[0]=temp1/100+'0';
	str3[1]=temp1%100/10+'0';
	str3[2]=temp1%10+'0';
	str3[3]=' ';
//	display_string_5x7(4,88,str3[3]);
}

	
