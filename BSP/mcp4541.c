#include "mcp4541.h"
#include "i2c.h"
//#include "usart.h"

/*******************************************************************
** Function Name    : WriteData
** Description      : 读取寄存器内的值
** Input Parameters : DeviceAdd，器件的硬件地址，
					  Reg 寄存器的地址
					  Data，要写入
** Output Parameters:

    note :                         
*******************************************************************/
#if HardFlag

void MCPWriteData(uint8_t DeviceAdd,uint8_t Reg,uint8_t Data)
{

  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&hi2c1, DeviceAdd, (Reg<<4+0x00), I2C_MEMADD_SIZE_8BIT, &Data, 1, 1000);
  
  /* 检测I2C通信状态 */
  if(status != HAL_OK)
  {
    /* 调用I2C通信错误处理函数 */
    printf("写入MCP失败！");
//      HAL_I2C_MspDeInit(&hi2c1);
  
  /* 重新初始化I2C通信总线*/
//  MX_I2C1_Init();
  }
    else
  {
      printf("写入MCP成功！");
  }

}



/*******************************************************************
** Function Name    : ReadData
** Description      : 读取寄存器内的值
** Input Parameters : DeviceAdd，器件的硬件地址，
                	  val读取的数据存放的地址
					  RegAdd，要读取的存储器地址
** Output Parameters:

    note :                         
*******************************************************************/

void MCPReadData(uint8_t DeviceAdd,uint8_t Reg,uint8_t *val )
{

  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Read(&hi2c1, DeviceAdd, Reg, I2C_MEMADD_SIZE_8BIT, val, 2, 1000);
 
  /* 检测I2C通信状态 */
  if(status != HAL_OK)
  {
    /* 调用I2C通信错误处理函数 */
    printf("读取MCP失败！");
    HAL_I2C_MspDeInit(&hi2c1);
  
  /* 重新初始化I2C通信总线*/
  MX_I2C1_Init();
  }
  else
  {
      printf("读取MCP成功！");
  }
}

/***************************************************************
** Function Name    : SetVolume
** Description      : 读取寄存器内的值
** Input Parameters : device所选择的数字电位器的序号 0~256，
                	  volume音量值 0~127
** Output Parameters: 1:设置成功，0：设置失败

    note :                         
***************************************************************/

uint8_t SetVolume(uint8_t device,uint8_t volume) 
{
  	uint8_t value;
	uint8_t DeviceAdd =0;
	uint8_t i=0,tempVolume=0;
	if(0x01 == device)
		DeviceAdd = Device_1; 	
	else if(0x02 == device)
		DeviceAdd = Device_2; 	
	if(volume>=128)
		tempVolume = 128;
	else
		tempVolume = volume;
	MCPReadData(DeviceAdd,0x00,&value);		
	while(value != tempVolume && i++ < 50)	
	{
		MCPWriteData(DeviceAdd,0x00,tempVolume);
		MCPReadData(DeviceAdd,0x00,&value);
	}
	if(i >= 50)
		return 0;
	else
		return 1;		
}


/*******************************************************************
** Function Name    : AddResValue
** Description      : 递增易失性抽头0,调用一次阻值增加 （val/128）*ResVal
** Input Parameters : DeviceAdd，器件的硬件地址，
                	  val递增的值
** Output Parameters:

    note :                         
*******************************************************************/

void AddResValue(uint8_t DeviceAdd, uint8_t val )
{

  if (HAL_I2C_Master_Transmit(&hi2c1,DeviceAdd,&val,1,0xff)!=HAL_OK)
  {
  printf("写入失败！");
  }
}

/**********************************************************************
** Function Name    : MinResValue
** Description      : 递减易失性抽头0 调用一次阻值减小（val/128）*ResVal
** Input Parameters : DeviceAdd，器件的硬件地址，
                	  val递减的值
** Output Parameters:

    note :                         
**********************************************************************/

void MinResValue(uint8_t DeviceAdd,uint8_t val )
{
  if (HAL_I2C_Master_Transmit(&hi2c1,DeviceAdd,&val,1,0xff)!=HAL_OK)
  {
  printf("写入失败！");
  }
}

#else
void MCPWriteData(uint8_t DeviceAdd,uint8_t Reg,uint8_t Data)
{
  I2C_Start();  						   //起始信号						
  I2C_SendByte(DeviceAdd&0xFE);         //发送控制字节 0 1 0 1 A2 A1 A0 0
  if (I2C_WaitAck() != 0)
  {
//    display_GB2312_string(0,5,"I2C NOACK1");
    I2C_Stop();                            //产生一个停止条件				
    return;
  } 
  I2C_SendByte(Reg<<4);                 //发送MCP45XX命令字节  AD3 AD2 AD1 AD0 X X 
  // AD3:AD0 存储器地址，XX表示命令操作位
  if (I2C_WaitAck() != 0)
  {
  //  display_GB2312_string(0,5,"I2C NOACK2");
    I2C_Stop();                            //产生一个停止条件				
    return;
  }   
  I2C_SendByte(Data);                   //发送数据位			   			
  if (I2C_WaitAck() != 0)
  {
  //  display_GB2312_string(0,5,"I2C NOACK3");
    I2C_Stop();                            //产生一个停止条件				
    return;
  }   
  I2C_Stop();                            //产生一个停止条件	
   //   display_GB2312_string(0,5,"I2C Succece");

}

//void MCPReadData(uint8_t DeviceAdd,uint8_t Reg,uint16_t val )
//{
//    I2C_Start();  						   //起始信号	
//      I2C_SendByte(DeviceAdd&0xFE);         //发送控制字节 0 1 0 1 A2 A1 A0 0
//    I2C_WaitAck(); 
//    I2C_SendByte((Reg<<4)| 0x0c);	       //发送读取命令	
//    I2C_WaitAck(); 
//    I2C_Start();  						   //起始信号	
//    I2C_SendByte(DeviceAdd|0x01);         //发送控制字节 0 1 0 1 A2 A1 A0 0
//    I2C_WaitAck(); 
//    val|= (uint16_t)(I2C_ReadByte()<<8);
//    val|= (uint16_t)I2C_ReadByte();
//    I2C_Stop();                            //产生一个停止条件				
//}
extern uint8_t FlashRemember[10];

uint8_t tempmcp1,tempmcp2,tempmcp3;
uint8_t tempCCR1,tempCCR2;
void MCP4541Sevice(void)
{
//    if(tempCCR1!=FlashRemember[0])
  
    if(tempmcp1!=FlashRemember[3])
      {
        MCPWriteData(Zone1ADDR,0x00,FlashRemember[3]);
        tempmcp1=FlashRemember[3];
      }
      
      if(tempmcp2!=FlashRemember[4])
      {
        MCPWriteData(Zone2ADDR,0x00,FlashRemember[4]);
        tempmcp2=FlashRemember[4];
      }
      
      if(tempmcp3!=FlashRemember[2])
      {
        MCPWriteData(Zone1ADDR,0x00,FlashRemember[2]);
        MCPWriteData(Zone2ADDR,0x00,FlashRemember[2]);
        tempmcp3=FlashRemember[2];
      }
}
#endif