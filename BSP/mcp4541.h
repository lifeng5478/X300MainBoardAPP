#ifndef       _MCP4541_H_
#define       _MCP4541_H_
#include "stm32f1xx_hal.h"

#define        Zone1ADDR         0x5c	  //0101 110x
#define        Zone2ADDR         0x5e	  //0101 111x


#define      WRITE_CON_BYTE     0X5

//��ʧ�Դ洢����ַ����
#define       RAM_W0_ADD        0X00	   //��ͷ0
#define       RAM_W1_ADD        0X01	   //��ͷ1
#define       RAM_TCON_ADD      0X04	   //�˿���




//��ʧ�Գ�ͷ0�洢������λ����
#define       RAM_W0_W_D        0x00	   //д������
#define       RAM_W0_V_ADD      0x04	   //����
#define       RAM_W0_V_MIN      0x08	   //�ݼ�
#define       RAM_W0_R_D        0x0C	   //��ȡ����
//��ʧ�Գ�ͷ1�洢������λ����
#define       RAM_W1_W_D        0x00	   //д������
#define       RAM_W1_V_ADD      0x04	   //����
#define       RAM_W1_V_MIN      0x08	   //�ݼ�
#define       RAM_W1_R_D        0x0C	   //��ȡ����

//��ʧ��TCON�洢������λ����
#define       RAM_TCON_W        0x00	   //д������
#define       RAM_TCON_R        0x0C	   //��ȡ����
 void AddResValue(uint8_t DeviceAdd, uint8_t val );
void MinResValue(uint8_t DeviceAdd, uint8_t val );
void MCPReadData(uint8_t DeviceAdd,uint8_t Reg,uint8_t *val );
void MCPWriteData(uint8_t DeviceAdd,uint8_t Reg,uint8_t Data);
void MCP4541Sevice(void);

 uint8_t SetVolume(uint8_t device,uint8_t volume);


#endif
