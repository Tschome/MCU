#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f10x_conf.h"

extern void iwdg_init(int ms);//��ʼ���ĺ���(�����ڲ�����Ԥ��Ƶֵ����װ��ֵ)

extern void iwdg_feed_dog(void);//ι���Ĳ���

#endif



