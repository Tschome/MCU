#ifndef __EINT_H
#define __EINT_H
/*
ʹ���жϵķ�ʽ����ȡ����
�������豸	�����ӵĹܽ�	ʹ�õ��ⲿ�жϺ�
KEY0				PC9						EXTI9
KEY1				PC8						EXTI8
KEY2				PA0						EXTI0
��ԭ��ͼ��֪
KEY0��KEY1�ڰ���ʱ			��⵽	�͵�ƽ
KEY0��KEY1��û�а���ʱ	��⵽	�ߵ�ƽ
KEY2�ڰ���ʱ						��⵽	�ߵ�ƽ
KEY2��û�а���ʱ				��⵽	�͵�ƽ
*/
#include "stm32f10x_conf.h"//�����˸�ͷ�ļ����е�����ͷ�ļ����Ѱ���

typedef void (*eint_handler)(void);//ͨ��typedef�ؼ��ֶ��庯��ָ������

extern void eint_init(void);//��ʼ���ĺ���(���ڳ�ʼ��GPIO�ܽź�NVIC��EXTI)

extern void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2);//���ûص�����

#endif








