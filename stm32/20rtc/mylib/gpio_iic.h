#ifndef __GPIO_IIC_H
#define __GPIO_IIC_H

//��GPIO�ķ�ʽ��ģ��IICЭ��

#include "stm32f10x_conf.h"

typedef unsigned char u8;

void IIC_Init(void);								//��ʼ��IICʹ�õ�GPIO				 
void IIC_Start(void);								//������ʼ�ź�
void IIC_Stop(void);								//���������ź�
void IIC_Send_Byte(u8 txd);					//����IIC���߷�������(һλһλ�ķ���)
u8 IIC_Recv_Byte(unsigned char ack);//����IIC���߽�������
u8 IIC_Wait_Ack(void);							//�ȴ�ACK
void IIC_Ack(void);									//����ACK
void IIC_NAck(void);								//������ACK

#endif
















