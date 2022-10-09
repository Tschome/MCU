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
	u8 i = 0;//ѭ������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//���ʹ��豸���豸��ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(waddr);//�����ڲ��洢�ռ�ĵ�ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	for(i = 0; i < size; i++)
	{
		IIC_Send_Byte(buf[i]);//��������
		while(IIC_Wait_Ack());//�ȴ�ACK
	}
	IIC_Stop();//���������ź�
}

u8 eeprom_cur_addr_read(u8 daddr)//��ǰ��ַ��
{
	u8 data = 0;//ͨ��data�������ն�ȡ��������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr | 1);//�����豸��ַ + ���ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	data = IIC_Recv_Byte(0);//��ȡ����,���Ҳ�����ACK
	IIC_Stop();//���������ź�
	
	return data;//�Ѷ�ȡ�������ݷ���
}

u8 eeprom_rand_addr_read(u8 daddr, u8 waddr)//�����ַ��
{
	u8 data = 0;//ͨ��data�������ն�ȡ��������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ + д�ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(waddr);//�����ڲ��洢�ռ�ĵ�ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr | 1);//�����豸��ַ + ���ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	data = IIC_Recv_Byte(0);//��ȡ����,���Ҳ�����ACK
	IIC_Stop();//���������ź�
	
	return data;//�Ѷ�ȡ�������ݷ���
}

void eeprom_sequ_read(u8 daddr, u8 waddr, u8 *buf, u8 size)//˳���ַ��
{
	u8 i = 0;//ѭ������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ + д�ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(waddr);//�����ڲ��洢�ռ�ĵ�ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr | 1);//�����豸��ַ + ���ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	for(i = 0; i < size; i++)
	{
		if(i == size - 1)
			buf[i] = IIC_Recv_Byte(0);//��ȡ���һ���ֽ�����,������ACK
		else
			buf[i] = IIC_Recv_Byte(1);//��ȡ����,����ACK
	}
	IIC_Stop();//���������ź�
}






