#ifndef __RTC_H
#define __RTC_H
/*
用于驱动STM32芯片中的RTC外设
计数值   : 从特定时间到当前时间的秒数
时钟频率 : 使用的是LSE(32.768KHz) + 分频 
(分频 : 由于硬件为了防止程序员写0分频,分频系数默认加1)
*/
#include "stm32f10x_conf.h"

struct time_st
{
	int Y;//年份
	int M;//月份
	int D;//日期
	int W;//星期
	int h;//小时
	int m;//分钟
	int s;//秒数
};

extern void rtc_init(struct time_st *t);//初始化RTC

extern void set_time(struct time_st *t);//如果是第一次使用RTC可以设置时间

extern void conv_time(struct time_st *t);//转换时间(计数值转换成年月日时分秒)

extern void get_time(struct time_st *t);//获取时间

#endif







