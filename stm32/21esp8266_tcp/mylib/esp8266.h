#ifndef __ESP8266_H
#define __ESP8266_H
/*
ESP8266ģ����WIFI����ͨѶģ��,��ģ���Ǵ��ڽӿ�
���ӵ������ǿ������ϵ�USART2
*/
#include "stm32f10x_conf.h"//������ͷ�ļ����е�����ͷ�ļ����Ѱ���

typedef void (*wifi_recv_handler)(char *buf, int len);//ͨ��typedef���庯��ָ������

extern void set_wifi_recv_handler(wifi_recv_handler h);//����wifi���յ����ݵĻص�����
extern void esp8266_init(void);//��ʼ���ĺ���(��ʼ������)
extern void esp8266_link_wifi(char *ssid, char *passwd);//����·��(��Ҫ·�ɵ����ƺ�·�ɵ�����)
extern void esp8266_connect(char *ip, char *port);//����TCP server
extern void esp8266_disconnect(void);//�Ͽ�TCP����
extern void esp8266_send(char *msg, char *len);//��������
extern void dataHandler(unsigned char c);//������յ�������

#endif









