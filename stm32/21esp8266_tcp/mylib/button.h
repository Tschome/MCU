#ifndef __BUTTON_H
#define __BUTTON_H
/*
KEY0	PC9
KEY1	PC8
WK_UP	PA0
��ԭ��ͼ�п�֪
����������GPIO�ܽż�⵽�͵�ƽ
��������û�а���ʱGPIO�ܽż�⵽�ߵ�ƽ
*/
#include "stm32f10x_conf.h"

extern void button_init(void);//��ʼ���ĺ���(��ʼ�����������ӵ�GPIO�ܽ�)

extern int button_status(int nu);//���ݲ���nu�����Ӧ�Ĺ��ܰ����Ƿ񱻰���

#endif






