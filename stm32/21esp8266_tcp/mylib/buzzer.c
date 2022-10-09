#include "buzzer.h"
#include "bitband.h"

void buzzer_init(void)//��ʼ���ĺ���(��ʼ�������ӵ�GPIO�ܽ�)
{
	GPIO_InitTypeDef Buzzer_Value;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ʱ��
	
	Buzzer_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ����������ģʽ
	Buzzer_Value.GPIO_Pin = GPIO_Pin_7;//ѡ���� 7 �Źܽ�
	Buzzer_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz������ٶ�
	GPIO_Init(GPIOC, &Buzzer_Value);//�����������Ƴ�ʼ��GPIOC��Ĺܽ�
	
	PCOut(7) = 0;//��PC7�ܽ�����
}

void buzzer_on(void)//ʹ��������ĺ���
{
	PCOut(7) = 1;//��PC7�ܽ�����
}

void buzzer_off(void)//ʹ����������ĺ���
{
	PCOut(7) = 0;//��PC7�ܽ�����
}







