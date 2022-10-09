#ifndef __LED_H
#define __LED_H
/*
LED0	PC1
LED1	PC2
LED2	PC3
����ߵ�ƽ ��
����͵�ƽ ��
*/
#include "stm32f10x_conf.h"

#define GPIOC_CRL *(volatile unsigned int *)(GPIOC_BASE + 0x00)
#define GPIOC_ODR *(volatile unsigned int *)(GPIOC_BASE + 0x0C)

extern void led_init(void);//��ʼ��LED��

extern void led_on(int nu);//ͨ���β�nuѡ�������Ӧ��LED��

extern void led_off(int nu);//ͨ���β�nuѡ�������Ӧ��LED��

#endif






