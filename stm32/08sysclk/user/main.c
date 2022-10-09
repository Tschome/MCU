#include "led.h"
#include "buzzer.h"
#include "button.h"

int main(void)
{
	int i = 0;//循环变量
	int ret = 0;//用于获取按键状态的变量
	
	led_init();//调用初始化LED灯的函数
	buzzer_init();//调用初始化蜂鸣器的函数
	button_init();//调用按键初始化的函数
	
	for(i = 0; i < 3; i = (i + 1) % 3)//i = 0 1 2
	{
		ret = button_status(i);
			ret == 1 ? buzzer_on(), led_on(i) : buzzer_off(), led_off(i);
	}
}
/*
可以从网上找一些蜂鸣器的曲谱
*/




