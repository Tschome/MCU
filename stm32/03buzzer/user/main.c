#include "led.h"
#include "buzzer.h"

int main(void)
{
	int i = 0;//循环变量
	int n = 0;
	
	led_init();//调用初始化LED灯的函数
	buzzer_init();//调用初始化蜂鸣器的函数
	
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
可以从网上找一些蜂鸣器的曲谱
*/




