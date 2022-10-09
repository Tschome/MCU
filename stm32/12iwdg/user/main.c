#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"
#include "iwdg.h"

int flag = 0;//全局变量flag

void h0(void)
{
	flag = 1;//改变flag的值
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
	led_init();//调用LED灯初始化的函数
	buzzer_init();//调用蜂鸣器初始化的函数
	button_init();//调用按键初始化的函数
	delay_init();//调用延时初始化的函数
	eint_init();//调用外部中断初始化的函数
	
	set_eint_handler(h0, h1, h2);//设置回调函数
	
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





