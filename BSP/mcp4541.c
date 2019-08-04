#include "mcp4541.h"
#include "i2c.h"
//#include "usart.h"

/*******************************************************************
** Function Name    : WriteData
** Description      : ��ȡ�Ĵ����ڵ�ֵ
** Input Parameters : DeviceAdd��������Ӳ����ַ��
					  Reg �Ĵ����ĵ�ַ
					  Data��Ҫд��
** Output Parameters:

    note :                         
*******************************************************************/
#if HardFlag

void MCPWriteData(uint8_t DeviceAdd,uint8_t Reg,uint8_t Data)
{

  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&hi2c1, DeviceAdd, (Reg<<4+0x00), I2C_MEMADD_SIZE_8BIT, &Data, 1, 1000);
  
  /* ���I2Cͨ��״̬ */
  if(status != HAL_OK)
  {
    /* ����I2Cͨ�Ŵ������� */
    printf("д��MCPʧ�ܣ�");
//      HAL_I2C_MspDeInit(&hi2c1);
  
  /* ���³�ʼ��I2Cͨ������*/
//  MX_I2C1_Init();
  }
    else
  {
      printf("д��MCP�ɹ���");
  }

}



/*******************************************************************
** Function Name    : ReadData
** Description      : ��ȡ�Ĵ����ڵ�ֵ
** Input Parameters : DeviceAdd��������Ӳ����ַ��
                	  val��ȡ�����ݴ�ŵĵ�ַ
					  RegAdd��Ҫ��ȡ�Ĵ洢����ַ
** Output Parameters:

    note :                         
*******************************************************************/

void MCPReadData(uint8_t DeviceAdd,uint8_t Reg,uint8_t *val )
{

  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Read(&hi2c1, DeviceAdd, Reg, I2C_MEMADD_SIZE_8BIT, val, 2, 1000);
 
  /* ���I2Cͨ��״̬ */
  if(status != HAL_OK)
  {
    /* ����I2Cͨ�Ŵ������� */
    printf("��ȡMCPʧ�ܣ�");
    HAL_I2C_MspDeInit(&hi2c1);
  
  /* ���³�ʼ��I2Cͨ������*/
  MX_I2C1_Init();
  }
  else
  {
      printf("��ȡMCP�ɹ���");
  }
}

/***************************************************************
** Function Name    : SetVolume
** Description      : ��ȡ�Ĵ����ڵ�ֵ
** Input Parameters : device��ѡ������ֵ�λ������� 0~256��
                	  volume����ֵ 0~127
** Output Parameters: 1:���óɹ���0������ʧ��

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
** Description      : ������ʧ�Գ�ͷ0,����һ����ֵ���� ��val/128��*ResVal
** Input Parameters : DeviceAdd��������Ӳ����ַ��
                	  val������ֵ
** Output Parameters:

    note :                         
*******************************************************************/

void AddResValue(uint8_t DeviceAdd, uint8_t val )
{

  if (HAL_I2C_Master_Transmit(&hi2c1,DeviceAdd,&val,1,0xff)!=HAL_OK)
  {
  printf("д��ʧ�ܣ�");
  }
}

/**********************************************************************
** Function Name    : MinResValue
** Description      : �ݼ���ʧ�Գ�ͷ0 ����һ����ֵ��С��val/128��*ResVal
** Input Parameters : DeviceAdd��������Ӳ����ַ��
                	  val�ݼ���ֵ
** Output Parameters:

    note :                         
**********************************************************************/

void MinResValue(uint8_t DeviceAdd,uint8_t val )
{
  if (HAL_I2C_Master_Transmit(&hi2c1,DeviceAdd,&val,1,0xff)!=HAL_OK)
  {
  printf("д��ʧ�ܣ�");
  }
}

#else
void MCPWriteData(uint8_t DeviceAdd,uint8_t Reg,uint8_t Data)
{
  I2C_Start();  						   //��ʼ�ź�						
  I2C_SendByte(DeviceAdd&0xFE);         //���Ϳ����ֽ� 0 1 0 1 A2 A1 A0 0
  if (I2C_WaitAck() != 0)
  {
//    display_GB2312_string(0,5,"I2C NOACK1");
    I2C_Stop();                            //����һ��ֹͣ����				
    return;
  } 
  I2C_SendByte(Reg<<4);                 //����MCP45XX�����ֽ�  AD3 AD2 AD1 AD0 X X 
  // AD3:AD0 �洢����ַ��XX��ʾ�������λ
  if (I2C_WaitAck() != 0)
  {
  //  display_GB2312_string(0,5,"I2C NOACK2");
    I2C_Stop();                            //����һ��ֹͣ����				
    return;
  }   
  I2C_SendByte(Data);                   //��������λ			   			
  if (I2C_WaitAck() != 0)
  {
  //  display_GB2312_string(0,5,"I2C NOACK3");
    I2C_Stop();                            //����һ��ֹͣ����				
    return;
  }   
  I2C_Stop();                            //����һ��ֹͣ����	
   //   display_GB2312_string(0,5,"I2C Succece");

}

//void MCPReadData(uint8_t DeviceAdd,uint8_t Reg,uint16_t val )
//{
//    I2C_Start();  						   //��ʼ�ź�	
//      I2C_SendByte(DeviceAdd&0xFE);         //���Ϳ����ֽ� 0 1 0 1 A2 A1 A0 0
//    I2C_WaitAck(); 
//    I2C_SendByte((Reg<<4)| 0x0c);	       //���Ͷ�ȡ����	
//    I2C_WaitAck(); 
//    I2C_Start();  						   //��ʼ�ź�	
//    I2C_SendByte(DeviceAdd|0x01);         //���Ϳ����ֽ� 0 1 0 1 A2 A1 A0 0
//    I2C_WaitAck(); 
//    val|= (uint16_t)(I2C_ReadByte()<<8);
//    val|= (uint16_t)I2C_ReadByte();
//    I2C_Stop();                            //����һ��ֹͣ����				
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