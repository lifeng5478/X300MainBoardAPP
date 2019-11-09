#include "gy25.h"


uint8_t STARTMPU[2] = {0xA5,0X51};
uint8_t MPUZERO[2] = {0xA5,0X55};


void GY25_inquiries(void)
{
  HAL_UART_Transmit(&huart2,STARTMPU,2,0x0f);
}

void GY25_zero_setting(void)
{
  HAL_UART_Transmit(&huart2,MPUZERO,2,0x0f);
}