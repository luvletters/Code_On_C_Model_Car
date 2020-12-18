#include "key.h"

/**
  * @brief  按键初始化（打开对应时钟，配置Key对应GPIO引脚的工作模式）
  * @param  Key：key为枚举体变量，只能是KEY1/2或KEY_ALL
  * @retval 无
  * @note KEY1 PG9 
					KEY2 PD7
  */
	
void Key_Init(KEY Key)
{
	if(Key==KEY1)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOG ,&GPIO_InitStructure);
	}
	else if(Key==KEY2)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOD ,&GPIO_InitStructure);
	}
	else if(Key==KEY_ALL)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOD, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_Init(GPIOG ,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		
		GPIO_Init(GPIOD ,&GPIO_InitStructure);
	}
}

/**
  * @brief  获取按键状态（判断按键是否按下）
  * @param  Key：key为枚举体变量，只能是KEY1、KEY2或KEY_ALL
  * @retval 无
  * @note Key_Get(KEY1);
*/
uint8_t Key_Get(KEY Key)
{
	if(Key==KEY1)
		return GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9);
	else if(Key==KEY2)
		return GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7);
	else
		return 1;
}





