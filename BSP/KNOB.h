#ifndef _KNOB_H
#define _KNOB_H

#define A_ON   HAL_GPIO_ReadPin(GPIOE,KNOB1_Pin) == 1
#define A_OFF  HAL_GPIO_ReadPin(GPIOE,KNOB1_Pin) == 0
#define B_ON   HAL_GPIO_ReadPin(GPIOE,KNOB2_Pin) == 1
#define B_OFF  HAL_GPIO_ReadPin(GPIOE,KNOB2_Pin) == 0

extern int LimitH;
extern int LimitL;
extern int Step1;
extern unsigned int tmp;
extern int temp1;
void encoder_GPIO_Init(void);
int encodingWitchPolling(void);
void Knob_covered_Votage(void);
#endif
