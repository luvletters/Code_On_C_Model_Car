#include "EncoderR.h"

//��0������cntֵ
void Encoder_Restart2(void)
{
	TIM3->CNT = 0;
}

//�򿪱����������Ķ�ʱ��
void Encoder_Start2(void)
{
	TIM_Cmd(TIM3, ENABLE);
}

//�رձ����������Ķ�ʱ��
void Encoder_Close2(void)
{
	TIM_Cmd(TIM3, DISABLE);
}


//�õ���������ǰ����ֵ,��ת�򷵻���ֵ����ת�򷵻ظ�ֵ����ת�򷵻�0
short Get_Encoder2(void)
{
	return (short)TIM3->CNT;
}



//��ʼ����������ʱ����ʹ��Ϊ������AB��ģʽ
//����0 cntֵ���رն�ʱ��4���ȵ��õ�ʱ����Ҫ������ʱ��4
//D12-> TIM4_CH1   D13-> TIM4_CH2 
void Encoder_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����һ��GPIO�ṹ�����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����һ����ʱ���ṹ�����
	TIM_ICInitTypeDef TIM_ICInitStructure;	//����һ����ʱ���������ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);//ʹ�ܶ�ʱ��4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;		//����D12-> TIM4_CH1   D13-> TIM4_CH2 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����50MHzʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//����Ϊ��������ģʽ
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//������ӳ��
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//���������ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);	//��ʼ����ʱ��4

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//��AB�����
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	Encoder_Restart2();//cnt��0
	Encoder_Close2();  //׼����ʼ����
}


