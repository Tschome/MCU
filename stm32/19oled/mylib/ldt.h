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

extern void ldt_init(void);//��ʼ���ĺ���

extern void hc138_out_data(u8 data);//ͨ��74HC138ѡ������ܵĹ�����

extern void hc595_send_data(u8 data);//ͨ��74HC595�Ѵ�������dataת���ɲ�������

extern void digit_show_data(int data);//��data�����д洢��������ʾ���������

#endif




