#include "dht.h"
#include "bitband.h"
#include "delay.h"

void set_dht_gpio_output(void)//��PC10�ܽų�ʼ�������ģʽ
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO�̼��Ľṹ�����
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ������������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//ѡ���� 10 �Źܽ�
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz������ٶ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
}	

void set_dht_gpio_input(void)//��PC10�ܽų�ʼ��������ģʽ
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO�̼��Ľṹ�����
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//ѡ���˸��������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//ѡ���� 10 �Źܽ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
}

void dht_output_state(int status)//ͨ������status�����������߸ߵ͵�ƽ
{
	set_dht_gpio_output();//�������߳�ʼ�������ģʽ
	if(status == 0)//�жϲ���status�Ƿ�Ϊ0
		PCOut(10) = 0;//����������
	else
		PCOut(10) = 1;//����������
}

int dht_input_state(void)//��������ߵĸߵ͵�ƽ�Է���ֵ����ʽ����
{
	set_dht_gpio_input();//�������߳�ʼ��������ģʽ
	return PCIn(10);//ͨ��λ����PC10�ܽŵĵ�ƽ�ߵͷ���
}

void dht_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��
}

void get_dht_value(char *buf)
{
	char flag = 0;//flag����������ȡ�����ߵĸߵ͵�ƽ
	char time = 0;//time����������ʱ����ļ���
	char i = 0;//i����Ϊѭ������
	char tmp = 0;//������������
	
	dht_output_state(1);//����������
	dht_output_state(0);//����������
	delay_ms(20);				//��ʱ20����
	dht_output_state(1);//����������
	//while(dht_input_state());//����(������������)
	do//��ʱ����(�ȴ�����������)
	{
		flag = dht_input_state();//��ȡ�����ߵĸߵ͵�ƽ
		delay_us(2);//��ʱ2΢��
		time++;//����ֵ����
	}while(flag == 1 && time <= 20);//�ж�flag�Ƿ���1����timeС�ڵ���20
	if(time > 20)//���time����20,��ʱ
		return;
	while(!dht_input_state());//�ȴ�����������
	for(i = 0; i < 40; i++)//ѭ��40��,����40λ������
	{
		while(dht_input_state());//�ȴ�����������
		while(!dht_input_state());//�ȴ�����������
		delay_us(40);//��ʱ40΢��
		tmp <<= 1;
		if(dht_input_state())//�ж��������Ƿ�Ϊ�ߵ�ƽ
			tmp |= 1;//��λ�ȳ�
		if((i + 1) % 8 == 0)//i = 7 15 23 31 39(ÿ��ȡ8λ����ת��һ��)
		{
			buf[i / 8] = tmp;//��8λ������ת�浽buf��
			tmp = 0;//���tmp
		}
	}
	dht_output_state(1);//����������
}








