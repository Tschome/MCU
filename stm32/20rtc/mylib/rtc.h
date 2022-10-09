#ifndef __RTC_H
#define __RTC_H
/*
��������STM32оƬ�е�RTC����
����ֵ   : ���ض�ʱ�䵽��ǰʱ�������
ʱ��Ƶ�� : ʹ�õ���LSE(32.768KHz) + ��Ƶ 
(��Ƶ : ����Ӳ��Ϊ�˷�ֹ����Աд0��Ƶ,��Ƶϵ��Ĭ�ϼ�1)
*/
#include "stm32f10x_conf.h"

struct time_st
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

extern void set_time(struct time_st *t);//����ǵ�һ��ʹ��RTC��������ʱ��

extern void conv_time(struct time_st *t);//ת��ʱ��(����ֵת����������ʱ����)

extern void get_time(struct time_st *t);//��ȡʱ��

#endif







