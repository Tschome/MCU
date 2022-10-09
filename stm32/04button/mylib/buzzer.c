#include "buzzer.h"

void buzzer_init(void)//�������ĳ�ʼ��
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��
	
	GPIOC_CRL |= (3 << 28);//��PC7�ܽ�����Ϊ50MHz�����ģʽ
	GPIOC_CRL &= ~((unsigned int )3 << 30);//��PC7�ܽ�����Ϊ�������
	GPIOC_ODR &= ~(1 << 7);//��PC7�ܽ�����͵�ƽ
}

void buzzer_on(void)//��������
{
	GPIOC_ODR |= (1 << 7);//��PC7�ܽ�����ߵ�ƽ
}

void buzzer_off(void)//����������
{
	GPIOC_ODR &= ~(1 << 7);//��PC7�ܽ�����͵�ƽ
}


