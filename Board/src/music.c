#include "music.h"

/**
  * @brief  music——aircity
  * @param  无
  * @retval 无
  * @note   无
  */
void aircity(void)
{
  while(1)
  {    
    delay_ms(200);//初始延时
    
    //开始演奏
    BuzzerBeep(LA_m,50);
    BuzzerBeep(SI_m,50);
    
    for(int i=0; i<2; i++) 
    {
      BuzzerBeep(DO_h,150);
      BuzzerBeep(SI_m,50);
      BuzzerBeep(DO_h,100);
      BuzzerBeep(MI_h,100);
      
      BuzzerBeep(SI_m,300);
      BuzzerBeep(MI_m,50);
      BuzzerBeep(MI_m,50);
      
      BuzzerBeep(LA_m,150);
      BuzzerBeep(SO_m,50);
      BuzzerBeep(LA_m,100);
      BuzzerBeep(DO_h,100);
      
      BuzzerBeep(SO_m,200);
      BuzzerBeep(0,100);	
      BuzzerBeep(MI_m,100);
      
      BuzzerBeep(FA_m,150);
      BuzzerBeep(MI_m,50);
      BuzzerBeep(FA_m,50);
      BuzzerBeep(DO_h,150);
      
      BuzzerBeep(MI_m,200);
      BuzzerBeep(0,50);
      BuzzerBeep(DO_h,50);	
      BuzzerBeep(DO_h,50);	
      BuzzerBeep(DO_h,50);
      
      BuzzerBeep(SI_m,150);
      BuzzerBeep(FA_m_r,50);
      BuzzerBeep(FA_m_r,100);
      BuzzerBeep(SI_m,100);
      
      BuzzerBeep(SI_m,200);
      BuzzerBeep(0,100);
      BuzzerBeep(LA_m,50);
      BuzzerBeep(SI_m,50);
      
      BuzzerBeep(DO_h,150);
      BuzzerBeep(SI_m,50);
      BuzzerBeep(DO_h,100);
      BuzzerBeep(MI_h,100);
      
      BuzzerBeep(SI_m,200);
      BuzzerBeep(0,100);
      BuzzerBeep(MI_m,50);
      BuzzerBeep(MI_m,50);
      
      BuzzerBeep(LA_m,150);
      BuzzerBeep(SO_m,50);
      BuzzerBeep(LA_m,100);
      BuzzerBeep(DO_h,100);
      
      BuzzerBeep(SO_m,300);
      BuzzerBeep(0,50);
      BuzzerBeep(MI_m,50);
      
      
      BuzzerBeep(FA_m,100);
      BuzzerBeep(DO_h,50);
      BuzzerBeep(SI_m,50);
      BuzzerBeep(SI_m,100);
      BuzzerBeep(DO_h,100);
      
      BuzzerBeep(RE_h,50);
      BuzzerBeep(RE_h,50);
      BuzzerBeep(MI_h,50);
      BuzzerBeep(DO_h,150);
      BuzzerBeep(0,100);
      
      BuzzerBeep(DO_h,50);
      BuzzerBeep(SI_m,50);
      BuzzerBeep(LA_m,50);
      BuzzerBeep(LA_m,50);
      BuzzerBeep(SI_m,100);
      BuzzerBeep(SO_m_r,100);//
      
      if (1 == i) break;
      
      BuzzerBeep(LA_m,200);
      BuzzerBeep(0,100);
      BuzzerBeep(DO_h,50);
      BuzzerBeep(RE_h,50);
      
      BuzzerBeep(MI_h,150); 
      BuzzerBeep(RE_h,50);
      BuzzerBeep(MI_h,100); 
      BuzzerBeep(SO_h,100);
      
      BuzzerBeep(RE_h,200);
      BuzzerBeep(0,100);
      BuzzerBeep(SO_m,50);
      BuzzerBeep(SO_m,50);
      
      BuzzerBeep(DO_h,150);
      BuzzerBeep(SI_m,50);
      BuzzerBeep(DO_h,100);
      BuzzerBeep(MI_h,100);
      
      BuzzerBeep(MI_h,200);
      BuzzerBeep(0,200);
      
      BuzzerBeep(LA_m,50);
      BuzzerBeep(SI_m,50);
      BuzzerBeep(DO_h,100);
      BuzzerBeep(SI_m,100);
      BuzzerBeep(RE_h,50);
      BuzzerBeep(RE_h,50);
      
      BuzzerBeep(DO_h,150);
      BuzzerBeep(SO_m,150);
      BuzzerBeep(0,100);
      
      BuzzerBeep(FA_h,100);
      BuzzerBeep(MI_h,100);
      BuzzerBeep(RE_h,100);
      BuzzerBeep(DO_h,100);
      
      BuzzerBeep(MI_h,400);
      
      BuzzerBeep(MI_h,100);
      BuzzerBeep(0,200);
      BuzzerBeep(MI_h,100);
      
      BuzzerBeep(LA_h,200);
      BuzzerBeep(SO_h,100);
      BuzzerBeep(SO_h,100);
      
      BuzzerBeep(MI_h,50);
      BuzzerBeep(RE_h,50);
      BuzzerBeep(DO_h,200);       
      BuzzerBeep(0,50);
      BuzzerBeep(DO_h,50);
      
      BuzzerBeep(RE_h,100);
      BuzzerBeep(DO_h,50);
      BuzzerBeep(RE_h,50);
      BuzzerBeep(RE_h,100);
      BuzzerBeep(SO_h,100);
      
      BuzzerBeep(MI_h,200);
      BuzzerBeep(0,100);
      BuzzerBeep(MI_h,100);
      
      BuzzerBeep(LA_h,200);
      BuzzerBeep(SO_h,200);
      
      BuzzerBeep(MI_h,50);
      BuzzerBeep(RE_h,50);
      BuzzerBeep(DO_h,200);
      BuzzerBeep(0,50);
      BuzzerBeep(DO_h,50);
      
      BuzzerBeep(RE_h,100);
      BuzzerBeep(DO_h,50);
      BuzzerBeep(RE_h,150);
      BuzzerBeep(SI_m,100);
      
      BuzzerBeep(LA_m,200);        
      BuzzerBeep(0,100);
      BuzzerBeep(LA_m,50);
      BuzzerBeep(SI_m,50);
    }    
    BuzzerBeep(LA_m,400);
    
  }
  BuzzerBeep(0,800);
}

/**
  * @brief  music——birthday
  * @param  无
  * @retval 无
  * @note   无
  */
void birthday (void)
{
		Led_Set(LED_ALL, 1);
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED_ALL, 0);
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED_ALL, 1);
		BuzzerBeep(LA_m,75);//6
		Led_Set(LED_ALL, 0);
		BuzzerBeep(LA_m,75);//6
		Led_Set(LED_ALL, 1);
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED_ALL, 0);
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED_ALL, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED_ALL, 0);
		BuzzerBeep(DO_h,75);//1
		
		
		BuzzerBeep(SI_m,75);//7
		BuzzerBeep(SI_m,75);//7
		BuzzerBeep(SI_m,75);//7
		BuzzerBeep(SI_m,75);//7---
		Led_Set(LED_ALL, 1);
    BuzzerBeep(SO_m,75);//5
		Led_Set(LED1, 0);
    BuzzerBeep(SO_m,75);//5
		Led_Set(LED2, 0);
		BuzzerBeep(LA_m,75);//6
		Led_Set(LED3, 0);
		BuzzerBeep(LA_m,75);//6
		Led_Set(LED4, 0);
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED5, 0);
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED6, 0);
		BuzzerBeep(RE_h,75);//2
		BuzzerBeep(RE_h,75);//2
		Led_Set(LED_ALL, 1);
		
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED_ALL, 0);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED_ALL, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED_ALL, 0);
		BuzzerBeep(DO_h,75);//1---
		Led_Set(LED_ALL, 0);
		BuzzerBeep(SO_m,75);//5
		
		BuzzerBeep(SO_m,75);//5
		Led_Set(LED6, 1);
		BuzzerBeep(SO_h,75);//5
		BuzzerBeep(SO_h,75);//5
		Led_Set(LED5, 1);
		BuzzerBeep(MI_h,75);//3
		BuzzerBeep(MI_h,75);//3
		Led_Set(LED4, 1);
		BuzzerBeep(DO_h,75);//1
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED3, 1);
		
		BuzzerBeep(SI_m,75);//7
		BuzzerBeep(SI_m,75);//7
		Led_Set(LED2, 1);
		BuzzerBeep(LA_m,75);//6
		BuzzerBeep(LA_m,75);//6
		Led_Set(LED1, 1);
		BuzzerBeep(LA_m,75);//6
		BuzzerBeep(LA_m,75);//6----
		delay_ms(75);//0
		delay_ms(75);//0
		Led_Set(LED6, 1);
		Led_Set(LED4, 1);
		Led_Set(LED2, 1);
		Led_Set(LED5, 0);
		Led_Set(LED3, 0);
		Led_Set(LED1, 0);
		delay_ms(75);//0
		delay_ms(75);//0
		BuzzerBeep(FA_h,75);//4
		BuzzerBeep(FA_h,75);//4
		Led_Set(LED6, 0);
		Led_Set(LED4, 0);
		Led_Set(LED2, 0);
		Led_Set(LED5, 1);
		Led_Set(LED3, 1);
		Led_Set(LED1, 1);
		BuzzerBeep(FA_h,75);//4
		BuzzerBeep(FA_h,75);//4
		Led_Set(LED6, 1);
		Led_Set(LED4, 1);
		Led_Set(LED2, 1);
		Led_Set(LED5, 0);
		Led_Set(LED3, 0);
		Led_Set(LED1, 0);
		
		BuzzerBeep(MI_h,75);//3
		BuzzerBeep(MI_h,75);//3
		Led_Set(LED6, 0);
		Led_Set(LED4, 0);
		Led_Set(LED2, 0);
		Led_Set(LED5, 1);
		Led_Set(LED3, 1);
		Led_Set(LED1, 1);
		BuzzerBeep(DO_h,75);//1
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED6, 1);
		Led_Set(LED4, 1);
		Led_Set(LED2, 1);
		Led_Set(LED5, 0);
		Led_Set(LED3, 0);
		Led_Set(LED1, 0);
		BuzzerBeep(RE_h,75);//2
		BuzzerBeep(RE_h,75);//2
		
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 0);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 1);
		Led_Set(LED5, 1);
		Led_Set(LED6, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 0);
		Led_Set(LED3, 1);
		Led_Set(LED4, 1);
		Led_Set(LED5, 1);
		Led_Set(LED6, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 0);
		Led_Set(LED4, 1);
		Led_Set(LED5, 1);
		Led_Set(LED6, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 0);
		Led_Set(LED5, 1);
		Led_Set(LED6, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 1);
		Led_Set(LED5, 0);
		Led_Set(LED6, 1);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 1);
		Led_Set(LED5, 1);
		Led_Set(LED6, 0);
		
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 1);
		Led_Set(LED5, 1);
		Led_Set(LED6, 0);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 1);
		Led_Set(LED5, 0);
		Led_Set(LED6, 0);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 1);
		Led_Set(LED4, 0);
		Led_Set(LED5, 0);
		Led_Set(LED6, 0);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 1);
		Led_Set(LED3, 0);
		Led_Set(LED4, 0);
		Led_Set(LED5, 0);
		Led_Set(LED6, 0);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED1, 1);
		Led_Set(LED2, 0);
		Led_Set(LED3, 0);
		Led_Set(LED4, 0);
		Led_Set(LED5, 0);
		Led_Set(LED6, 0);
		BuzzerBeep(DO_h,75);//1
		Led_Set(LED_ALL, 0);
		delay_ms(75);//0
}






