#ifndef __LDT_H
#define __LDT_H
/*
HC138_A0		PC11
HC138_A1		PC12
HC138_A2		PD2
HC595_DATA	PB3
HC595_LCLK	PB4
HC595_SCLK	PB5
��Ҫ���������,����ܵĹ��������ӵ���74HC138��
����ܵ�LED�����ӵ���74HC595
*/
#include "stm32f10x_conf.h"//�����˸�ͷ�ļ����е������ļ����Ѱ���

extern void ldt_init(void);//��ʼ���ĺ���(��ʼ��ģ��ʹ�õ��Ĺܽ�)

extern void hc138_out_data(uint8_t data);//ͨ��hc138ѡ������ܵĹ�����

extern void hc595_send_data(uint8_t data);//ͨ��hc595�Ѵ�������ת���ɲ�������

extern void digit_show_data(int data);//�����������ʾ����

#endif









