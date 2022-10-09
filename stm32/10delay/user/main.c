#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"

int main(void)
{
	int i = 0;//循环变量
	
	led_init();//调用初始化LED灯的函数
	buzzer_init();//调用初始化蜂鸣器的函数
	button_init();//调用按键初始化的函数
	delay_init();//调用延时初始化的函数
	
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





