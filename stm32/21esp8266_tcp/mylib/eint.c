#include "eint.h"

eint_handler e_h0, e_h1, e_h2;

void eint_init(void)//��ʼ���ĺ���(���ڳ�ʼ��GPIO�ܽź�NVIC��EXTI)
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO�̼��Ľṹ�����
	NVIC_InitTypeDef Nvic_Value;//������NVIC�̼��Ľṹ�����
	EXTI_InitTypeDef Exti_Value;//������EXTI�̼��Ľṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	//ͨ��APB2����ʹ��GPIOA���GPIOC���AFIO��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPU;//ѡ�����������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;//ѡ���� 9 8 �Źܽ�
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz����ٶ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPD;//ѡ�����������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//ѡ�� 0 �Źܽ�
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	//Ϊ�ⲿ�ж�9ѡ����PC9�ܽŴ��� Ϊ�ⲿ�ж�8ѡ����PC8�ܽŴ��� Ϊ�ⲿ�ж�0ѡ����PA0����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���������ȼ��������ȼ�����ռ����
	Nvic_Value.NVIC_IRQChannel = EXTI9_5_IRQn;//ѡ�����жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ʹ�ܸ��ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//���������ȼ��ļ���Ϊ2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//���������ȼ��ļ���Ϊ2
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC�жϿ�����
	
	Nvic_Value.NVIC_IRQChannel = EXTI0_IRQn;//ѡ�����жϺ�
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC�жϿ�����
	
	Exti_Value.EXTI_Line = EXTI_Line8 | EXTI_Line9;//ѡ���ⲿ�жϺ�9 8
	Exti_Value.EXTI_LineCmd = ENABLE;//ʹ�ܸ��ⲿ�ж�
	Exti_Value.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ���ж�ģʽ
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Falling;//ѡ���½��ش���
	EXTI_Init(&Exti_Value);//�������������ó�ʼ��EXTI
	
	Exti_Value.EXTI_Line = EXTI_Line0;//ѡ���ⲿ�жϺ�0
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Rising;//ѡ�������ش���
	EXTI_Init(&Exti_Value);//�������������ó�ʼ��EXTI
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET)//�ж��Ƿ�����EXTI9�������ж�
	{
		e_h0();//���ð��°�������֮��ͻ���Ҫ���Ĵ�����
		EXTI_ClearITPendingBit(EXTI_Line9);//����ⲿ�ж�9���жϱ�־
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)//�ж��Ƿ�����EXTI8�������ж�
	{
		e_h1();//���ð��°�������֮��ͻ���Ҫ���Ĵ�����
		EXTI_ClearITPendingBit(EXTI_Line8);//����ⲿ�ж�8���жϱ�־
	}
}

void EXTI0_IRQHandler(void)
{
	e_h2();//���ð��°�������֮��ͻ���Ҫ���Ĵ�����
	EXTI_ClearITPendingBit(EXTI_Line0);//����ⲿ�ж�0���жϱ�־
}

void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2)//���ûص�����
{
	e_h0 = h0;//���β�h0������ĺ�����ַת�浽ȫ�ֱ���e_h0��
	e_h1 = h1;
	e_h2 = h2;
}








