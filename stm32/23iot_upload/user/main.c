#include "led.h"
#include "buzzer.h"
#include "delay.h"
#include "esp8266.h"
#include "iot.h"
#include "string.h"

#define SIZE 2
#define API_KEY "eyJpYXQiOjE2MTU2MDQzODcsImFsZyI6IkhTMjU2IiwiZXhwIjoxOTMwOTY0Mzg3fQ.eyJpZCI6MTY4N30.7Gw6G8d16GQl0wX467Gq5YK8VL_5ffe4kTNRD7uHRTY:"
//API_KEY��Ҫ�޸ĳ��Լ��˺�(����ð��)

int main(void)
{
	int sensor_id_arrary[SIZE] = {5333, 5332};//��Ҫ�޸ĳ��Լ��Ĵ�������ID��
	double sensor_data_arrary[SIZE] = {22, 33};
	
	led_init();
	buzzer_init();
	delay_init();
	esp8266_init();
	
	led_on(0);
	esp8266_link_wifi("UPIOT", "easthome");//��Ҫ�޸ĳ��Լ����ֻ��ȵ�
	delay_ms(500);
	led_off(0);
	
	while(1)
	{
		sensor_data_arrary[0]++;
		sensor_data_arrary[1]++;
		upload_device_datas("119.29.98.16", "1932", API_KEY, sensor_id_arrary, sensor_data_arrary, SIZE);
		//IP��ַ����Ҫ�޸�
		led_on(0);
		delay_ms(4000);
		led_off(0);
		delay_ms(4000);
	}
}










