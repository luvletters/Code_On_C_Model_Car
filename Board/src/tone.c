#include "tone.h"

/**
  * @brief  蜂鸣器发声函数
  * @param  tone：音调  time：持续时间（节拍） 
  * @retval 无
  * @note TIM4CH4
  */
void BuzzerBeep(uint16_t tone,uint16_t time)
{
  static short cnt = 0;
  cnt++;
	TIM_PWM_Init(tone,71);//tone为音调，改变预分频值可以改变音高
	TIM_SetCompare4(TIM4,(uint16_t)(tone*0.5));//占空比50%
	delay_ms(time*5);//延时控制节拍
	
/****演奏birthday时建议注释此处灯光****************/
	if (cnt%6 ==0)  LED_Reverse(LED1);//灯光效果
	if (cnt%6 ==1)  LED_Reverse(LED2);
	if (cnt%6 ==2)  LED_Reverse(LED3);
	if (cnt%6 ==3)  LED_Reverse(LED4);
	if (cnt%6 ==4)  LED_Reverse(LED5);
	if (cnt%6 ==5)  LED_Reverse(LED6);
/**************************************************/
}

/**
  * @brief  pwm驱动蜂鸣器发声
  * @param  arr：寄存器周期   psc：预分频值 
  * @retval 无
  * @note   无
  */
void TIM_PWM_Init(uint16_t arr,uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);//TIM4 CH4引脚重映射为D15，之前必须使能FIO复用功能模块时钟
	 
   //设置该引脚为复用输出功能,输出TIM4 CH4的PWM脉冲波形	GPIOD.15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM4_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM4 Channe4 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;		//设置初始占空比
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC4

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM4在CCR2上的预装载寄存器
 
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
	

}
