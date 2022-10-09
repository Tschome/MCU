#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"
#include "iwdg.h"
#include "usart1.h"

void recv_handler(u8 c)
{
	switch(c)
	{
		case 'a' : buzzer_on(); break;
		case 'b' : buzzer_off(); break;
	}
}

int main(void)
{
	u8 c = 'A';//c变量存储的数据是用来发送的
	u8 ret = 0;//ret变量是用来接收数据的
	
	led_init();//调用LED灯初始化的函数
	buzzer_init();//调用蜂鸣器初始化的函数
	button_init();//调用按键初始化的函数
	delay_init();//调用延时初始化的函数
	eint_init();//调用外部中断初始化的函数
	usart_1_init();//调用USART1初始化的函数
	
	set_usart1_handler(recv_handler);//设置回调函数
	
	while(1)
	{
		usart_1_send_byte(c++);
		if(c > 'Z')
			c = 'A';
		led_on(0);
		delay_ms(500);
		led_off(0);
		delay_ms(500);
	}
}










