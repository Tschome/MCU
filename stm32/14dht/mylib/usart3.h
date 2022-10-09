#ifndef __USART3_H
#define __USART3_H
/*
USART3_TX	PB10		主动地操作复用模式
USART3_RX	PB11	被动地操作输入模式(浮空输入)
*/
#include "stm32f10x_conf.h"

typedef void (*usart3_handler)(u8);//定义了函数指针类型

extern void usart_3_init(void);//初始化的函数(初始化GPIO管脚和串口功能)

extern void usart_3_send_byte(u8 c);//发送一个字节的数据

extern void usart_3_send_data(char *buf);//发送字符串

extern u8 usart_3_recv_byte(void);//接收一个字节数据

extern void set_usart3_handler(usart3_handler h);//设置回调函数

#endif



