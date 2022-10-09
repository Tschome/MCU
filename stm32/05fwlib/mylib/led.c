#include "led.h"

void led_init(void)//��ʼ��LED��
{
	GPIO_InitTypeDef Led_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��

	Led_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ������������ģʽ
	Led_Value.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//ѡ����1 2 3�Źܽ�
	Led_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz���������
	GPIO_Init(GPIOC, &Led_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�

	GPIO_ResetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	//��PC1 PC2 PC3�ܽ�����͵�ƽ
}

void led_on(int nu)//ͨ���β�nuѡ�������Ӧ��LED��
{
	switch(nu)
	{
		case 0 : GPIO_SetBits(GPIOC, GPIO_Pin_1); break;//��PC1�ܽ�����ߵ�ƽ
		case 1 : GPIO_SetBits(GPIOC, GPIO_Pin_2); break;//��PC2�ܽ�����ߵ�ƽ
		case 2 : GPIO_SetBits(GPIOC, GPIO_Pin_3); break;//��PC3�ܽ�����ߵ�ƽ
	}
}

void led_off(int nu)//ͨ���β�nuѡ�������Ӧ��LED��
{
	switch(nu)
	{
		case 0 : GPIO_ResetBits(GPIOC, GPIO_Pin_1); break;//��PC1�ܽ�����͵�ƽ
		case 1 : GPIO_ResetBits(GPIOC, GPIO_Pin_2); break;//��PC2�ܽ�����͵�ƽ
		case 2 : GPIO_ResetBits(GPIOC, GPIO_Pin_3); break;//��PC3�ܽ�����͵�ƽ
	}
}





