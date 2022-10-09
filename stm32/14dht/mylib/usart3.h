#ifndef __USART3_H
#define __USART3_H
/*
USART3_TX	PB10		�����ز�������ģʽ
USART3_RX	PB11	�����ز�������ģʽ(��������)
*/
#include "stm32f10x_conf.h"

typedef void (*usart3_handler)(u8);//�����˺���ָ������

extern void usart_3_init(void);//��ʼ���ĺ���(��ʼ��GPIO�ܽźʹ��ڹ���)

extern void usart_3_send_byte(u8 c);//����һ���ֽڵ�����

extern void usart_3_send_data(char *buf);//�����ַ���

extern u8 usart_3_recv_byte(void);//����һ���ֽ�����

extern void set_usart3_handler(usart3_handler h);//���ûص�����

#endif



