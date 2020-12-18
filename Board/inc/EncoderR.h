#ifndef __ENCODER__H
#define __ENCODER__H
#include "stm32f10x.h"

void Encoder_Init2(void);
short Get_Encoder2(void);
void Encoder_Start2(void);
void Encoder_Close2(void);
void Encoder_Restart2(void);

#endif
