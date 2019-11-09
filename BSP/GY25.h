#ifndef       _GY25_H_
#define       _GY25_H_

#include "usart.h"

extern uint8_t STARTMPU[2];

void GY25_inquiries(void);
void GY25_zero_setting(void);

#endif
