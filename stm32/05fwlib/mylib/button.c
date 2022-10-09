#include "button.h"

void button_init(void)//������ʼ���ĺ���
{
	GPIO_InitTypeDef Button_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOA���GPIOC���ʱ��
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPU;//ѡ�������������ģʽ
	Button_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;//ѡ����9 8�Źܽ�
	GPIO_Init(GPIOC, &Button_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPD;//ѡ�������������ģʽ
	Button_Value.GPIO_Pin = GPIO_Pin_0;//ѡ����0�Źܽ�
	GPIO_Init(GPIOA, &Button_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�
}

int button_status(int nu)//ͨ��nu�������Ӧ������״̬
{
	int ret = 0;//���ڶ�ȡ�ܽŵĵ�ƽ�ߵ�
	
	switch(nu)
	{
		case 0 :ret = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9); break;//��ȡPC9�ܽŵĵ�ƽ�ߵ�
		case 1 :ret = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8); break;//��ȡPC8�ܽŵĵ�ƽ�ߵ�
		case 2 :ret = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); ret = !ret; break;//��ȡPA0�ܽŵĵ�ƽ�ߵ�
	}
	
	return !ret;
}






