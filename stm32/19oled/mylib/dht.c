#include "dht.h"
#include "bitband.h"
#include "delay.h"

void set_dht_output(void)//��PC10�ܽų�ʼ�������ģʽ
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ������������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//ѡ����10�Źܽ�
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz���������
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��PC10�ܽ�
}

void set_dht_input(void)//��PC10�ܽų�ʼ��������ģʽ
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//ѡ���˸�������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//ѡ����10�Źܽ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��PC10�ܽ�
}

void dht_output_status(int state)
{
	set_dht_output();//��PC10�ܽ�����Ϊ���ģʽ
	PCOut(10) = state;//�ѹܽ�����ߵ͵�ƽ
}

int dht_input_status(void)
{
	set_dht_input();//��PC10�ܽ�����Ϊ����ģʽ
	return PCIn(10);
}

void dht_init(void)//��ʼ��DHT�ĺ���
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��
}

void get_dht_value(char *buf)//��ȡDHT11������������
{
	u8 flag = 0;
	u8 time = 0;
	u8 data = 0;
	u8 i = 0;
	
	dht_output_status(1);//������������
	dht_output_status(0);//������������
	delay_ms(20);//��ʱ20����
	dht_output_status(1);//������������
	//while(dht_input_status());//�����ȵķ�ʽ�ȴ������߱�����
	do
	{
		flag = dht_input_status();//��ȡ�����ߵĵ�ƽ״̬
		time++;//��������
		delay_us(2);//��ʱ2us
	}while(flag == 1 && time <= 20);//�жϳ�ʱ����
	if(time > 20)//�ж��Ƿ�ʱ
		return ;//��������
	while(!dht_input_status());//�ȴ������߱�����
	for(i = 0; i < 40; i++)//ѭ��40�ζ�ȡ����
	{
		while(dht_input_status());//�ȴ������߱�����
		while(!dht_input_status());//�ȴ������߱�����
		delay_us(40);//�ֶ���ʱ40us
		data <<= 1;//��data�����е����ݶ�����һλ
		if(dht_input_status() == 1)//�жϾ�����ʱ���������Ƿ��Ǹߵ�ƽ
			data |= 1;//�Ը�λ�ȳ��ķ�ʽ��ȡ����
		if((i + 1) % 8 == 0)//���i = 7 15 23 31 39
		{
			buf[i / 8] = data;//��������浽buf�ռ���
			data = 0;//�ѱ����ռ����
		}
	}
	dht_output_status(1);//������������
}






