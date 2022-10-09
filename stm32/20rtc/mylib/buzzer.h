#ifndef __BUZZER_H
#define __BUZZER_H
/*
BUZZER	PC7
输出高电平 响
输出低电平 不响
*/
#include "stm32f10x_conf.h"

extern void buzzer_init(void);//蜂鸣器的初始化

extern void buzzer_on(void);//蜂鸣器响

extern void buzzer_off(void);//蜂鸣器不响

#endif




