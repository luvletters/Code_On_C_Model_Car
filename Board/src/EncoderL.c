#include "EncoderL.h"

//��0������cntֵ
void Encoder_Restart1(void)
{
	TIM4->CNT = 0;
}

//�򿪱����������Ķ�ʱ��
void Encoder_Start1(void)
{
	TIM_Cmd(TIM4, ENABLE);
}


//�رձ����������Ķ�ʱ��
void Encoder_Close1(void)
{
	TIM_Cmd(TIM4, DISABLE);
}


//�õ���������ǰ����ֵ,��ת�򷵻���ֵ����ת�򷵻ظ�ֵ����ת�򷵻�0
short Get_Encoder1(void)
{
	return (short)TIM4->CNT;
}



//��ʼ����������ʱ����ʹ��Ϊ������AB��ģʽ
//����0 cntֵ���رն�ʱ��4���ȵ��õ�ʱ����Ҫ������ʱ��4
//D12-> TIM4_CH1   D13-> TIM4_CH2 
void Encoder_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	//����һ��GPIO�ṹ�����
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//����һ����ʱ���ṹ�����
	TIM_ICInitTypeDef TIM_ICInitStructure;	//����һ����ʱ���������ṹ�����

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//ʹ�ܶ�ʱ��4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;		//����D12-> TIM4_CH1   D13-> TIM4_CH2 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//����50MHzʱ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//����Ϊ��������ģʽ
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//������ӳ��
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//���������ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//ʱ�Ӳ���Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	//��ʼ����ʱ��4

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//��AB�����
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);

	Encoder_Restart1();//cnt��0
	Encoder_Close1();  //׼����ʼ����
}


