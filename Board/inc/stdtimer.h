/*
	* 初始化定时器的时候指定我们分频系数psc,这里是将我们的系统时钟(72MHz)进行分频
	* 然后指定重装载值arr,这个重装载值的意思就是当 我们的定时器的计数值 达到这个arr时,定时器就会重新装载其他值.
		例如当我们设置定时器为向上计数时,定时器计数的值等于arr之后就会被清0重新计数
	* 定时器计数的值被重装载一次被就是一个更新(Update)
	* 计算Update时间公式
	Tout = ((arr+1)*(psc+1))/Tclk
	公式推导详解:
		Tclk是定时器时钟源,在这里就是72Mhz 
		我们将分配的时钟进行分频,指定分频值为psc,就将我们的Tclk分了psc+1,我们定时器的最终频率就是Tclk/(psc+1) MHz
		这里的频率的意思就是1s中记 Tclk/(psc+1)M个数 (1M=10的6次方) ,每记一个数的时间为(psc+1)/Tclk ,很好理解频率的倒数是周期,这里每一个数的周期就是(psc+1)/Tclk 秒
		然后我们从0记到arr 就是 (arr+1)*(psc+1)/Tclk
	举例:比如我们设置arr=7199,psc=9999
	我们将72MHz (1M等于10的6次方) 分成了(9999+1)等于 7200Hz
	就是一秒钟记录9000数,每记录一个数就是1/7200秒
	我们这里记录9000个数进入定时器更新(7199+1)*(1/7200)=1s,也就是1s进入一次更新Update
*/
//简单进行定时器初始化,设置 预装载值 和 分频系数
#include "stm32f10x.h"
#include "delay.h"
#include "Servo.h"
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "motor.h"
#include "math.h"
#include "oled.h"
#include "EncoderR.h"
#include "EncoderL.h"
void MY_TIM6_Init(u16 arr,u16 psc){
	
	//初始化结构体
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//1.分配时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	//2.初始化定时器相关配置
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	
	/*在这里说一下这个TIM_ClockDivision 是设置与进行输入捕获相关的分频
		设置的这个值不会影响定时器的时钟频率,我们一般设置为TIM_CKD_DIV1,也就是不分频*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	
	//3.打开定时器
	TIM_Cmd(TIM6,ENABLE);
}

