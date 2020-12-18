#include "led.h"

/**
  * @brief  LED初始化
  * @param  Led：LED灯（LED1 - LED6）
  * @retval 无
  * @note Led_Init(LED1);
					LED1 PF13
					LED2 PF14
					LED3 PF15		
					LED4 PG0
					LED5 PG1
					LED6 PE7
  */
void Led_Init(LED Led)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	if(Led==LED1)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF ,&GPIO_InitStructure);
	}
	else if(Led==LED2)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF ,&GPIO_InitStructure);
	}
	else if(Led==LED3)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF ,&GPIO_InitStructure);
	}
	else if(Led==LED4)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOG ,&GPIO_InitStructure);
	}
	else if(Led==LED5)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOG ,&GPIO_InitStructure);
	}
	else if(Led==LED6)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);
	}
	else if(Led==LED_ALL)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOG|RCC_APB2Periph_GPIOE, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF ,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
		GPIO_Init(GPIOG ,&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_Init(GPIOE ,&GPIO_InitStructure);
	}
}

/**
  * @brief  设置LED状态
  * @param  Led：LED灯（LED1 - LED6）
  * @param  State： 设置的状态（0、1）
  * @retval 无
  * @note Led_Set(LED1,1);
  */
void Led_Set(LED Led, uint8_t State)
{
	if(Led==LED1)
	{
		if(State==1)
			GPIO_ResetBits(GPIOF,GPIO_Pin_13);
		else if(State==0)
			GPIO_SetBits(GPIOF,GPIO_Pin_13);
	}
	else if(Led==LED2)
	{
		if(State==1)
			GPIO_ResetBits(GPIOF,GPIO_Pin_14);
		else if(State==0)
			GPIO_SetBits(GPIOF,GPIO_Pin_14);
	}
	else if(Led==LED3)
	{
		if(State==1)
			GPIO_ResetBits(GPIOF,GPIO_Pin_15);
		else if(State==0)
			GPIO_SetBits(GPIOF,GPIO_Pin_15);
	}
	else if(Led==LED4)
	{
		if(State==1)
			GPIO_ResetBits(GPIOG,GPIO_Pin_0);
		else if(State==0)
			GPIO_SetBits(GPIOG,GPIO_Pin_0);
	}
	else if(Led==LED5)
	{
		if(State==1)
			GPIO_ResetBits(GPIOG,GPIO_Pin_1);
		else if(State==0)
			GPIO_SetBits(GPIOG,GPIO_Pin_1);
	}
	else if(Led==LED6)
	{
		if(State==1)
			GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		else if(State==0)
			GPIO_SetBits(GPIOE,GPIO_Pin_7);
	}
	else if(Led==LED_ALL)
	{
		if(State==1)
		{
			GPIO_ResetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			GPIO_ResetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1);
			GPIO_ResetBits(GPIOE,GPIO_Pin_7);
		}
		else if(State==0)
		{
			GPIO_SetBits(GPIOF,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
			GPIO_SetBits(GPIOG,GPIO_Pin_0|GPIO_Pin_1);
			GPIO_SetBits(GPIOE,GPIO_Pin_7);
		}
	}
}
/**
  * @brief  反转LED状态
  * @param  Led：LED灯（LED1 - LED6）
  * @param  State： 设置的状态（0、1）
  * @retval 无
  * @note LED_Reverse(LED1);
  */
void LED_Reverse(LED led)
{
    //记录LED状态 
    static uint8_t led_state[7];
    led_state[led]++;
    
    if(0 == led_state[led]%2)
    {
        Led_Set(led,1);
    }
    else
    {
        Led_Set(led,0);
    }
}
