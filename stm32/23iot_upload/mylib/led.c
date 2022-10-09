#include "led.h"
#include "bitband.h"

void led_init(void)
{
	GPIO_InitTypeDef Led_Value;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/*ͨ��APB2����ʹ��GPIOC���ʱ��*/
	
	Led_Value.GPIO_Mode = GPIO_Mode_Out_PP;//ѡ����������ģʽ
	Led_Value.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//ѡ��1�Źܽ�2�Źܽ�3�Źܽ�
	Led_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz������ٶ�
	
	GPIO_Init(GPIOC, &Led_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	PCOut(1) = 0;
	PCOut(2) = 0;
	PCOut(3) = 0;
	//��GPIOC�����Ӧ�ܽ�����
}

void led_on(int nu)
{
	switch(nu)
	{
		case 0 : PCOut(1) = 1; break;
		case 1 : PCOut(2) = 1; break;
		case 2 : PCOut(3) = 1; break;
	}	
}

void led_off(int nu)
{
	switch(nu)
	{
		case 0 : PCOut(1) = 0; break;
		case 1 : PCOut(2) = 0; break;
		case 2 : PCOut(3) = 0; break;
	}
}



