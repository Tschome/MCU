#include "led.h"

void led_init(void)//��ʼ��LED��
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��

	GPIOC_CRL |= ((3 << 4) | (3 << 8) | (3 << 12));
	//��PC1 2 3�ܽ�����Ϊ���ģʽ,������50MHz���������
	GPIOC_CRL &= ~((3 << 6) | (3 << 10) | (3 << 14));
	//��PC1 2 3�ܽ�����Ϊ��������ģʽ
	GPIOC_ODR &= ~((1 << 1) | (1 << 2) | (1 << 3));
	//��PC1 2 3�ܽ�����͵�ƽ
}

void led_on(int nu)//ͨ���β�nuѡ�������Ӧ��LED��
{
	switch(nu)
	{
		case 0 : GPIOC_ODR |= (1 << 1); break;
		case 1 : GPIOC_ODR |= (1 << 2); break;
		case 2 : GPIOC_ODR |= (1 << 3); break;
	}
}

void led_off(int nu)//ͨ���β�nuѡ�������Ӧ��LED��
{
	switch(nu)
	{
		case 0 : GPIOC_ODR &= ~(1 << 1); break;
		case 1 : GPIOC_ODR &= ~(1 << 2); break;
		case 2 : GPIOC_ODR &= ~(1 << 3); break;
	}
}





