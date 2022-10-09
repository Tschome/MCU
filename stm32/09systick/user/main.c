#include "led.h"
#include "buzzer.h"
#include "button.h"

int flag = 0;//定义全局变量,

void timing_delay(void)//只要触发中断该函数就被调用
{
	if(flag == 0)
		return ;
	flag--;
}

void my_delay_ms(int ms)//自己实现的毫秒级延时
{
	flag = ms;//把形参ms的值赋值给全局变量flag
	while(flag);//轮询等待flag变量跳出循环
}

int main(void)
{
	int i = 0;//循环变量
	
	SysTick_Config(9000);//配置系统定时器的计数值
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//把系统定时器的时钟频率设置为9MHz
	//系统定时器的时钟频率为9MHz 如果想要进行1ms的延时
	//那么计数值要多大 9000
	//官方固件默认开启了外部触发
	//当计数值从9000->0,则会触发中断,打断CPU,CPU跳到
	//中断处理函数中执行相应的内容,执行完之后CPU再跳回来
	//.s文件中有异常向量表,异常向量表中存储的是中断处理函数的函数名
	//异常向量表中存储的是中断处理函数的入口地址
	
	led_init();//调用初始化LED灯的函数
	buzzer_init();//调用初始化蜂鸣器的函数
	button_init();//调用按键初始化的函数
	
	for(i = 0; i < 3; i = (i + 1) % 3)//i = 0 1 2
	{
		led_on(i);
		buzzer_on();
		my_delay_ms(500);
		led_off(i);
		buzzer_off();
		my_delay_ms(500);
	}
}





