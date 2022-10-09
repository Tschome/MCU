#include "eint.h"

eint_handler eh0, eh1, eh2;//������ȫ�ֱ���(����ָ��)

void eint_init(void)//��ʼ���ĺ���(���ڳ�ʼ��GPIO��EXTI�Լ�NVIC)
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	NVIC_InitTypeDef Nvic_Value;//������NVIC��ʼ���Ľṹ�����ͱ���
	EXTI_InitTypeDef Exti_Value;//������EXTI��ʼ���Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���GPIOA���ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//ͨ��APB2����ʹ��AFIO��ʱ��
	//(������Ҫͨ��AFIOΪ�ⲿ�ж�ѡ�񴥷���GPIO�ܽ�)
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPU;//ѡ�������������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;//ѡ����9 8 �Źܽ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPD;//ѡ�������������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//ѡ����0�Źܽ�
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	//ΪEXTI9ѡ����PC9�ܽŴ��� ΪEXTI8ѡ����PC8�ܽŴ���
	//ΪEXTI0ѡ����PA0�ܽŴ���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���������ȼ��������ȼ�����ռ����
	Nvic_Value.NVIC_IRQChannel = EXTI9_5_IRQn;//ѡ�����жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ѡ��ʹ�ܸ��ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//���������ȼ��ļ���Ϊ2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//���������ȼ��ļ���Ϊ2
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC

	Nvic_Value.NVIC_IRQChannel = EXTI0_IRQn;//ѡ�����жϺ�
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC
	
	Exti_Value.EXTI_Line = EXTI_Line9 | EXTI_Line8;//ѡ�����ⲿ�жϺ�9 8
	Exti_Value.EXTI_LineCmd = ENABLE;//ѡ��ʹ�ܸ��ⲿ�ж�
	Exti_Value.EXTI_Mode = EXTI_Mode_Interrupt;//ѡ�����жϵ�ģʽ
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Falling;//ѡ�����½��ش���
	EXTI_Init(&Exti_Value);//�����������ó�ʼ��EXTI9 EXTI8
	
	Exti_Value.EXTI_Line = EXTI_Line0;//ѡ����EXTI0�ⲿ�жϺ�
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Rising;//ѡ���������ش���
	EXTI_Init(&Exti_Value);//�����������ó�ʼ��EXTI0	
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET)//�ж��Ƿ�����EXTI9�������ж�
	{
		eh0();//����PC9��������֮��ͻ���Ҫ���Ĵ���
		EXTI_ClearITPendingBit(EXTI_Line9);//���EXTI9���жϱ�־λ
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)//�ж��Ƿ�����EXTI9�������ж�
	{
		eh1();//����PC8��������֮��ͻ���Ҫ���Ĵ���
		EXTI_ClearITPendingBit(EXTI_Line8);//���EXTI9���жϱ�־λ
	}
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)//�ж��Ƿ�����EXTI9�������ж�
	{
		eh2();//����PC9��������֮��ͻ���Ҫ���Ĵ���
		EXTI_ClearITPendingBit(EXTI_Line0);//���EXTI9���жϱ�־λ
	}
}

void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2)//���ûص�����
{
	eh0 = h0;//���β�ָ�뱣��ĵ�ַ��浽ȫ��ָ����
	eh1 = h1;
	eh2 = h2;
}





