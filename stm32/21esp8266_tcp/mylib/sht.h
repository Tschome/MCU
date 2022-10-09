#ifndef __SHT_H
#define __SHT_H
/*
	��Ҫ����SHT30������,ʹ�õĽӿ���IIC,ʹ��GPIO��ģ��IIC��Э��
	SDA		PB7
	SCL		PB6
*/
#include "stm32f10x_conf.h"

#define SLAVE_ADDR 0x88//SHT30���豸��ַ
#define PERIODIC_MODE_HIGH 0x2737//����SHT30�Ĳ���Ƶ������
#define READOUT_PERIODIC_MODE 0xE000//��ȡSHT30���������ݵ�����

extern void sht_init(void);//��ʼ���ĺ���

extern void sht_write_mode(void);//����SHT30�������ڲ���������

extern void sht_write_read_cmd(void);//���Ͷ�ȡSHT30�ɼ����ݵ�����

extern void sht_read_data(double sht_data[2]);//��ȡSHT30�ɼ���������

#endif







