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

extern void button_init(void);//������ʼ���ĺ���

extern int button_status(int nu);//ͨ��nu�������Ӧ������״̬

#endif




