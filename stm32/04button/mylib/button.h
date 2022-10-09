#ifndef __BUTTON_H
#define __BUTTON_H
/*
KEY0	PC9
KEY1	PC8
KEY2	PA0
KEY0 KEY1��û�а���ʱӦ�����ָߵ�ƽ,����Ӧ�����ֵ͵�ƽ
KEY2��û�а���ʱӦ�����ֵ͵�ƽ,����Ӧ�����ָߵ�ƽ
*/
#include "stm32f10x_conf.h"

#define GPIOA_CRL *(volatile unsigned int *)(GPIOA_BASE + 0x00)
#define GPIOA_IDR *(volatile unsigned int *)(GPIOA_BASE + 0x08)
#define GPIOA_ODR *(volatile unsigned int *)(GPIOA_BASE + 0x0C)

#define GPIOC_CRH *(volatile unsigned int *)(GPIOC_BASE + 0x04)
#define GPIOC_IDR *(volatile unsigned int *)(GPIOC_BASE + 0x08)
#define GPIOC_ODR *(volatile unsigned int *)(GPIOC_BASE + 0x0C)

extern void button_init(void);//������ʼ���ĺ���

extern int button_status(int nu);//ͨ��nu�������Ӧ������״̬

#endif




