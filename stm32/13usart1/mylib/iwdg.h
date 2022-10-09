#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f10x_conf.h"

extern void iwdg_init(int ms);//初始化的函数(函数内部设置预分频值和重装载值)

extern void iwdg_feed_dog(void);//喂狗的操作

#endif



