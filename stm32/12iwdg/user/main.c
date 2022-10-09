#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"
#include "iwdg.h"

int flag = 0;//ȫ�ֱ���flag

void h0(void)
{
	flag = 1;//�ı�flag��ֵ
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
	
	buzzer_on();
	iwdg_init(6 * 625);
	delay_ms(4000);
	buzzer_off();
	
	while(!flag)
	{
		iwdg_feed_dog();
		led_on(0);
		delay_ms(2000);
		led_off(0);
		delay_ms(2000);
	}
	
	while(1);
}





