#ifndef __LED_H
#define __LED_H
/*
LED0	PC1
LED1	PC2
LED2	PC3
输出高电平 亮
输出低电平 灭
*/
#include "stm32f10x_conf.h"

extern void led_init(void);//初始化LED灯

extern void led_on(int nu);//通过形参nu选择点亮相应的LED灯

extern void led_off(int nu);//通过形参nu选择灭掉相应的LED灯

#endif







