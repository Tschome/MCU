#ifndef __BUTTON_H
#define __BUTTON_H
/*
KEY0	PC9
KEY1	PC8
KEY2	PA0
KEY0 KEY1在没有按下时应当呈现高电平,按下应当呈现低电平
KEY2在没有按下时应当呈现低电平,按下应当呈现高电平
*/
#include "stm32f10x_conf.h"

extern void button_init(void);//按键初始化的函数

extern int button_status(int nu);//通过nu来检测相应按键的状态

#endif




