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
	char dht_buf[5] = {0};//用于存储DHT11数据
	double sht_buf[2] = {0};//用于存储SHT30的数据
	int adj_value = 0;//用于存储AD转换的结果
	u8 old = 79, ww = 0;//用于存储EEPROM的数据
	int i = 500;//和数码管相关的变量
	
	led_init();//调用LED灯初始化的函数
	buzzer_init();//调用蜂鸣器初始化的函数
	button_init();//调用按键初始化的函数
	delay_init();//调用延时初始化的函数
	eint_init();//调用外部中断初始化的函数
	usart_1_init();//调用USART1初始化的函数
	dht_init();//调用DHT11初始化的函数
	ldt_init();//调用LDT初始化的函数
	adj_res_init();//调用高精度可调电阻的初始化函数
	eeprom_init();//调用EEPROM初始化的函数
	sht_init();//调用SHT30初始化的函数
	OLED_Init();//调用OLED初始化的函数
	
	OLED_Clear();//清屏
	//OLED_ShowChar(0, 0, 'A', 16);
	//OLED_ShowNum(0, 0, 9527, 4, 16);
	OLED_ShowString(0, 0, (u8 *)"Hello World!", 16);
	
	eeprom_byte_write(0xA0, 0x10, old);//按字节来写
	sht_write_mode();//配置采样频率
	
	while(1)
	{
		get_dht_value(dht_buf);
		adj_value = get_adj_res_value();
		ww = eeprom_rand_addr_read(0xA0, 0x10);
		sht_write_read_cmd();//发送读取SHT30数据的指令
		sht_read_data(sht_buf);//读取SHT30的数据
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










