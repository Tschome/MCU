#ifndef __IWDG_H
#define __IWDG_H
/*
�йض������Ź��Ĳ���
��STM32F10X���Ĳο��ֲ��п�֪���������Ź���ʱ��Դ����LSI�ṩ(������Ƶ)
��STM32F10X���Ĳο��ֲ��п�֪���������Ź��ļ���ֵΪ 0 ~ 2��12�η�-1(0 ~ 4095)
*/
#include "stm32f10x_conf.h"//�����˸�ͷ�ļ����е�����ͷ�ļ����Ѱ���

extern void iwdg_init(int ms);//��ʼ���ĺ���(�������ڲ�����Ԥ��Ƶ���ͼ���ֵ)

extern void iwdg_feed_dog(void);//ι���Ĺ��ܺ���

#endif










