#ifndef __BUTTON_H
#define __BUTTON_H
/*
KEY0	PC9
KEY1	PC8
WK_UP	PA0
从原理图中可知
当按键按下GPIO管脚检测到低电平
当按键在没有按下时GPIO管脚检测到高电平
*/
#include "stm32f10x_conf.h"

extern void button_init(void);//初始化的函数(初始化按键所连接的GPIO管脚)

extern int button_status(int nu);//根据参数nu检测相应的功能按键是否被按下

#endif






