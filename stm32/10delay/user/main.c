#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"

int main(void)
{
	int i = 0;//ѭ������
	
	led_init();//���ó�ʼ��LED�Ƶĺ���
	buzzer_init();//���ó�ʼ���������ĺ���
	button_init();//���ð�����ʼ���ĺ���
	delay_init();//������ʱ��ʼ���ĺ���
	
	for(i = 0; i < 3; i = (i + 1) % 3)//i = 0 1 2
	{
		led_on(i);
		buzzer_on();
		delay_ms(500);
		led_off(i);
		buzzer_off();
		delay_ms(500);
	}
}





