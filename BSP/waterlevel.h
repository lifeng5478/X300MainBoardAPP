#ifndef __WATERLEVEL_H__
#define __WATERLEVEL_H__

#include "stm32f1xx_hal.h"
#define PumpOFF HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_SET);
#define PumpON HAL_GPIO_WritePin(GPIOD,JDQ4_Pin, GPIO_PIN_RESET);

extern uint8_t FlagAll;

void WL_Init(void);
void WL_scan(void);
void WLSevice(void);

#endif

