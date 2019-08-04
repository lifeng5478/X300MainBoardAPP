#include "lcd_zk.h"
#include "menu.h"
#include "knob.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "waterlevel.h"

extern uint8_t FlashRemember[10];
uint8_t STOP1[9]={0x5A,0xA5,0x06,0x82,0x10,0x0B,0x00,0x00,0x00};
uint8_t START1[9]={0x5A,0xA5,0x06,0x82,0x10,0x0B,0x00,0x01,0x00};

void RootMenu(void)	//初始界面
{
  display_GB2312_string(0,1,"DSI控制系统    ");
  display_GB2312_string(2,1,"    DSI        ");
  display_GB2312_string(4,1," 大上创新	  ");
  display_GB2312_string(6,1,"按任意键进入   ");
}

void Menu1_1(void)	//菜单选择
{
  display_GB2312_string(0,1,"DSI控制系统    ");
  display_GB2312_string(2,1,">设备开关      ");
  display_GB2312_string(4,1," 水泵开关	  ");
  display_GB2312_string(6,1," 风扇调速      ");
}

void Menu1_2(void)	//菜单选择
{
  display_GB2312_string(0,1,"DSI控制系统    ");
  display_GB2312_string(2,1," 设备开关      ");
  display_GB2312_string(4,1,">水泵开关      ");
  display_GB2312_string(6,1," 风扇调速      ");
}

void Menu1_3(void)	//菜单选择
{
  display_GB2312_string(0,1,"DSI控制系统    ");
  display_GB2312_string(2,1," 设备开关      ");
  display_GB2312_string(4,1," 水泵开关      ");
  display_GB2312_string(6,1,">风扇调速      ");
}

void Menu1_4(void)	//菜单选择
{
  display_GB2312_string(0,1,"DSI控制系统    ");
  display_GB2312_string(2,1,">雾化片初始化  ");
  display_GB2312_string(4,1," 雾化片功率    ");
  display_GB2312_string(6,1,"               ");
}

void Menu1_5(void)	//菜单选择
{
  display_GB2312_string(0,1,"DSI控制系统    ");
  display_GB2312_string(2,1," 雾化片初始化  ");
  display_GB2312_string(4,1,">雾化片功率    ");
  display_GB2312_string(6,1,"               ");
}



void Menu2_1(void)	//设备开关选择
{
  display_GB2312_string(0,1,"DSI设备开关    ");
  display_GB2312_string(2,1,">设备开        ");
  display_GB2312_string(4,1," 设备关        ");
  display_GB2312_string(6,1,"               ");
  if(FlagAll == 1)
  {
    MachineSTART();
    SendMashineComond(START1);
  }
}

void Menu2_2(void)	//设备开关选择
{
  display_GB2312_string(0,1,"DSI设备开关    ");
  display_GB2312_string(2,1," 设备开        ");
  display_GB2312_string(4,1,">设备关        ");
  display_GB2312_string(6,1,"               ");
  MachineSTOP();
  SendMashineComond(STOP1);
}

void Menu3_1(void)	//设备开关选择
{
  display_GB2312_string(0,1,"DSI水泵开关    ");
  display_GB2312_string(2,1,">水泵开        ");
  display_GB2312_string(4,1," 水泵关        ");
  display_GB2312_string(6,1,"               ");
  PUMPStart();
}

void Menu3_2(void)	//设备开关选择
{
  display_GB2312_string(0,1,"DSI水泵开关    ");
  display_GB2312_string(2,1," 水泵开        ");
  display_GB2312_string(4,1,">水泵关        ");
  display_GB2312_string(6,1,"               ");
  PUMPStop();
}

void Menu4_1(void)	//风扇速度调节
{
  display_GB2312_string(0,1,"DSI风扇速度    ");
  display_GB2312_string(2,1,">M风扇         ");
  display_GB2312_string(4,1," F风扇         ");
  display_GB2312_string(6,1,"               ");
}

void Menu4_2(void)	//风扇速度调节
{
  display_GB2312_string(0,1,"DSI风扇速度    ");
  display_GB2312_string(2,1," M风扇         ");
  display_GB2312_string(4,1,">F风扇         ");
  display_GB2312_string(6,1,"               ");
}

void Menu4_1_1(void)	//风扇速度调节
{
  display_GB2312_string(0,1,"DSI风扇速度    ");
  display_GB2312_string(2,1,">M风扇         ");
  display_GB2312_string(4,1," 	          ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[0];
}

void Menu4_2_1(void)	//风扇速度调节
{
  display_GB2312_string(0,1,"DSI风扇速度    ");
  display_GB2312_string(2,1,">F风扇         ");
  display_GB2312_string(4,1,"	          ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[1];
}

void Menu5_1(void)	//雾化片初始化
{
  display_GB2312_string(0,1,"雾化片初始化   ");
  display_GB2312_string(2,1,"初始化中....   ");
  display_GB2312_string(4,1,"请稍候!        ");
  display_GB2312_string(6,1,"               ");
}

void Menu6_1(void)	//雾化片功率调节
{
  display_GB2312_string(0,1,"雾化片功率     ");
  display_GB2312_string(2,1,">总功率        ");
  display_GB2312_string(4,1," 分区一        ");
  display_GB2312_string(6,1," 分区二        ");
}

void Menu6_2(void)	//雾化片功率调节
{
  display_GB2312_string(0,1,"雾化片功率     ");
  display_GB2312_string(2,1," 总功率        ");
  display_GB2312_string(4,1,">分区一        ");
  display_GB2312_string(6,1," 分区二        ");
}

void Menu6_3(void)	//雾化片功率调节
{
  display_GB2312_string(0,1,"雾化片功率     ");
  display_GB2312_string(2,1," 总功率        ");
  display_GB2312_string(4,1," 分区一        ");
  display_GB2312_string(6,1,">分区二        ");
}

void Menu6_1_1(void)	//雾化片功率调节
{
  display_GB2312_string(0,1,"雾化片功率     ");
  display_GB2312_string(2,1,">总功率        ");
  display_GB2312_string(4,1,"               ");
  display_GB2312_string(6,1,"               ");       
  tmp=FlashRemember[2];
  
}

void Menu6_2_1(void)	//雾化片功率调节
{
  display_GB2312_string(0,1,"雾化片功率     ");
  display_GB2312_string(2,1,">分区一        ");
  display_GB2312_string(4,1,"               ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[3];
  
}

void Menu6_3_1(void)	//雾化片功率调节
{
  display_GB2312_string(0,1,"雾化片功率     ");
  display_GB2312_string(2,1,">分区二        ");
  display_GB2312_string(4,1,"               ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[4];
  
}

void KeepDate(void)
{
  display_GB2312_string(0,1,"               ");
  display_GB2312_string(2,1,"正在保存数据   ");
  display_GB2312_string(4,1,"   请稍侯...   ");
  display_GB2312_string(6,1,"               ");	
}
