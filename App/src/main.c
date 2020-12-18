
#include "stm32f10x.h"
#include "delay.h"
#include "Servo.h"
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "motor.h"
#include "math.h"
#include "oled.h"
#include "stdtimer.h"
#include "EncoderR.h"
#include "EncoderL.h"

float pid_s,pid_m_R,pid_m_L;
void Servo_open(void)
{
	TIM_SetCompare1(TIM_SERVO,pid_s);
	TIM_SetCompare2(TIM_SERVO,pid_s);
	TIM_SetCompare3(TIM_SERVO,pid_s);
}
//--------------------------------------------------------------------------------^^
// ADC1转换的电压值通过MDA方式传到SRAM
extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

// 局部变量，用于保存转换计算后的电压值 	 
float ADC_ConvertedValueLocal[NOFCHANEL];    
float LastSensorDevitation=0;
float w=1;

//lalala
int i=0;
int j=0;
int k=0;

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 


//--------------------------------- main start here ------------------------------------------------
int main()
{
	
	
	OLED_init();
	
	
	
	
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%   INIT1  &&&&&&&&&&&&&&&&&&&&&&&&&
	GPIO_InitTypeDef GPIO_InitStructure;	//定义一个GPIO结构体变量
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;//定义一个定时器结构体变量
	TIM_ICInitTypeDef TIM_ICInitStructure;	//定义一个定时器编码器结构体变量

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO, ENABLE);//使能GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);//使能定时器4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;		//配置D12-> TIM4_CH1   D13-> TIM4_CH2 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//设置50MHz时钟
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//设置为下拉输入模式
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	//开启重映射
	GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);
	TIM_TimeBaseStructure.TIM_Period = 0xffff;	//计数器最大值	
	TIM_TimeBaseStructure.TIM_Prescaler = 0;	//时钟不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	// 使用的采样频率之间的分频比例
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	//初始化定时器4

	TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12,TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//在AB相计数
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


	TIM4->CNT = 0;//cnt清0
	TIM_Cmd(TIM4, DISABLE);  //准备开始计数//初始化编码器
	
	
	TIM_Cmd(TIM4, ENABLE);//打开编码器定时器

	
	short Encoder_v1=0;//编码器当前速度值
	int Encoder_a1=0;//编码器当前转角
	
	Encoder_Init2();//初始化编码器
	Encoder_Start2();//打开编码器定时器
	
	short Encoder_v2=0;//编码器当前速度值
	int Encoder_a2=0;//编码器当前转角
	
	delay_init();	//延时初始化
	TIM_PWM_Init();	//定时器PWM初始化
	
	// 配置串口
	USART_Config();
	
	// ADC 初始化
	ADCx_Init();
	
	//motor set
	tim_motor_init();
	
MY_TIM3_Init(71,9999);

/*
	while(1)
	{
		  ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,180);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,180);//left positive
			TIM_SetCompare1(TIM_SERVO,1550);
	    TIM_SetCompare2(TIM_SERVO,1550);
	    TIM_SetCompare3(TIM_SERVO,1550);
		if(ADC_ConvertedValueLocal[0]>1.0||ADC_ConvertedValueLocal[2]>1.0)
		{
			float sv=100;
			TIM_SetCompare1(TIM_SERVO,1500-sv);
	    TIM_SetCompare2(TIM_SERVO,1500-sv);
	    TIM_SetCompare3(TIM_SERVO,1500-sv);
			delay_ms(2500);

			goto Label_1;
		}
	}
*/
	
	while(1)
	{ 
		//Label_1:
		

   		ADC_ConvertedValueLocal[0] =(float) ADC_ConvertedValue[0]/4096*3.3;
			ADC_ConvertedValueLocal[1] =(float) ADC_ConvertedValue[1]/4096*3.3;
			ADC_ConvertedValueLocal[2] =(float) ADC_ConvertedValue[2]/4096*3.3;
			ADC_ConvertedValueLocal[3] =(float) ADC_ConvertedValue[3]/4096*3.3;
			ADC_ConvertedValueLocal[4] =(float) ADC_ConvertedValue[4]/4096*3.3;
		
				ADC_ConvertedValueLocal[1]-=0.26;
		
		if(	ADC_ConvertedValueLocal[0]<0.06){ADC_ConvertedValueLocal[0]=0;}//0,06
		if(	ADC_ConvertedValueLocal[1]<0.02){ADC_ConvertedValueLocal[1]=0;}//0.26
		if(	ADC_ConvertedValueLocal[2]<0.018){ADC_ConvertedValueLocal[2]=0;}//0.018
		if(	ADC_ConvertedValueLocal[3]<0.004){ADC_ConvertedValueLocal[3]=0;}//0,004
		if(	ADC_ConvertedValueLocal[4]<0.07){ADC_ConvertedValueLocal[4]=0;}//0.07
		
		
		ADC_ConvertedValueLocal[0]*=100;
		ADC_ConvertedValueLocal[1]*=100;
		ADC_ConvertedValueLocal[2]*=100;
		ADC_ConvertedValueLocal[3]*=100;
		ADC_ConvertedValueLocal[4]*=100;
		
		ADC_ConvertedValueLocal[0]/=1.80;
		ADC_ConvertedValueLocal[1]/=1.54;//1.54
		ADC_ConvertedValueLocal[2]/=1.86;
		ADC_ConvertedValueLocal[3]/=1.487;//1.487
		ADC_ConvertedValueLocal[4]/=2.4210;
		
		float SensorDevitation;
		float r_s=85,tl=0;
		if(ADC_ConvertedValueLocal[4]<0.01)
		{tl=400;}
		float away;
    float enbig_1=150,ensmall_m=0.045;
    float pid_P,pid_D=0,pid_I,pid_center=1550+tl,I_max=30;
    float g_Proportion=1.1,g_Differential=0.0000011,g_Integral=0.00000002;
		
		away=1*w;
		
    SensorDevitation = (ADC_ConvertedValueLocal[3]-ADC_ConvertedValueLocal[1])/(ADC_ConvertedValueLocal[3]+ADC_ConvertedValueLocal[1]);
    SensorDevitation = SensorDevitation*enbig_1;
		LastSensorDevitation = SensorDevitation;
		if(SensorDevitation<0.5&&SensorDevitation>-0.5) SensorDevitation=0;
    pid_P = SensorDevitation*g_Proportion;
    //pid_D =(SensorDevitation-LastSensorDevitation)*g_Differential;
    pid_I += SensorDevitation * g_Integral;
		if(pid_I > I_max){pid_I = I_max;}
		else if(pid_I < -I_max){pid_I = -I_max;}
    pid_s = pid_center+pid_P+pid_I+pid_D;
		Servo_open();
		delay_ms(1);
		//Servo_close();
		//adjust: enbig,g_Proportion,g_Differential,g_Integral,I_max,delay.etc.
		//-------------------servo control end here-----------------------------
		
		
		if(TIM_GetFlagStatus(TIM3,TIM_IT_Update))
				{
					Encoder_v1=(short)TIM4->CNT;//Get_Encoder1();
					Encoder_a1 += Encoder_v1;
					Encoder_v2=Get_Encoder2();
					Encoder_a2 += Encoder_v2;
							


					Encoder_Restart2();//清0 cnt值
					TIM4->CNT = 0;//Encoder_Restart1();//清0 cnt值
					
					TIM_ClearFlag(TIM3,TIM_IT_Update);
				}
		
		
	
		float rp,lp;
		float conr=1000,conl=1000;
		float pid_2center=130;
				
				
				
		char txt[20];
	  OLED_clear();

		sprintf(txt,"1: %6.1f mV",rp);
		OLED_show6x8string(40,3,txt);
			
				
		float encoderDevitation_R=0;
		encoderDevitation_R=-rp+Encoder_v1*conr;
		float LastencoderDevitation_R=0,enbig_2_R=1;
		float pid_2p_R,pid_2d_R,pid_2i_R;//  -30
		float constant_P_R=1,constant_i_R=0.0001,constant_d_R=0.0001;
		//encoderDevitation_R = 2333-2333;
		encoderDevitation_R = encoderDevitation_R*enbig_2_R;
		LastencoderDevitation_R = encoderDevitation_R;
		pid_2p_R=encoderDevitation_R*constant_P_R;
		pid_2d_R=(encoderDevitation_R-LastencoderDevitation_R)*constant_d_R;
		pid_2i_R+=encoderDevitation_R*constant_i_R;
		if(pid_2i_R > 100){pid_2i_R=100;}
		else if(pid_2i_R < -100){pid_2i_R=-100;}
		
		float encoderDevitation_L=0;
		encoderDevitation_L=-lp+Encoder_v2*conl;
		float LastencoderDevitation_L,enbig_2_L=1;
		float pid_2p_L,pid_2d_L,pid_2i_L;//  -30
		float constant_P_L=1,constant_i_L=0.0001,constant_d_L=0.0001;
		//encoderDevitation_L = 2333-2333;
		encoderDevitation_L = encoderDevitation_L*enbig_2_L;
		LastencoderDevitation_L = encoderDevitation_L;
		pid_2p_L=encoderDevitation_L*constant_P_L;
		pid_2d_L=(encoderDevitation_L-LastencoderDevitation_L)*constant_d_L;
		pid_2i_L+=encoderDevitation_L*constant_i_L;
		if(pid_2i_L > 100){pid_2i_L=100;}
		else if(pid_2i_L < -100){pid_2i_L=-100;}
		
		pid_m_R=pid_2p_R+pid_2d_R+pid_2i_R+pid_2center;
		pid_m_L=pid_2p_L+pid_2d_L+pid_2i_L+pid_2center;
		
		rp=(pid_m_R-SensorDevitation*ensmall_m)*away;
		lp=(pid_m_L-SensorDevitation*ensmall_m)*away;
		//------------------motor PID end here----------------------------------
	
		motor_run(motor_1,(30)*away);//right negative
		motor_run(motor_2,rp);//right positive
		motor_run(motor_3,(30)*away);//left negative
		motor_run(motor_4,lp);//left positive
		
		/* sample
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,100);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,100);//left positive
		
		*/
		
		if(ADC_ConvertedValueLocal[4]>110&&i==0)
		{
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,180);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,180);//left positive
			
			i++;
					TIM_SetCompare1(TIM_SERVO,1500+0.8*r_s);
					TIM_SetCompare2(TIM_SERVO,1500+0.8*r_s);
					TIM_SetCompare3(TIM_SERVO,1500+0.8*r_s);
				delay_ms(500);
			
					TIM_SetCompare1(TIM_SERVO,1500+2*r_s);
					TIM_SetCompare2(TIM_SERVO,1500+2*r_s);
					TIM_SetCompare3(TIM_SERVO,1500+2*r_s);
			  delay_ms(1000);
			
			}
		
		
		//adjust:,enbig_2,constant_P,constant_i,constant_d,I_max,over_m.etc.
		//-----------------motor control end here------------------------------
		
	}
	
}
