#include "EncoderR.h"

//清0编码器cnt值
void Encoder_Restart2(void)
{
	TIM3->CNT = 0;
}

//打开编码器计数的定时器
void Encoder_Start2(void)
{
	TIM_Cmd(TIM3, ENABLE);
}

//关闭编码器计数的定时器
void Encoder_Close2(void)
{
	TIM_Cmd(TIM3, DISABLE);
}


//得到编码器当前计数值,正转则返回正值，倒转则返回负值，不转则返回0
short Get_Encoder2(void)
{
	return (short)TIM3->CNT;
}



//初始化编码器定时器并使能为编码器AB相模式
//并清0 cnt值，关闭定时器4，等到用的时候需要开启定时器4
//D12-> TIM4_CH1   D13-> TIM4_CH2 
void Encoder_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//定义一个GPIO结构体变量
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
	TIM_ICInitTypeDef TIM_ICInitStructure;	//定义一个定时器编码器结构体变量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//使能定时器4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;		//配置D12-> TIM4_CH1   D13-> TIM4_CH2 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置50MHz时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//设置为下拉输入模式
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//开启重映射
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//计数器最大值	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//时钟不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	//初始化定时器4

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//在AB相计数
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	Encoder_Restart2();//cnt清0
	Encoder_Close2();  //准备开始计数
}


