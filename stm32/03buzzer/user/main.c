#include "led.h"
#include "buzzer.h"

int main(void)
{
	int i = 0;//ѭ������
	int n = 0;
	
	led_init();//���ó�ʼ��LED�Ƶĺ���
	buzzer_init();//���ó�ʼ���������ĺ���
	
	for(i = 0; i < 3; i = (i + 1) % 3)//i = 0 1 2
	{
		led_on(i);
		buzzer_on();
		for(n = 0; n < 1000000; n++);
		led_off(i);
		buzzer_off();
		for(n = 0; n < 1000000; n++);
	}
}
/*
���Դ�������һЩ������������
*/




