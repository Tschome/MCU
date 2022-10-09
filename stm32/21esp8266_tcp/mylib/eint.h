#ifndef __EINT_H
#define __EINT_H
/*
使用中断的方式来获取按键
开发板设备	所连接的管脚	使用的外部中断号
KEY0				PC9						EXTI9
KEY1				PC8						EXTI8
KEY2				PA0						EXTI0
从原理图可知
KEY0和KEY1在按下时			检测到	低电平
KEY0和KEY1在没有按下时	检测到	高电平
KEY2在按下时						检测到	高电平
KEY2在没有按下时				检测到	低电平
*/
#include "stm32f10x_conf.h"//包含了该头文件所有的外设头文件均已包含

typedef void (*eint_handler)(void);//通过typedef关键字定义函数指针类型

extern void eint_init(void);//初始化的函数(用于初始化GPIO管脚和NVIC和EXTI)

extern void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2);//设置回调函数

#endif








