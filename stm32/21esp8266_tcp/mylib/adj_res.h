#ifndef __ADJ_RES_H
#define __ADJ_RES_H
/*
需要驱动开发板上的高精度可调电阻
ADC_VOL ----- PC0/ADC_IN10
已知芯片的管脚是多功能复用型的管脚
输入功能 输出功能 复用功能 模拟功能
这一次需要操作GPIOC组的10号管脚,需要初始化成模拟功能
*/
#include "stm32f10x_conf.h"//包含了该头文件所有的外设头文件均已包含

extern void adj_res_init(void);//初始化高精度可调电阻的函数(初始化所使用到的GPIO管脚以及AD功能)

extern int get_adj_res_value(void);//获取AD转换之后的结果

#endif









