#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x.h"

//��ö������з�װ
typedef enum 
{
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6,
	LED_ALL
}LED;

extern void Led_Init(LED Led);
extern void Led_Set(LED Led, uint8_t State);
extern void LED_Reverse(LED led);

#endif
