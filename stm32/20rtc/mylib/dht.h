#ifndef __DHT_H
#define __DHT_H
/*
DHT11	PC10
����Ҫ����ģʽ(��������)Ҳ��Ҫ���ģʽ(�������)
*/
#include "stm32f10x_conf.h"

extern void dht_init(void);//��ʼ��DHT�ĺ���

extern void get_dht_value(char *buf);//��ȡDHT11������������

#endif




