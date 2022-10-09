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
	struct time_st oldtime = {2021, 4, 2, 5, 16, 35, 0};//定义当前时间的结构体变量
	struct time_st newtime;	
	double sht_data[2] = {0};//存储从SHT30中读出的温度和湿度
	char Sht_Temp[9] = {0};//把SHT30得到的温度转换成字符串
	char Sht_Hum[11] = {0};//把SHT30得到的湿度转换成字符串
	char Dht_Data[5] = {0};//用于存储从DHT11传感器中得到的数据
	int Dht_Value = 0;//用于整合DHT11的湿度和温度
	int adj_res_value = 0;//用于存储高精度可调电阻的数值
	int i = 500;//i变量为循环变量
	char Date[13] = {0};//保存转换成字符串的日期
	char Time[9] = {0};//保存转换成字符串的时间
	char buf[62] = {0};//保存所有数据转换成的字符串
	/*YYYY/MM/DD W HH:MM:SS SHT30:XX.XX XX.XX DHT11:XX XX ADC:XXXX\r\n*/
	
	led_init();//初始化LED灯
	buzzer_init();//初始化蜂鸣器
	button_init();//初始化按键
	delay_init();//初始化延时函数
	eint_init();//初始化外部中断
	usart_1_init();//初始化USART1
	dht_init();//初始化DHT
	eeprom_init();//初始化eeprom
	sht_init();//初始化SHT30
	OLED_Init();//初始化OLED
	ldt_init();//初始化数码管
	adj_res_init();//初始化高精度可调电阻
	rtc_init(&oldtime);//初始化RTC
	esp8266_init();//初始化ESP8266
	
	sht_write_mode();//配置SHT30的采样频率
	OLED_Clear();//清屏
	
	led_on(0);
	esp8266_link_wifi("iPhone 11", "123456123456");//连接路由
	delay_ms(2000);//延时2s
	led_off(0);
	
	led_on(1);
	esp8266_connect("172.20.10.4", "2222");//建立TCP连接
	delay_ms(2000);//延时2s
	led_off(1);
	
	set_wifi_recv_handler(h);//设置回调函数
	
	while(1)
	{
		get_time(&newtime);//获取时间
		adj_res_value = get_adj_res_value();//获取AD转换的结果
		get_dht_value(Dht_Data);//采集DHT11获取的数据
		Dht_Value = Dht_Data[0];//把DHT11采集到的湿度转存到Dht_Value中
		Dht_Value *= 100;
		Dht_Value += Dht_Data[2];//把DHT11采集到的温度转存到Dht_Value中
		sht_write_read_cmd();//配置采集数据
		sht_read_data(sht_data);//获取数据
		sprintf(Sht_Temp, " : %.2f", sht_data[0]);//把SHT30得到的温度转换成字符串
		sprintf(Sht_Hum, " : %.2f %%", sht_data[1]);//把SHT30得到的湿度转换成字符串
		sprintf(Date, "%d-%02d-%02d %d", newtime.Y, newtime.M, newtime.D, newtime.W);//把获取到的日期转换成字符串
		sprintf(Time, "%02d:%02d:%02d", newtime.h, newtime.m, newtime.s);//把获取到的时间转换成字符串
		sprintf(buf, "%d/%02d/%02d %d %02d:%02d:%02d SHT30:%.2f %.2f DHT11:%d %d ADC:%04d\r\n", newtime.Y, newtime.M, newtime.D, newtime.W, newtime.h, newtime.m, newtime.s, sht_data[0], sht_data[1], Dht_Data[2], Dht_Data[0], adj_res_value);
		OLED_ShowString(0, 0, (u8 *)Sht_Temp, 12);//在OLED中显示温度
		OLED_ShowString(0, 2, (u8 *)Sht_Hum, 12);//在OLED中显示湿度
		OLED_ShowString(0, 4, (u8 *)Date, 12);//在OLED中显示日期
		OLED_ShowString(0, 6, (u8 *)Time, 12);//在OLED中显示时间
		while(i--)//循环显示数码管上的数据
			digit_show_data(adj_res_value);//把高精度可调电阻转换的数值交给数码管显示
		i = 500;
		esp8266_send(buf, "62");
		//esp8266_send("Hello World", "11");
		led_on(0);
		delay_ms(500);
		led_off(0);
		delay_ms(500);
	}
}







