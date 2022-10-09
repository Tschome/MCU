#ifndef __SHT_H
#define __SHT_H
/*
	需要驱动SHT30传感器,使用的接口是IIC,使用GPIO来模拟IIC的协议
	SDA		PB7
	SCL		PB6
*/
#include "stm32f10x_conf.h"

#define SLAVE_ADDR 0x88//SHT30的设备地址
#define PERIODIC_MODE_HIGH 0x2737//配置SHT30的采样频率命令
#define READOUT_PERIODIC_MODE 0xE000//读取SHT30传感器数据的命令

extern void sht_init(void);//初始化的函数

extern void sht_write_mode(void);//配置SHT30传感器内部采样速率

extern void sht_write_read_cmd(void);//发送读取SHT30采集数据的命令

extern void sht_read_data(double sht_data[2]);//读取SHT30采集到的数据

#endif







