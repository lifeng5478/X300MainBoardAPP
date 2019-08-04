#include "lcd_zk.h"
#include "menu.h"
#include "knob.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
#include "waterlevel.h"

extern uint8_t FlashRemember[10];
uint8_t STOP1[9]={0x5A,0xA5,0x06,0x82,0x10,0x0B,0x00,0x00,0x00};
uint8_t START1[9]={0x5A,0xA5,0x06,0x82,0x10,0x0B,0x00,0x01,0x00};

void RootMenu(void)	//��ʼ����
{
  display_GB2312_string(0,1,"DSI����ϵͳ    ");
  display_GB2312_string(2,1,"    DSI        ");
  display_GB2312_string(4,1," ���ϴ���	  ");
  display_GB2312_string(6,1,"�����������   ");
}

void Menu1_1(void)	//�˵�ѡ��
{
  display_GB2312_string(0,1,"DSI����ϵͳ    ");
  display_GB2312_string(2,1,">�豸����      ");
  display_GB2312_string(4,1," ˮ�ÿ���	  ");
  display_GB2312_string(6,1," ���ȵ���      ");
}

void Menu1_2(void)	//�˵�ѡ��
{
  display_GB2312_string(0,1,"DSI����ϵͳ    ");
  display_GB2312_string(2,1," �豸����      ");
  display_GB2312_string(4,1,">ˮ�ÿ���      ");
  display_GB2312_string(6,1," ���ȵ���      ");
}

void Menu1_3(void)	//�˵�ѡ��
{
  display_GB2312_string(0,1,"DSI����ϵͳ    ");
  display_GB2312_string(2,1," �豸����      ");
  display_GB2312_string(4,1," ˮ�ÿ���      ");
  display_GB2312_string(6,1,">���ȵ���      ");
}

void Menu1_4(void)	//�˵�ѡ��
{
  display_GB2312_string(0,1,"DSI����ϵͳ    ");
  display_GB2312_string(2,1,">��Ƭ��ʼ��  ");
  display_GB2312_string(4,1," ��Ƭ����    ");
  display_GB2312_string(6,1,"               ");
}

void Menu1_5(void)	//�˵�ѡ��
{
  display_GB2312_string(0,1,"DSI����ϵͳ    ");
  display_GB2312_string(2,1," ��Ƭ��ʼ��  ");
  display_GB2312_string(4,1,">��Ƭ����    ");
  display_GB2312_string(6,1,"               ");
}



void Menu2_1(void)	//�豸����ѡ��
{
  display_GB2312_string(0,1,"DSI�豸����    ");
  display_GB2312_string(2,1,">�豸��        ");
  display_GB2312_string(4,1," �豸��        ");
  display_GB2312_string(6,1,"               ");
  if(FlagAll == 1)
  {
    MachineSTART();
    SendMashineComond(START1);
  }
}

void Menu2_2(void)	//�豸����ѡ��
{
  display_GB2312_string(0,1,"DSI�豸����    ");
  display_GB2312_string(2,1," �豸��        ");
  display_GB2312_string(4,1,">�豸��        ");
  display_GB2312_string(6,1,"               ");
  MachineSTOP();
  SendMashineComond(STOP1);
}

void Menu3_1(void)	//�豸����ѡ��
{
  display_GB2312_string(0,1,"DSIˮ�ÿ���    ");
  display_GB2312_string(2,1,">ˮ�ÿ�        ");
  display_GB2312_string(4,1," ˮ�ù�        ");
  display_GB2312_string(6,1,"               ");
  PUMPStart();
}

void Menu3_2(void)	//�豸����ѡ��
{
  display_GB2312_string(0,1,"DSIˮ�ÿ���    ");
  display_GB2312_string(2,1," ˮ�ÿ�        ");
  display_GB2312_string(4,1,">ˮ�ù�        ");
  display_GB2312_string(6,1,"               ");
  PUMPStop();
}

void Menu4_1(void)	//�����ٶȵ���
{
  display_GB2312_string(0,1,"DSI�����ٶ�    ");
  display_GB2312_string(2,1,">M����         ");
  display_GB2312_string(4,1," F����         ");
  display_GB2312_string(6,1,"               ");
}

void Menu4_2(void)	//�����ٶȵ���
{
  display_GB2312_string(0,1,"DSI�����ٶ�    ");
  display_GB2312_string(2,1," M����         ");
  display_GB2312_string(4,1,">F����         ");
  display_GB2312_string(6,1,"               ");
}

void Menu4_1_1(void)	//�����ٶȵ���
{
  display_GB2312_string(0,1,"DSI�����ٶ�    ");
  display_GB2312_string(2,1,">M����         ");
  display_GB2312_string(4,1," 	          ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[0];
}

void Menu4_2_1(void)	//�����ٶȵ���
{
  display_GB2312_string(0,1,"DSI�����ٶ�    ");
  display_GB2312_string(2,1,">F����         ");
  display_GB2312_string(4,1,"	          ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[1];
}

void Menu5_1(void)	//��Ƭ��ʼ��
{
  display_GB2312_string(0,1,"��Ƭ��ʼ��   ");
  display_GB2312_string(2,1,"��ʼ����....   ");
  display_GB2312_string(4,1,"���Ժ�!        ");
  display_GB2312_string(6,1,"               ");
}

void Menu6_1(void)	//��Ƭ���ʵ���
{
  display_GB2312_string(0,1,"��Ƭ����     ");
  display_GB2312_string(2,1,">�ܹ���        ");
  display_GB2312_string(4,1," ����һ        ");
  display_GB2312_string(6,1," ������        ");
}

void Menu6_2(void)	//��Ƭ���ʵ���
{
  display_GB2312_string(0,1,"��Ƭ����     ");
  display_GB2312_string(2,1," �ܹ���        ");
  display_GB2312_string(4,1,">����һ        ");
  display_GB2312_string(6,1," ������        ");
}

void Menu6_3(void)	//��Ƭ���ʵ���
{
  display_GB2312_string(0,1,"��Ƭ����     ");
  display_GB2312_string(2,1," �ܹ���        ");
  display_GB2312_string(4,1," ����һ        ");
  display_GB2312_string(6,1,">������        ");
}

void Menu6_1_1(void)	//��Ƭ���ʵ���
{
  display_GB2312_string(0,1,"��Ƭ����     ");
  display_GB2312_string(2,1,">�ܹ���        ");
  display_GB2312_string(4,1,"               ");
  display_GB2312_string(6,1,"               ");       
  tmp=FlashRemember[2];
  
}

void Menu6_2_1(void)	//��Ƭ���ʵ���
{
  display_GB2312_string(0,1,"��Ƭ����     ");
  display_GB2312_string(2,1,">����һ        ");
  display_GB2312_string(4,1,"               ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[3];
  
}

void Menu6_3_1(void)	//��Ƭ���ʵ���
{
  display_GB2312_string(0,1,"��Ƭ����     ");
  display_GB2312_string(2,1,">������        ");
  display_GB2312_string(4,1,"               ");
  display_GB2312_string(6,1,"               ");
  tmp=FlashRemember[4];
  
}

void KeepDate(void)
{
  display_GB2312_string(0,1,"               ");
  display_GB2312_string(2,1,"���ڱ�������   ");
  display_GB2312_string(4,1,"   ���Ժ�...   ");
  display_GB2312_string(6,1,"               ");	
}
