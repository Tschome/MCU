#ifndef __BUZZER_H
#define __BUZZER_H
/*
BUZZER	PC7
����ߵ�ƽ ��
����͵�ƽ ����
*/
#include "stm32f10x_conf.h"

#define GPIOC_CRL *(volatile unsigned int *)(GPIOC_BASE + 0x00)
#define GPIOC_ODR *(volatile unsigned int *)(GPIOC_BASE + 0x0C)

extern void buzzer_init(void);//�������ĳ�ʼ��

extern void buzzer_on(void);//��������

extern void buzzer_off(void);//����������

#endif




