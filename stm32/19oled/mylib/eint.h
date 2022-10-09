#ifndef __EINT_H
#define __EINT_H
/*
����	�ܽ�	�ⲿ�жϺ�
KEY0	PC9		EXTI9
KEY1	PC8		EXTI8
KEY2	PA0		EXTI0
KEY0 KEY1��û�а���ʱӦ�����ָߵ�ƽ,����Ӧ�����ֵ͵�ƽ
KEY2��û�а���ʱӦ�����ֵ͵�ƽ,����Ӧ�����ָߵ�ƽ
*/
#include "stm32f10x_conf.h"

typedef void(*eint_handler)(void);//ͨ��typedef�ؼ��ֶ����˺���ָ������

extern void eint_init(void);//��ʼ���ĺ���(���ڳ�ʼ��GPIO��EXTI�Լ�NVIC)

extern void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2);//���ûص�����

#endif





