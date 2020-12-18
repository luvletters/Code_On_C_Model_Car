/*
	* ��ʼ����ʱ����ʱ��ָ�����Ƿ�Ƶϵ��psc,�����ǽ����ǵ�ϵͳʱ��(72MHz)���з�Ƶ
	* Ȼ��ָ����װ��ֵarr,�����װ��ֵ����˼���ǵ� ���ǵĶ�ʱ���ļ���ֵ �ﵽ���arrʱ,��ʱ���ͻ�����װ������ֵ.
		���統�������ö�ʱ��Ϊ���ϼ���ʱ,��ʱ��������ֵ����arr֮��ͻᱻ��0���¼���
	* ��ʱ��������ֵ����װ��һ�α�����һ������(Update)
	* ����Updateʱ�乫ʽ
	Tout = ((arr+1)*(psc+1))/Tclk
	��ʽ�Ƶ����:
		Tclk�Ƕ�ʱ��ʱ��Դ,���������72Mhz 
		���ǽ������ʱ�ӽ��з�Ƶ,ָ����ƵֵΪpsc,�ͽ����ǵ�Tclk����psc+1,���Ƕ�ʱ��������Ƶ�ʾ���Tclk/(psc+1) MHz
		�����Ƶ�ʵ���˼����1s�м� Tclk/(psc+1)M���� (1M=10��6�η�) ,ÿ��һ������ʱ��Ϊ(psc+1)/Tclk ,�ܺ����Ƶ�ʵĵ���������,����ÿһ���������ھ���(psc+1)/Tclk ��
		Ȼ�����Ǵ�0�ǵ�arr ���� (arr+1)*(psc+1)/Tclk
	����:������������arr=7199,psc=9999
	���ǽ�72MHz (1M����10��6�η�) �ֳ���(9999+1)���� 7200Hz
	����һ���Ӽ�¼9000��,ÿ��¼һ��������1/7200��
	���������¼9000�������붨ʱ������(7199+1)*(1/7200)=1s,Ҳ����1s����һ�θ���Update
*/
//�򵥽��ж�ʱ����ʼ��,���� Ԥװ��ֵ �� ��Ƶϵ��
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
	
	//��ʼ���ṹ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	//1.����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	//2.��ʼ����ʱ���������
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	
	/*������˵һ�����TIM_ClockDivision ��������������벶����صķ�Ƶ
		���õ����ֵ����Ӱ�춨ʱ����ʱ��Ƶ��,����һ������ΪTIM_CKD_DIV1,Ҳ���ǲ���Ƶ*/
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
	
	//3.�򿪶�ʱ��
	TIM_Cmd(TIM6,ENABLE);
}

