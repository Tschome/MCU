#ifndef __ADJ_RES_H
#define __ADJ_RES_H
/*
��Ҫ�����������ϵĸ߾��ȿɵ�����
ADC_VOL----PC0/ADC_IN10
��֪оƬ�Ĺܽ��Ƕ๦�ܸ����͵Ĺܽ�
����ģʽ ���ģʽ ����ģʽ ģ��ģʽ
��һ����Ҫ����GPIOC���0�ܽ�,��Ҫ��ʼ����ģ������ģʽ
*/
#include "stm32f10x_conf.h"

extern void adj_res_init(void);//��ʼ���߾��ȿɵ�����ĺ���

extern int get_adj_res_value(void);//��ȡADת��֮��Ľ��

#endif




