#include "ldt.h"
#include "bitband.h"
#include "delay.h"

#define HC595_SCLK	PBOut(5)
#define HC595_LCLK	PBOut(4)
#define HC595_DATA	PBOut(3)
#define HC138_A2		PDOut(2)	
#define HC138_A1		PCOut(12)	
#define HC138_A0		PCOut(11)

void ldt_init(void)//��ʼ���ĺ���
{
	GPIO_InitTypeDef Gpio_Value;//����GPIO��ʼ���Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	//ͨ��APB2����ʹ��GPIOB GPIOC GPIOD AFIO��ʱ��
	//��Ҫ��PB3�ܽŵ�JTAG���ܹر�
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	//�ı�ָ���ܽŵ�ӳ��(JTAG-DP�ر� + SW-DPʹ��)
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ�����������
	Gpio_Value.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;//ѡ����3 4 5�Źܽ�
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz���������
	GPIO_Init(GPIOB, &Gpio_Value);//�����������ó�ʼ��GPIOB��Ĺܽ�
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;//ѡ����11 12�Źܽ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_2;//ѡ����2�Źܽ�
	GPIO_Init(GPIOD, &Gpio_Value);//�����������ó�ʼ��GPIOD��Ĺܽ�
}

void hc138_out_data(u8 data)//ͨ��74HC138ѡ������ܵĹ�����
{
	switch(data)
	{
		case 0 : HC138_A2 = 0; HC138_A1 = 0; HC138_A0 = 0; break;//ѡ����CH1������
		case 1 : HC138_A2 = 0; HC138_A1 = 0; HC138_A0 = 1; break;//ѡ����CH2������
		case 2 : HC138_A2 = 0; HC138_A1 = 1; HC138_A0 = 0; break;//ѡ����CH3������
		case 3 : HC138_A2 = 0; HC138_A1 = 1; HC138_A0 = 1; break;//ѡ����CH4������
	}
}

void hc595_send_data(u8 data)//ͨ��74HC595�Ѵ�������dataת���ɲ�������
{
	u8 i = 0;//ѭ������
	
	for(i = 0; i < 8; i++)
	{
		HC595_SCLK = 0;//����λ�Ĵ�����ʱ��������
		if(data & 0x80)//�ж�data����������������λ�Ƿ�Ϊ1
			HC595_DATA = 1;//�����λ���ݽ���DS������
		else
			HC595_DATA = 0;//�����λ���ݽ���DS������
		data <<= 1;//��data�����д洢����������1λ
		HC595_SCLK = 1;//����λ�Ĵ�����ʱ��������
	}
	HC595_LCLK = 0;//�Ѵ洢�Ĵ�����ʱ��������
	HC595_LCLK = 1;//�Ѵ洢�Ĵ�����ʱ��������
}

void digit_show_data(int data)//��data�����д洢��������ʾ���������
{
	char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	//���干��������ܵı���
	u8 d[4] = {0};//���ڴ洢data�����е�ÿһλ
	u8 i = 0;//ѭ������,ѡ���������ʾ����
	
	d[0] = data / 1000;//�洢ǧλ
	d[1] = data / 100 % 10;//�洢��λ
	d[2] = data / 10 % 10;//�洢ʮλ
	d[3] = data % 10;//�洢��λ

	for(i = 0; i < 4; i++)
	{
		hc138_out_data(i);//ͨ��ѭ������i��ֵѡ�񹫹���
		hc595_send_data(table[d[i]]);
		//ͨ��d�����ҵ�����,��ͨ��table�����ҵ����ݵı���
		//�ٰѱ��뽻��hc595����ת��
		delay_ms(1);//��ʱ1ms
		hc595_send_data(0);//�ֶ����74HC595ģ���е�8bit��λ�Ĵ���
	}
}






