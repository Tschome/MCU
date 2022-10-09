#ifndef __USART1_H
#define __USART1_H
/*
USART1_TX	PA9		主动地操作复用模式
USART1_RX	PA10	被动地操作输入模式(浮空输入)
*/
#include "stm32f10x_conf.h"

typedef void (*usart1_handler)(u8);//定义了函数指针类型

extern void usart_1_init(void);//初始化的函数(初始化GPIO管脚和串口功能)

extern void usart_1_send_byte(u8 c);//发送一个字节的数据

extern u8 usart_1_recv_byte(void);//接收一个字节数据

extern void set_usart1_handler(usart1_handler h);//设置回调函数

#endif



