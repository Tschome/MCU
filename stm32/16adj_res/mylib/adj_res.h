#ifndef __ADJ_RES_H
#define __ADJ_RES_H
/*
需要驱动开发板上的高精度可调电阻
ADC_VOL----PC0/ADC_IN10
已知芯片的管脚是多功能复用型的管脚
输入模式 输出模式 复用模式 模拟模式
这一次需要操作GPIOC组的0管脚,需要初始化成模拟输入模式
*/
#include "stm32f10x_conf.h"

extern void adj_res_init(void);//初始化高精度可调电阻的函数

extern int get_adj_res_value(void);//获取AD转换之后的结果

#endif




