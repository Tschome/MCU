#ifndef __LDT_H
#define __LDT_H
/*
HC595_SCLK	PB5	<SH_CP>
HC595_LCLK	PB4	<ST_CP>
HC595_DATA	PB3	<DS>
HC138_A2		PD2	
HC138_A1		PC12	
HC138_A0		PC11
*/
#include "stm32f10x_conf.h"

extern void ldt_init(void);//初始化的函数

extern void hc138_out_data(u8 data);//通过74HC138选择数码管的公共端

extern void hc595_send_data(u8 data);//通过74HC595把串行数据data转换成并行数据

extern void digit_show_data(int data);//把data变量中存储的数据显示到数码管中

#endif




