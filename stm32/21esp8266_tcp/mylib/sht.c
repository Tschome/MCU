#include "sht.h"
#include "gpio_iic.h"
#include "delay.h"
#include "led.h"

void sht_init(void)//��ʼ���ĺ���
{
	IIC_Init();//��ʼ��SHT30��ʹ�õ���GPIO�ܽ�
}

void sht_write_mode(void)//����SHT30�������ڲ���������
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDR);//�����豸��ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH >> 8);//���Ͳ�������ĸ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH & 0xFF);//���Ͳ�������ĵ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Stop();//���������ź�
	delay_ms(5);//5�������ʱ
}

void sht_write_read_cmd(void)//���Ͷ�ȡSHT30�ɼ����ݵ�����
{
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDR);//�����豸��ַ
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE >> 8);//���ͻ�ȡ��������ĸ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE & 0xFF);//���ͻ�ȡ��������ĵ��ֽ�
	while(IIC_Wait_Ack());//�ȴ�ACK
}

void sht_read_data(double sht_data[2])//��ȡSHT30�ɼ���������
{
	u8 buf[6] = {0};//�洢SHT30����������
	u16 Temp = 0;
	u16 Hum = 0;
	u8 i = 0;//i����Ϊѭ������
	
	IIC_Start();//������ʼ�ź�
	IIC_Send_Byte(SLAVE_ADDR | 0x01);//�����豸��ַ + ���ı�־
	delay_us(5);//5΢�����ʱ
	while(IIC_Wait_Ack());//�ȴ�ACK
	for(i = 0; i < 6; i++)
	{
		if(i == 5)
			buf[i] = IIC_Recv_Byte(0);//�����ݣ�����Ҫ����ACK
		else
			buf[i] = IIC_Recv_Byte(1);//�����ݣ�����ACK
	}
	IIC_Stop();
	//////////////////////////////////ת������
	
	Temp = buf[0] & 0xFF;
	Temp <<= 8;
	Temp |= buf[1] & 0xFF;
	Hum = buf[3] & 0xFF;
	Hum <<= 8;
	Hum |= buf[4] & 0xFF;
	
	sht_data[0] = (double)(-45 + 175 * (double)(Temp) / 65535);
	sht_data[1] = (double)(100 * (double)(Hum) / 65535);
}







