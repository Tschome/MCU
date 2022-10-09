#ifndef __SHT_H
#define __SHT_H
/*
需要驱动SHT30传感器,使用的接口是IIC接口,IIC总线
使用的是用GPIO的方式模拟IIC的协议
*/
#include "stm32f10x_conf.h"

#define SLAVE_ADDR 0x88//SHT30的设备地址
#define PERIODIC_MODE_HIGH 0x2737//配置SHT30传感器的采样频率指令
#define READOUT_PERIODIC_MODE 0xE000//读取SHT30传感器数据的指令

extern void sht_init(void);//初始化SHT30的函数(初始化管脚)

extern void sht_write_mode(void);//配置SHT30的采样频率

extern void sht_write_read_cmd(void);//发送读取SHT30数据的指令

extern void sht_read_data(double sht_data[2]);//读取SHT30传感器的数据

#endif




