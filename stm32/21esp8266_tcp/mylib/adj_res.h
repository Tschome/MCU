#ifndef __ADJ_RES_H
#define __ADJ_RES_H
/*
��Ҫ�����������ϵĸ߾��ȿɵ�����
ADC_VOL ----- PC0/ADC_IN10
��֪оƬ�Ĺܽ��Ƕ๦�ܸ����͵Ĺܽ�
���빦�� ������� ���ù��� ģ�⹦��
��һ����Ҫ����GPIOC���10�Źܽ�,��Ҫ��ʼ����ģ�⹦��
*/
#include "stm32f10x_conf.h"//�����˸�ͷ�ļ����е�����ͷ�ļ����Ѱ���

extern void adj_res_init(void);//��ʼ���߾��ȿɵ�����ĺ���(��ʼ����ʹ�õ���GPIO�ܽ��Լ�AD����)

extern int get_adj_res_value(void);//��ȡADת��֮��Ľ��

#endif









