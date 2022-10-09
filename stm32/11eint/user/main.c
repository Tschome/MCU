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
	led_init();//调用LED灯初始化的函数
	buzzer_init();//调用蜂鸣器初始化的函数
	button_init();//调用按键初始化的函数
	delay_init();//调用延时初始化的函数
	eint_init();//调用外部中断初始化的函数
	
	set_eint_handler(h0, h1, h2);//设置回调函数
	
	while(1);
}





