#include "eeprom.h"
#include "gpio_iic.h"

void eeprom_init(void)//��ʼ���ĺ���(����ֱ�ӵ���IIC_Init��ʼ������)
{
	IIC_Init();//��ʼ��IIC��ʹ�õ���GPIO�ܽ�
}

void eeprom_byte_write(u8 daddr, u8 waddr, u8 data)//���ֽ���д
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ0xA0
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(waddr);//�����ڲ��洢�ռ�ĵ�ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(data);//��������
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Stop();//���������ź�
}

void eeprom_page_write(u8 daddr, u8 waddr, u8 *buf, u8 size)//��ҳ��д
{
}

u8 eeprom_cur_addr_read(u8 daddr)//��ǰ��ַ��
{
}

u8 eeprom_rand_addr_read(u8 daddr, u8 waddr)//�����ַ��
{
}

void eeprom_sequ_read(u8 daddr, u8 waddr, u8 *buf, u8 size)//˳���ַ��
{
}






