#include "tone.h"

/**
  * @brief  ��������������
  * @param  tone������  time������ʱ�䣨���ģ� 
  * @retval ��
  * @note TIM4CH4
  */
void BuzzerBeep(uint16_t tone,uint16_t time)
{
  static short cnt = 0;
  cnt++;
	TIM_PWM_Init(tone,71);//toneΪ�������ı�Ԥ��Ƶֵ���Ըı�����
	TIM_SetCompare4(TIM4,(uint16_t)(tone*0.5));//ռ�ձ�50%
	delay_ms(time*5);//��ʱ���ƽ���
	
/****����birthdayʱ����ע�ʹ˴��ƹ�****************/
	if (cnt%6 ==0)  LED_Reverse(LED1);//�ƹ�Ч��
	if (cnt%6 ==1)  LED_Reverse(LED2);
	if (cnt%6 ==2)  LED_Reverse(LED3);
	if (cnt%6 ==3)  LED_Reverse(LED4);
	if (cnt%6 ==4)  LED_Reverse(LED5);
	if (cnt%6 ==5)  LED_Reverse(LED6);
/**************************************************/
}

/**
  * @brief  pwm��������������
  * @param  arr���Ĵ�������   psc��Ԥ��Ƶֵ 
  * @retval ��
  * @note   ��
  */
void TIM_PWM_Init(uint16_t arr,uint16_t psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//ʹ�ܶ�ʱ��4ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD  | RCC_APB2Periph_AFIO, ENABLE);  //ʹ��GPIO�����AFIO���ù���ģ��ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);//TIM4 CH4������ӳ��ΪD15��֮ǰ����ʹ��FIO���ù���ģ��ʱ��
	 
   //���ø�����Ϊ�����������,���TIM4 CH4��PWM���岨��	GPIOD.15
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //TIM4_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM4 Channe4 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;		//���ó�ʼռ�ձ�
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM4 OC4

	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR2�ϵ�Ԥװ�ؼĴ���
 
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4
	

}
