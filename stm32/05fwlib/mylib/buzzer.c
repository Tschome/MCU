#include "buzzer.h"

void buzzer_init(void)//�������ĳ�ʼ��
{
	GPIO_InitTypeDef Buzzer_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��
	
	Buzzer_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ������������ģʽ
	Buzzer_Value.GPIO_Pin = GPIO_Pin_7;//ѡ����7�Źܽ�
	Buzzer_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz���������
	GPIO_Init(GPIOC, &Buzzer_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);//��PC7�ܽ�����͵�ƽ
}

void buzzer_on(void)//��������
{
	GPIO_SetBits(GPIOC, GPIO_Pin_7);//��PC7�ܽ�����͵�ƽ
}

void buzzer_off(void)//����������
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);//��PC7�ܽ�����͵�ƽ
}


