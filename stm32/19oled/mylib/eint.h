#ifndef __EINT_H
#define __EINT_H
/*
按键	管脚	外部中断号
KEY0	PC9		EXTI9
KEY1	PC8		EXTI8
KEY2	PA0		EXTI0
KEY0 KEY1在没有按下时应当呈现高电平,按下应当呈现低电平
KEY2在没有按下时应当呈现低电平,按下应当呈现高电平
*/
#include "stm32f10x_conf.h"

typedef void(*eint_handler)(void);//通过typedef关键字定义了函数指针类型

extern void eint_init(void);//初始化的函数(用于初始化GPIO和EXTI以及NVIC)

extern void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2);//设置回调函数

#endif





