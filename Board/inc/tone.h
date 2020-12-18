#ifndef  _TONE_H
#define  _TONE_H

#include "stm32f10x.h"
#include "include.h"	
//此处音调所对应的值并不是频率，为了改变定时器的溢出频率更加方便，将频率转变成了相应的周期
//公式：time = 1/freq*1000000us

//low
#define DO_l 3817
#define RE_l 3401
#define MI_l 3030
#define FA_l 2865
#define SO_l 2551
#define LA_l 2273
#define SI_l 2024
//midumn
#define DO_m 1912
#define RE_m 1704
#define MI_m 1517
#define FA_m 1433
#define SO_m 1276
#define LA_m 1136
#define SI_m 1012
//high
#define DO_h 956
#define RE_h 851
#define MI_h 759
#define FA_h 716
#define SO_h 638
#define LA_h 568
#define SI_h 508

//extra define
#define FA_m_r 1351
#define SO_m_r 1205

//附各个音调对应频率
/*
//low
#define DO_l 262
#define RE_l 294
#define MI_l 330
#define FA_l 349
#define SO_l 392
#define LA_l 440
#define SI_l 494
//midumn
#define DO_m 523
#define RE_m 587
#define MI_m 659
#define FA_m 698
#define SO_m 784
#define LA_m 880
#define SI_m 988
//high  
#define DO_h 1047
#define RE_h 1175
#define MI_h 1319
#define FA_h 1397
#define SO_h 1568
#define LA_h 1760
#define SI_h 1967
//extra define
#define FA_m_r 740
#define SO_m_r 830

*/

extern void TIM_PWM_Init(uint16_t arr,uint16_t psc);

extern void beep_beat(uint16_t tone,uint16_t time);

extern void BuzzerBeep(uint16_t tone,uint16_t time); 


#else
	
#endif

