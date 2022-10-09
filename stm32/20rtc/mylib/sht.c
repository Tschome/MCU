#include "sht.h"//IIC����
#include "gpio_iic.h"
#include "delay.h"

void sht_init(void)//��ʼ��SHT30�ĺ���(��ʼ���ܽ�)
{
	IIC_Init();//��ʼ��SHT30��ʹ�õ�GPIO�ܽ�
}

void sht_write_mode(void)//����SHT30�Ĳ���Ƶ��
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDR);//�����豸��ַ + д�ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH >> 8);//���Ͳ���ָ��ĸ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH & 0xFF);//���Ͳ���ָ��ĵ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Stop();//���������ź�
}

void sht_write_read_cmd(void)//���Ͷ�ȡSHT30���ݵ�ָ��
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDR);//�����豸��ַ + д�ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE >> 8);//���Ͷ�ȡ���ݵ�ָ��ĸ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE & 0xFF);//���Ͷ�ȡ���ݵ�ָ��ĵ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
}

void sht_read_data(double sht_data[2])//��ȡSHT30������������
{
	u8 i = 0;//ѭ������
	u8 data[6] = {0};//���ڴ洢��SHT30��ֱ�Ӷ���������
	u16 temp = 0;//�����洢�¶ȵ�16bit����
	u16 hum = 0;//�����洢ʪ�ȵ�16bit����
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDR | 0x01);//�����豸��ַ + ���ı�־
	while(IIC_Wait_Ack());//�ȴ�ACK
	for(i = 0; i < 6; i++)
	{
		if(i == 5)
			data[i] = IIC_Recv_Byte(0);//��ȡ���ݲ��Ҳ�����ACK
		else
			data[i] = IIC_Recv_Byte(1);//��ȡ���ݲ��Ҳ���ACK
	}
	IIC_Stop();//���������ź�
	
	temp = data[0] & 0xFF;//��ȡ�¶ȵĸ��ֽ�����
	temp <<= 8;//��֮ǰ��ȡ�������Ƶ����ֽ�
	temp |= data[1] & 0xFF;//��ȡ�¶ȵĵ��ֽ�����
	hum = data[3] & 0xFF;//��ȡʪ�ȵĸ��ֽ�����
	hum <<= 8;//��֮ǰ��ȡ�������Ƶ����ֽ�
	hum |= data[4] & 0xFF;//��ȡʪ�ȵĵ��ֽ�����
	
	sht_data[0] = (double)(-45 + 175 * (double)(temp) / 65535);
	sht_data[1] = (double)(100 * (double)(hum) / 65535);
}







