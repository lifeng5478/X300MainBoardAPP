#ifndef       _MCP4541_H_
#define       _MCP4541_H_
#include "stm32f1xx_hal.h"

#define        Zone1ADDR         0x5c	  //0101 110x
#define        Zone2ADDR         0x5e	  //0101 111x


#define      WRITE_CON_BYTE     0X5

//易失性存储器地址定义
#define       RAM_W0_ADD        0X00	   //抽头0
#define       RAM_W1_ADD        0X01	   //抽头1
#define       RAM_TCON_ADD      0X04	   //端控制




//易失性抽头0存储器操作位定义
#define       RAM_W0_W_D        0x00	   //写入数据
#define       RAM_W0_V_ADD      0x04	   //递增
#define       RAM_W0_V_MIN      0x08	   //递减
#define       RAM_W0_R_D        0x0C	   //读取数据
//易失性抽头1存储器操作位定义
#define       RAM_W1_W_D        0x00	   //写入数据
#define       RAM_W1_V_ADD      0x04	   //递增
#define       RAM_W1_V_MIN      0x08	   //递减
#define       RAM_W1_R_D        0x0C	   //读取数据

//易失性TCON存储器操作位定义
#define       RAM_TCON_W        0x00	   //写入数据
#define       RAM_TCON_R        0x0C	   //读取数据
 void AddResValue(uint8_t DeviceAdd, uint8_t val );
void MinResValue(uint8_t DeviceAdd, uint8_t val );
void MCPReadData(uint8_t DeviceAdd,uint8_t Reg,uint8_t *val );
void MCPWriteData(uint8_t DeviceAdd,uint8_t Reg,uint8_t Data);
void MCP4541Sevice(void);

 uint8_t SetVolume(uint8_t device,uint8_t volume);


#endif
