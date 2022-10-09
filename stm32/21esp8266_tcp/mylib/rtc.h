#ifndef __RTC_H
#define __RTC_H
/*
���ļ���������STM32F103RBT6оƬ��RTC������
ʱ��Ƶ��ʹ�õ���LSE��Ԥ��Ƶ = 1Hz
����ֵ�������洢������
���Ǳ�ʾ��ʱ�䷶ΧΪ
1970/1/1 00:00:00 ----- 2099/12/31 23:59:59
*/
#include "stm32f10x_conf.h"//�����˸�ͷ�ļ����е�����ͷ�ļ����Ѱ���

struct time_st//���ڴ洢���ں�ʱ��Ľṹ��
{
	int Y;//���
	int M;//�·�
	int D;//����
	int W;//����
	int h;//Сʱ
	int m;//����
	int s;//����
};

extern void rtc_init(struct time_st *t);//��ʼ��RTC

extern void set_time(struct time_st *t);//����ʱ��

extern void conv_time(struct time_st *t);//ת��ʱ��

extern void get_time(struct time_st *t);//��ȡʱ��

#endif







