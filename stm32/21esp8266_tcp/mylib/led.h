#ifndef __LED_H
#define __LED_H
/*
LED0	PC1
LED1	PC2
LED2	PC3
��ԭ��ͼ����֪
GPIO�ܽ�����ߵ�ƽ	����
GPIO�ܽ�����͵�ƽ	����
��ʼ��ʱ
1.ͨ��APB2���߰�GPIOC���ʱ��ʹ��
2.ʱ��ʹ��֮��������ʼ��
*/

#include "stm32f10x_conf.h"//����ST��˾�ṩ��ͷ�ļ�

extern void led_init(void);//��ʼ��

extern void led_on(int nu);//����nu��������

extern void led_off(int nu);//����nu�������

#endif





