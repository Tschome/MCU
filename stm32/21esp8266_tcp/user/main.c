#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"
#include "iwdg.h"
#include "usart1.h"
#include "stdio.h"
#include "dht.h"
#include "eeprom.h"
#include "sht.h"
#include "oled.h"
#include "ldt.h"
#include "adj_res.h"
#include "rtc.h"
#include "esp8266.h"
#include "string.h"

void h(char *buf, int len)
{
	if(strcmp(buf, "BUZZER_ON") == 0)
		buzzer_on();
	if(strcmp(buf, "BUZZER_OFF") == 0)
		buzzer_off();
}

int main(void)
{
	struct time_st oldtime = {2021, 4, 2, 5, 16, 35, 0};//���嵱ǰʱ��Ľṹ�����
	struct time_st newtime;	
	double sht_data[2] = {0};//�洢��SHT30�ж������¶Ⱥ�ʪ��
	char Sht_Temp[9] = {0};//��SHT30�õ����¶�ת�����ַ���
	char Sht_Hum[11] = {0};//��SHT30�õ���ʪ��ת�����ַ���
	char Dht_Data[5] = {0};//���ڴ洢��DHT11�������еõ�������
	int Dht_Value = 0;//��������DHT11��ʪ�Ⱥ��¶�
	int adj_res_value = 0;//���ڴ洢�߾��ȿɵ��������ֵ
	int i = 500;//i����Ϊѭ������
	char Date[13] = {0};//����ת�����ַ���������
	char Time[9] = {0};//����ת�����ַ�����ʱ��
	char buf[62] = {0};//������������ת���ɵ��ַ���
	/*YYYY/MM/DD W HH:MM:SS SHT30:XX.XX XX.XX DHT11:XX XX ADC:XXXX\r\n*/
	
	led_init();//��ʼ��LED��
	buzzer_init();//��ʼ��������
	button_init();//��ʼ������
	delay_init();//��ʼ����ʱ����
	eint_init();//��ʼ���ⲿ�ж�
	usart_1_init();//��ʼ��USART1
	dht_init();//��ʼ��DHT
	eeprom_init();//��ʼ��eeprom
	sht_init();//��ʼ��SHT30
	OLED_Init();//��ʼ��OLED
	ldt_init();//��ʼ�������
	adj_res_init();//��ʼ���߾��ȿɵ�����
	rtc_init(&oldtime);//��ʼ��RTC
	esp8266_init();//��ʼ��ESP8266
	
	sht_write_mode();//����SHT30�Ĳ���Ƶ��
	OLED_Clear();//����
	
	led_on(0);
	esp8266_link_wifi("iPhone 11", "123456123456");//����·��
	delay_ms(2000);//��ʱ2s
	led_off(0);
	
	led_on(1);
	esp8266_connect("172.20.10.4", "2222");//����TCP����
	delay_ms(2000);//��ʱ2s
	led_off(1);
	
	set_wifi_recv_handler(h);//���ûص�����
	
	while(1)
	{
		get_time(&newtime);//��ȡʱ��
		adj_res_value = get_adj_res_value();//��ȡADת���Ľ��
		get_dht_value(Dht_Data);//�ɼ�DHT11��ȡ������
		Dht_Value = Dht_Data[0];//��DHT11�ɼ�����ʪ��ת�浽Dht_Value��
		Dht_Value *= 100;
		Dht_Value += Dht_Data[2];//��DHT11�ɼ������¶�ת�浽Dht_Value��
		sht_write_read_cmd();//���òɼ�����
		sht_read_data(sht_data);//��ȡ����
		sprintf(Sht_Temp, " : %.2f", sht_data[0]);//��SHT30�õ����¶�ת�����ַ���
		sprintf(Sht_Hum, " : %.2f %%", sht_data[1]);//��SHT30�õ���ʪ��ת�����ַ���
		sprintf(Date, "%d-%02d-%02d %d", newtime.Y, newtime.M, newtime.D, newtime.W);//�ѻ�ȡ��������ת�����ַ���
		sprintf(Time, "%02d:%02d:%02d", newtime.h, newtime.m, newtime.s);//�ѻ�ȡ����ʱ��ת�����ַ���
		sprintf(buf, "%d/%02d/%02d %d %02d:%02d:%02d SHT30:%.2f %.2f DHT11:%d %d ADC:%04d\r\n", newtime.Y, newtime.M, newtime.D, newtime.W, newtime.h, newtime.m, newtime.s, sht_data[0], sht_data[1], Dht_Data[2], Dht_Data[0], adj_res_value);
		OLED_ShowString(0, 0, (u8 *)Sht_Temp, 12);//��OLED����ʾ�¶�
		OLED_ShowString(0, 2, (u8 *)Sht_Hum, 12);//��OLED����ʾʪ��
		OLED_ShowString(0, 4, (u8 *)Date, 12);//��OLED����ʾ����
		OLED_ShowString(0, 6, (u8 *)Time, 12);//��OLED����ʾʱ��
		while(i--)//ѭ����ʾ������ϵ�����
			digit_show_data(adj_res_value);//�Ѹ߾��ȿɵ�����ת������ֵ�����������ʾ
		i = 500;
		esp8266_send(buf, "62");
		//esp8266_send("Hello World", "11");
		led_on(0);
		delay_ms(500);
		led_off(0);
		delay_ms(500);
	}
}







