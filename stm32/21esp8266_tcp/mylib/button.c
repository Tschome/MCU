#include "button.h"
#include "bitband.h"

void button_init(void)//��ʼ���ĺ���(��ʼ�����������ӵ�GPIO�ܽ�)
{
	GPIO_InitTypeDef Button_Value;//������GPIO�̼��Ľṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOA��� �� GPIOC���ʱ��
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPU;//ѡ�������������ģʽ
	Button_Value.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;//ѡ���� 8 9 �Źܽ�
	Button_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz������ٶ�
	GPIO_Init(GPIOC, &Button_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPD;//ѡ�����������ģʽ
	Button_Value.GPIO_Pin = GPIO_Pin_0;//ѡ���� 0 �Źܽ�
	GPIO_Init(GPIOA, &Button_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�
}

int button_status(int nu)//���ݲ���nu�����Ӧ�Ĺ��ܰ����Ƿ񱻰���
{
	int ret = 0;//ret����������ȡGPIO�Ĵ����е�����
	
	switch(nu)
	{
		case 0 : ret = PCIn(9); break;//��PC9�ܽŵĵ�ƽ�ߵ�
		case 1 : ret = PCIn(8); break;//��PC8�ܽŵĵ�ƽ�ߵ�
		case 2 : ret = PAIn(0); ret = !ret; break;//��PA0�ܽŵĵ�ƽ�ߵ�
	}
	return !ret;//�Ѷ������������߼��ǵĲ����ٷ���
}










