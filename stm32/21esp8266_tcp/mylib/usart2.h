#ifndef __USART2_H
#define __USART2_H
/*
USART2_TX		PA2
USART2_RX		PA3
��֪оƬ�Ĺܽ��Ƕ๦�ܸ����͵Ĺܽ�
����ģʽ ���ģʽ ����ģʽ ģ��ģʽ
���������ô��ڵĹܽ�ʱ��ѡ���õ�ģʽ
USART2_TX		����	����ģʽ
USART2_RX		����	���յ�����ģʽ
*/
#include "stm32f10x_conf.h"//������ͷ�ļ����е�����ͷ�ļ����Ѱ���

typedef void (*usart2_handler)(unsigned char);//ͨ��typedef������һ������ָ������

extern void usart_2_init(void);//��ʼ���ĺ���(��ʼ��GPIO�ܽźʹ��ڹ���)

extern void usart_2_send_byte(unsigned char c);//����һ���ֽڵ�����

extern void usart_2_send_data(char *buf);//����һ���ַ���������

extern unsigned char usart_2_recv_byte(void);//����һ���ֽ�����

extern void set_usart2_handler(usart2_handler h);//���ûص�����

#endif






