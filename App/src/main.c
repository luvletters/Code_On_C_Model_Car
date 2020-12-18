
#include "stm32f10x.h"
#include "delay.h"
#include "Servo.h"
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "motor.h"
#include "math.h"

float pid_s,pid_m;
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
	delay_init();	//延时初始化
	TIM_PWM_Init();	//定时器PWM初始化
	
	// 配置串口
	USART_Config();
	
	// ADC 初始化
	ADCx_Init();
	
	//motor set
	tim_motor_init();
	
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
		if(ADC_ConvertedValueLocal[0]>1.0&&ADC_ConvertedValueLocal[2]>1.0)
		{
			float sv=100;
			TIM_SetCompare1(TIM_SERVO,1500-sv);
	    TIM_SetCompare2(TIM_SERVO,1500-sv);
	    TIM_SetCompare3(TIM_SERVO,1500-sv);
			delay_ms(2500);

			goto Label_1;
		}
	}
	
	
	while(1)
	{ 
		Label_1:

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
		ADC_ConvertedValueLocal[4]/=2.421;
		
		if(ADC_ConvertedValueLocal[4]<5)
		{
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,100);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,100);//left positive
			
			delay_ms(2000);
		}
		

		

		
		float SensorDevitation;
		float r_s=90,tl=0;
		if(ADC_ConvertedValueLocal[4]<0.01)
		{tl=400;}
		float away;
    float enbig_1=150,ensmall_m=0.045;//0.15
    float pid_P,pid_D=0,pid_I=0,pid_center=1550+tl,I_max=30;
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
		
		
		float rp,lp;
		
		
		
		float encoderDevitation;
		float LastencoderDevitation,enbig_2;
		float pid_2p,pid_2d,pid_2i,pid_2center=135;
		float constant_P,constant_i,constant_d;
		encoderDevitation = 2333-2333;
		encoderDevitation = encoderDevitation*enbig_2;
		LastencoderDevitation = encoderDevitation;
		pid_2p=encoderDevitation*constant_P;
		pid_2d=(encoderDevitation-LastencoderDevitation)*constant_d;
		pid_2i+=encoderDevitation*constant_i;
		if(pid_2i > 100){pid_2i=100;}
		else if(pid_2i < -100){pid_2i=-100;}
		
		//------------------motor PID end here----------------------------------
		

			
		pid_m=pid_2p+pid_2d+pid_2i+pid_2center;
		

		motor_run(motor_1,(30)*away);//right negative
		motor_run(motor_2,(pid_m-SensorDevitation*ensmall_m)*away);//right positive
		motor_run(motor_3,(30)*away);//left negative
		motor_run(motor_4,(pid_m-SensorDevitation*ensmall_m)*away);//left positive
		
		/*
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,100);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,100);//left positive
		
		*/
		
		if(ADC_ConvertedValueLocal[4]>100&&i==0)
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
		
			if(ADC_ConvertedValueLocal[4]>90&&i==1){i++;}
			if(i==2){j++;}
		  if(j>12500){w=2;k++;}
			if(k>1200){w=0.5;}
		
		//adjust:,enbig_2,constant_P,constant_i,constant_d,I_max,over_m.etc.
		//-----------------motor control end here------------------------------
		
	}
	
}

