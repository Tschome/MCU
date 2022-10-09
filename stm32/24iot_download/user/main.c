#include "led.h"
#include "buzzer.h"
#include "delay.h"
#include "esp8266.h"
#include "iot.h"
#include "string.h"

#define API_KEY "eyJhbGciOiJIUzI1NiIsImV4cCI6MTkzMzA1Nzc0OSwiaWF0IjoxNjE3Njk3NzQ5fQ.eyJpZCI6MTcyMn0._ZWcye_QMze7-IW84Bo2aCanBRzHY3uapn0x406ftHU:"
//API_KEY需要修改

void recv_handler(char *buf, int len)
{
	char *v = NULL;
	
	v = strstr(buf, "true");
	if(v != NULL)
		buzzer_on();
	else
		buzzer_off();
}

int main(void)
{	
	led_init();
	buzzer_init();
	delay_init();
	esp8266_init();
	
	led_on(0);
	esp8266_link_wifi("UPIOT", "easthome");//需改
	delay_ms(500);
	led_off(0);

	set_wifi_recv_handler(recv_handler);
	
	while(1)
	{
		download_sensor_status("119.29.98.16", "1962", "5444", API_KEY);
		/*
		IP地址不需要修改
		1962	设备ID需要修改
		5444	传感器ID需要修改
		*/
		led_on(0);
		delay_ms(1000);
		led_off(0);
	}
}










