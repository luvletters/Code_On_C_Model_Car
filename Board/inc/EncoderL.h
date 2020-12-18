#ifndef __ENCODER__H
#define __ENCODER__H
#include "stm32f10x.h"

void Encoder_Init1(void);
short Get_Encoder1(void);
void Encoder_Start1(void);
void Encoder_Close1(void);
void Encoder_Restart1(void);

#endif
