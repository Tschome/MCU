#include "eeprom.h"
#include "gpio_iic.h"

void eeprom_init(void)//��ʼ��eeprom�ĺ���
{
	IIC_Init();//��ʼ��IICʵ�õ���GPIO�ܽ�
}

void eeprom_byte_write(u8 daddr, u8 waddr, u8 data)//���ֽ���д
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Send_Byte(waddr);//���ʹ洢�ռ��ڲ��ĵ�ַ
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Send_Byte(data);//��������
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Stop();//���������ź�
}

void eeprom_page_write(u8 daddr, u8 waddr, u8 *buf, u8 size)//��ҳ��д
{
	u8 i = 0;//i����Ϊѭ������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ + д�ı�־
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Send_Byte(waddr);//����EEPROM�ڲ��洢�ռ�ĵ�ַ
	IIC_Wait_Ack();
	for(i = 0; i < size; i++)
	{
		IIC_Send_Byte(buf[i]);//��������
		IIC_Wait_Ack();//�ȴ�ACK
	}
	IIC_Stop();//���������ź�
}
	
u8 eeprom_cur_addr_read(u8 daddr)//��ǰ��ַ��
{
	u8 data = 0;
	
	IIC_Start();
	IIC_Send_Byte(daddr | 1);
	IIC_Wait_Ack();
	data = IIC_Recv_Byte(0);
	IIC_Stop();
	
	return data;
}

u8 eeprom_rand_read(u8 daddr, u8 waddr)//�����ַ��
{
	u8 data = 0;//data�������������ȡ��������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Send_Byte(waddr);//���ʹ洢�ռ��ڲ��ĵ�ַ
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr | 1);//�����豸��ַ
	IIC_Wait_Ack();//�ȴ�ACK
	data = IIC_Recv_Byte(0);//��ȡ����
	IIC_Stop();//���������ź�
	
	return data;//��data�����б��浽�����ݷ���
}

void eeprom_sequ_read(u8 daddr, u8 waddr, u8 *buf, u8 size)//˳���ַ��
{
	u8 i = 0;//i����Ϊѭ������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr);//�����豸��ַ
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Send_Byte(waddr);//����EEPROM�ڲ��洢�ռ�ĵ�ַ
	IIC_Wait_Ack();//�ȴ�ACK
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(daddr | 1);//�����豸��ַ + ���ı�־
	IIC_Wait_Ack();//�ȴ�ACK
	for(i = 0; i < size; i++)
	{
		if(i == size - 1)
			buf[i] = IIC_Recv_Byte(0);//��ȡ���ݲ�����ACK
		else
			buf[i] = IIC_Recv_Byte(1);//��ȡ���ݲ���ACK
	}
	IIC_Stop();//���������ź�
}











