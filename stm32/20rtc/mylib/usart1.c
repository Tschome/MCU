#include "usart1.h"
#include "stdio.h"

usart1_handler u1_h;//����ȫ�ֱ���(����ָ��)

//���ð�����ģʽ
#pragma import(__use_no_semihosting)

struct __FILE
{
	int a;
};

FILE __stdout;
FILE __stdin;

void _sys_exit(int x)
{
	
}

int fputc(int c, FILE *f)
{
	usart_1_send_byte(c);
	return c;
}

int fgetc(FILE *f)//ʹ����ѯ�ķ�ʽ
{
	return usart_1_recv_byte();
}

void usart_1_init(void)//��ʼ���ĺ���(��ʼ��GPIO�ܽźʹ��ڹ���)
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO��ʼ���Ľṹ�����ͱ���
	USART_InitTypeDef Usart_Value;//������USART��ʼ���Ľṹ�����ͱ���
	NVIC_InitTypeDef Nvic_Value;//������NVIC��ʼ���Ľṹ�����ͱ���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	//ͨ��APB2����ʹ��GPIOA���USART1��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF_PP;//ѡ��������ĸ���ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_9;//ѡ����9�Źܽ�
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz���������
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��PA9�ܽ�

	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//ѡ���˸�������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//ѡ����10�Źܽ�
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��PA10�ܽ�

	Usart_Value.USART_BaudRate = 115200;//����Ϊ115200�Ĳ�����
	Usart_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ѡ��ر�Ӳ������
	Usart_Value.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ѡ���˷��ͺͽ���ģʽ
	Usart_Value.USART_Parity = USART_Parity_No;//ѡ����û����żУ��
	Usart_Value.USART_StopBits = USART_StopBits_1;//ѡ����һ��ֹͣλ
	Usart_Value.USART_WordLength = USART_WordLength_8b;//ѡ����8������λ
	USART_Init(USART1, &Usart_Value);//�����������ó�ʼ��USART1
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���������ȼ��������ȼ�����ռ����
	Nvic_Value.NVIC_IRQChannel = USART1_IRQn;//ѡ����USART1���жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ѡ��ʹ�ܸ��ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//ѡ���������ȼ��ļ���Ϊ2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//ѡ���������ȼ��ļ���Ϊ2
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//ʹ����USART1�Ľ������ݴ����ж�
	
	USART_Cmd(USART1, ENABLE);//ʹ��USART1�Ĺ���
}

void usart_1_send_byte(u8 c)//����һ���ֽڵ�����
{
	USART_SendData(USART1, c);//���β�c�洢������ͨ��USART1���ڽ��з���
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	//�����ȵķ�ʽ�ȴ�USART1�ķ�������,���ͳɹ�
	USART_ClearFlag(USART1, USART_FLAG_TC);//���USART1�ķ������ݳɹ��ı�־״̬
}

void usart_1_send_data(char *buf)//�����ַ���
{
	while(*buf)
	{
		usart_1_send_byte(*buf);
		buf++;
	}
}

u8 usart_1_recv_byte(void)//����һ���ֽ�����
{
	u8 ret = 0;//ret������������USART1���յ�������
	
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	//�ж�USART1�Ƿ���յ�������
	{
		ret = USART_ReceiveData(USART1);//��USART1���յ������ݱ��浽ret������
		USART_ClearFlag(USART1, USART_FLAG_RXNE);//���USART1���յ����ݵı�־
	}
	
	return ret;//�ѽ��յ������ݷ���
}

void USART1_IRQHandler(void)//USART1���жϴ�����
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//�ж��Ƿ�����USART1�������ݴ������ж�
	{
		u1_h(USART_ReceiveData(USART1));//�Ѵ�USART1�ж�ȡ�������ݽ����ͻ������ݴ�����
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//���USART1�������ݵ��жϱ�־
	}
}

void set_usart1_handler(usart1_handler h)//���ûص�����
{
	u1_h = h;
}



