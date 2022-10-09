#ifndef __USART1_H
#define __USART1_H
/*
USART1_TX	PA9		�����ز�������ģʽ
USART1_RX	PA10	�����ز�������ģʽ(��������)
*/
#include "stm32f10x_conf.h"

typedef void (*usart1_handler)(u8);//�����˺���ָ������

extern void usart_1_init(void);//��ʼ���ĺ���(��ʼ��GPIO�ܽźʹ��ڹ���)

extern void usart_1_send_byte(u8 c);//����һ���ֽڵ�����

extern u8 usart_1_recv_byte(void);//����һ���ֽ�����

extern void set_usart1_handler(usart1_handler h);//���ûص�����

#endif



