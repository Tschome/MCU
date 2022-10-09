#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"

void h0(void)
{
	led_on(0);
	led_on(1);
	led_on(2);
}

void h1(void)
{
	buzzer_on();
}

void h2(void)
{
	led_off(0);
	led_off(1);
	led_off(2);
	buzzer_off();
}

int main(void)
{	
	led_init();//����LED�Ƴ�ʼ���ĺ���
	buzzer_init();//���÷�������ʼ���ĺ���
	button_init();//���ð�����ʼ���ĺ���
	delay_init();//������ʱ��ʼ���ĺ���
	eint_init();//�����ⲿ�жϳ�ʼ���ĺ���
	
	set_eint_handler(h0, h1, h2);//���ûص�����
	
	while(1);
}





