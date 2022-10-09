#ifndef __DHT_H
#define __DHT_H
/*
DHT11	PC10
既需要输入模式(浮空输入)也需要输出模式(推挽输出)
*/
#include "stm32f10x_conf.h"

extern void dht_init(void);//初始化DHT的函数

extern void get_dht_value(char *buf);//获取DHT11传感器的数据

#endif




