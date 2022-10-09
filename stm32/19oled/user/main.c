#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"
#include "iwdg.h"
#include "usart1.h"
#include "stdio.h"
#include "dht.h"
#include "ldt.h"
#include "adj_res.h"
#include "eeprom.h"
#include "sht.h"
#include "oled.h"

int main(void)
{
	char dht_buf[5] = {0};//���ڴ洢DHT11����
	double sht_buf[2] = {0};//���ڴ洢SHT30������
	int adj_value = 0;//���ڴ洢ADת���Ľ��
	u8 old = 79, ww = 0;//���ڴ洢EEPROM������
	int i = 500;//���������صı���
	
	led_init();//����LED�Ƴ�ʼ���ĺ���
	buzzer_init();//���÷�������ʼ���ĺ���
	button_init();//���ð�����ʼ���ĺ���
	delay_init();//������ʱ��ʼ���ĺ���
	eint_init();//�����ⲿ�жϳ�ʼ���ĺ���
	usart_1_init();//����USART1��ʼ���ĺ���
	dht_init();//����DHT11��ʼ���ĺ���
	ldt_init();//����LDT��ʼ���ĺ���
	adj_res_init();//���ø߾��ȿɵ�����ĳ�ʼ������
	eeprom_init();//����EEPROM��ʼ���ĺ���
	sht_init();//����SHT30��ʼ���ĺ���
	OLED_Init();//����OLED��ʼ���ĺ���
	
	OLED_Clear();//����
	//OLED_ShowChar(0, 0, 'A', 16);
	//OLED_ShowNum(0, 0, 9527, 4, 16);
	OLED_ShowString(0, 0, (u8 *)"Hello World!", 16);
	
	eeprom_byte_write(0xA0, 0x10, old);//���ֽ���д
	sht_write_mode();//���ò���Ƶ��
	
	while(1)
	{
		get_dht_value(dht_buf);
		adj_value = get_adj_res_value();
		ww = eeprom_rand_addr_read(0xA0, 0x10);
		sht_write_read_cmd();//���Ͷ�ȡSHT30���ݵ�ָ��
		sht_read_data(sht_buf);//��ȡSHT30������
		printf("Dht:%d/%d Adj:%d Eeprom:%d Sht:%.2f/%.2f\n", dht_buf[0], dht_buf[2], adj_value, ww, sht_buf[0], sht_buf[1]);
		while(i--)
			digit_show_data(adj_value);
		i = 500;
		led_on(0);
		delay_ms(500);
		led_off(0);
		delay_ms(500);
	}
}










