#include "button.h"

void button_init(void)//������ʼ���ĺ���
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOA���GPIOC���ʱ��
	
	GPIOA_CRL &= ~(15 << 0);//��PA0�ܽ�����Ϊ����ģʽ
	GPIOA_CRL |= (2 << 2);//��PA0�ܽ�����Ϊ����/��������ģʽ
	GPIOA_ODR &= ~(1 << 0);//Ĭ�ϰ�PA0�ܽ�����
	
	GPIOC_CRH &= ~((15 << 0) | (15 << 4));//��PC9 PC8�ܽ�����Ϊ����ģʽ
	GPIOC_CRH |= ((2 << 2) | (2 << 6));//��PC9 PC8 �ܽ�����Ϊ����/��������ģʽ
	GPIOC_ODR |= ((1 << 8) | (1 << 9));//Ĭ�ϰ�PC9 PC8�ܽ�����
}

int button_status(int nu)//ͨ��nu�������Ӧ������״̬
{
	//��Ҫ��ȡGPIOC_IDR�Ĵ����ĵ�9λ
	int ret = 0;
	
	switch(nu)
	{
		case 0 : ret = (GPIOC_IDR >> 9) & 0x01; break;//��ȡPC9�ܽŵĵ�ƽ�ߵ�
		case 1 : ret = (GPIOC_IDR >> 8) & 0x01; break;//��ȡPC8�ܽŵĵ�ƽ�ߵ�
		case 2 : ret = GPIOA_IDR & 0x01; ret = !ret; break;//��ȡPA0�ܽŵĵ�ƽ�ߵ�
	}
	
	return !ret;
}






