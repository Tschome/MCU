#ifndef __DHT_H
#define __DHT_H
/*
DHT11		PC10
�ڳ�ʼ��ʱֻ��ҪPC10�ܽŵ�����������ܼ���
����Ҫ����Ҳ��Ҫ���
*/
#include "stm32f10x_conf.h"//�����˸�ͷ�ļ����е�����ͷ�ļ����Ѱ���

extern void dht_init(void);//��ʼ���ĺ���

extern void get_dht_value(char *buf);//��ȡDHT11�ɼ�������

#endif







