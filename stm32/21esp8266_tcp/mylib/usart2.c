#include "usart2.h"
#include "esp8266.h"

usart2_handler u2_h;

void usart_2_init(void)//��ʼ���ĺ���(��ʼ��GPIO�ܽźʹ��ڹ���)
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO�̼��Ľṹ�����
	USART_InitTypeDef Usart_Value;//������USART�̼��Ľṹ�����
	NVIC_InitTypeDef Nvic_Value;//������NVIC�̼��Ľṹ�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	//ͨ��APB2����ʹ��GPIOA���ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	//ͨ��PAB1����ʹ��USART2��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF_PP;//ѡ��������ĸ���ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_2;//ѡ���� 2 �Źܽ�(PA2�Ƿ��͹ܽ�)
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ����50MHz������ٶ�
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�

	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//ѡ���˸��յ�����ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_3;//ѡ���� 3 �Źܽ�(PA3�ǽ��չܽ�)
	GPIO_Init(GPIOA, &Gpio_Value);//�����������ó�ʼ��GPIOA��Ĺܽ�
	
	Usart_Value.USART_BaudRate = 115200;//ѡ����115200�Ĳ�����
	Usart_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//ѡ���˹ر�Ӳ������
	Usart_Value.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//ѡ���˷���ģʽ�ͽ���ģʽ
	Usart_Value.USART_Parity = USART_Parity_No;//ѡ����û����żУ��
	Usart_Value.USART_StopBits = USART_StopBits_1;//ѡ����1��ֹͣλ
	Usart_Value.USART_WordLength = USART_WordLength_8b;//ѡ����8������λ
	USART_Init(USART2, &Usart_Value);//�����������ó�ʼ��USART2
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���������ȼ��������ȼ�����ռ����
	Nvic_Value.NVIC_IRQChannel = USART2_IRQn;//ѡ����USART2�ж�Դ���жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ѡ��ʹ�ܸ��ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//ѡ���������ȼ��ļ���Ϊ2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//ѡ���������ȼ��ļ���Ϊ2
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC�жϿ�����
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ����USART2�Ľ������ݴ����ж�
	
	USART_Cmd(USART2, ENABLE);//ʹ��USART2�Ĺ���
}

void usart_2_send_byte(unsigned char c)//����һ���ֽڵ�����
{
	USART_SendData(USART2, c);//ͨ��USART2��c������������ݷ��ͳ�ȥ
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);//����USART2�ķ��������Ƿ��ͳɹ���(��ʱ����)
	USART_ClearFlag(USART2, USART_FLAG_TC);//���USART2�ķ��ͳɹ��ı�־״̬
}

void usart_2_send_data(char *buf)//����һ���ַ���������
{
	while(*buf)//ͨ��whileѭ�����ַ����е���Ч�ַ�����һ��
	{
		usart_2_send_byte(*buf);//����Ч���ַ����з���
		buf++;//��bufָ��ָ����һ���ַ�
	}
}

unsigned char usart_2_recv_byte(void)//����һ���ֽ�����
{
	unsigned char ret = 0;//ret������������USART1�ӵ�������
	
	if(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == SET)//�ж�USART2�Ƿ���յ�������
	{
		ret = USART_ReceiveData(USART2);//��USART2���յ������ݱ��浽ret������
		USART_ClearFlag(USART2, USART_FLAG_RXNE);//���USART2���յ����ݵı�־
	}
	
	return ret;
}

void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)//�ж��Ƿ�����USART2�Ľ������ݴ������ж�
	{
		dataHandler(USART_ReceiveData(USART2));//����USART1�����ݣ����ѽ��յ��������Դ��ε���ʽ���ݸ��ص�����
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);//���USART1�������ݵ��жϱ�־
	}
}

void set_usart2_handler(usart2_handler h)//���ûص�����
{
	u2_h = h;//���β�h���洢�ĺ�����ַ��浽ȫ�ֱ���u1_h��
}













