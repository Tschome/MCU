#ifndef __EEPROM_H
#define __EEPROM_H
/*
EEPROM��SDA��SCL���ӵ���PB6 PB7�ܽ�
ͨ��GPIO��ģ��IIC��Э��Ӷ�����EEPROM
*/
#include "stm32f10x_conf.h"

extern void eeprom_init(void);//��ʼ���ĺ���(����ֱ�ӵ���IIC_Init��ʼ������)

extern void eeprom_byte_write(u8 daddr, u8 waddr, u8 data);//���ֽ���д

extern void eeprom_page_write(u8 daddr, u8 waddr, u8 *buf, u8 size);//��ҳ��д

extern u8 eeprom_cur_addr_read(u8 daddr);//��ǰ��ַ��

extern u8 eeprom_rand_addr_read(u8 daddr, u8 waddr);//�����ַ��

extern void eeprom_sequ_read(u8 daddr, u8 waddr, u8 *buf, u8 size);//˳���ַ��

#endif




