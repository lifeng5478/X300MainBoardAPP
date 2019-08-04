#include "flasheeprom.h"

#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_254   /* Start @ of user Flash area����EEPROM����ʼ��ַ���� */
#define FLASH_USER_END_ADDR     ADDR_FLASH_PAGE_255 + FLASH_PAGE_SIZE   /* End @ of user Flash area ����EEPROM�Ľ�����ַ���� һ������оƬ�����1-2K�͹�����*/
#define STMFLASH_SIZE			2048
uint32_t Address = 0, PAGEError = 0;

uint16_t STMFLASH_BUFF[STMFLASH_SIZE];

void eeprom_erase(void)
{
	  FLASH_EraseInitTypeDef EraseInitStruct;
	  HAL_FLASH_Unlock();
	  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
		EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR) / FLASH_PAGE_SIZE;
		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError) != HAL_OK)
  {
    /*
      Error occurred while page erase.
      User can add here some code to deal with this error.
      PAGEError will contain the faulty page and then to know the code error on this page,
      user can call function 'HAL_FLASH_GetError()'
    */
    /* Infinite loop */
    while (1)
    {
      /* Make LED2 blink (100ms on, 2s off) to indicate error in Erase operation */
      HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
      HAL_Delay(50);
    }
  }
}

void eeprom_prog(void)	
{
	uint16_t i;
  Address = FLASH_USER_START_ADDR;

  while (Address < FLASH_USER_END_ADDR)
  {
		for(i=0;i<STMFLASH_SIZE;i++)
    
		{
			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, Address, *(STMFLASH_BUFF+i)) == HAL_OK)			//32λ����Ϊ16λ�������ֽ�
    {
      Address = Address + 2;
    }
    else
    {
      /* Error occurred while writing data in Flash memory.
         User can add here some code to deal with this error */
      while (1)
      {
        /* Make LED2 blink (100ms on, 2s off) to indicate error in Write operation */
      HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_2);
      HAL_Delay(50);
      }
    }
	}
  }

}


void STMFLASH_Write(uint16_t Addr,uint16_t *pBuffer,uint16_t NumToWrite)
{
	uint16_t j;
	eeprom_erase();
		for(j=0;j<NumToWrite;j++)
	{
		STMFLASH_BUFF[j+Addr] = *(pBuffer+j);			//������д��������ȥ
	}	
	eeprom_prog();
	 HAL_FLASH_Lock();
}

void STMFLASH_Read(uint16_t Addr,uint16_t *pstr,uint16_t NumberToRead)
{
	uint16_t t;
	for(t=0;t<NumberToRead;t++)
	{
		*(pstr+t) = *(__IO uint16_t*)(FLASH_USER_START_ADDR+Addr+t*2);	
	}
}
