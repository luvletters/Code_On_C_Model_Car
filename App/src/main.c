/**********************718创新实验室开发板例程*********************
*  编写：718创新实验室
*  平台：STM32F103VET6
*  说明：由于作者的水平有限，若有不足之处，还请大家谅解。
*		 建议大家多看看数据手册。     
******************************************************************/


/*************************功能说明********************************
*通过三路PWM控制舵机
*TIM2/5 通道2， PA1
*TIM2/5 通道3， PA2
*************************功能说明********************************/

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

//lalala
int i=0;

// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */



//-----------------------------------------------------------------------------------
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
		
		ADC_ConvertedValueLocal[3]=ADC_ConvertedValueLocal[3]+0.1;
		
		float SensorDevitation;
		float r_s=90;
    float LastSensorDevitation=0,enbig_1=215,ensmall_m=0.18;
    float pid_P,pid_D=0,pid_I=0,pid_center=1500,I_max=30;
    float g_Proportion=1.1,g_Differential=0.0000011,g_Integral=0.00000002;
    SensorDevitation = (sqrt(ADC_ConvertedValueLocal[3])*1.8-sqrt(ADC_ConvertedValueLocal[1]*1.35))/(ADC_ConvertedValueLocal[3]+ADC_ConvertedValueLocal[1]);
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
		//adjust: enbig,g_Proportion,g_Differential,g_Integral,I_max,delay.
		//-------------------servo control end here-----------------------------
		
		float encoderDevitation;
		float LastencoderDevitation,enbig_2;
		float pid_2p,pid_2d,pid_2i,pid_2center=220;
		float constant_P,constant_i,constant_d;
		encoderDevitation = 2333-2333;
		encoderDevitation = encoderDevitation*enbig_2;
		LastencoderDevitation = encoderDevitation;
		pid_2p=encoderDevitation*constant_P;
		pid_2d=(encoderDevitation-LastencoderDevitation)*constant_d;
		pid_2i+=encoderDevitation*constant_i;
		if(pid_2i > 100){pid_2i=100;}
		else if(pid_2i < -100){pid_2i=-100;}
		pid_m=pid_2p+pid_2d+pid_2i+pid_2center;
		
		if(ADC_ConvertedValueLocal[4]>1)
		{
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,pid_m-SensorDevitation*ensmall_m*3);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,pid_m-SensorDevitation*ensmall_m);//left positive
		}
		
		;
		if(ADC_ConvertedValueLocal[4]>3&&i==0)
		{
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
		/*motor_run(motor_1,100);//right negative
		motor_run(motor_2,100);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,100);//left positive*/
		
		/*else
		{
		motor_run(motor_1,100);//right negative
		motor_run(motor_2,150);//right positive
		motor_run(motor_3,100);//left negative
		motor_run(motor_4,150);//left positive
		}
		*/
		
		
		//adjust:,enbig_2,constant_P,constant_i,constant_d,I_max,over_m.
		//-----------------motor control end here------------------------------
		
	}
	
}

