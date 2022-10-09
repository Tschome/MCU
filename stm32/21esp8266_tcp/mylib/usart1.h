#ifndef __USART1_H
#define __USART1_H
/*
USART1_TX		PA9
USART1_RX		PA10
��֪оƬ�Ĺܽ��Ƕ๦�ܸ����͵Ĺܽ�
����ģʽ ���ģʽ ����ģʽ ģ��ģʽ
���������ô��ڵĹܽ�ʱ��ѡ���õ�ģʽ
USART1_TX		����	����ģʽ
USART1_RX		����	���յ�����ģʽ
*/
#include "stm32f10x_conf.h"//������ͷ�ļ����е�����ͷ�ļ����Ѱ���

typedef void (*usart1_handler)(unsigned char);//ͨ��typedef������һ������ָ������

extern void usart_1_init(void);//��ʼ���ĺ���(��ʼ��GPIO�ܽźʹ��ڹ���)

extern void usart_1_send_byte(unsigned char c);//����һ���ֽڵ�����

extern void usart_1_send_data(char *buf);//����һ���ַ���������

extern unsigned char usart_1_recv_byte(void);//����һ���ֽ�����

extern void set_usart1_handler(usart1_handler h);//���ûص�����

#endif









