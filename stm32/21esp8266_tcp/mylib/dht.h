#ifndef __DHT_H
#define __DHT_H
/*
DHT11		PC10
在初始化时只需要PC10管脚的输入输出功能即可
既需要输入也需要输出
*/
#include "stm32f10x_conf.h"//包含了该头文件所有的外设头文件均已包含

extern void dht_init(void);//初始化的函数

extern void get_dht_value(char *buf);//获取DHT11采集的数据

#endif







