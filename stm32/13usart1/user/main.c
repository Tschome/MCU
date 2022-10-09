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
	u8 c = 'A';//c�����洢���������������͵�
	u8 ret = 0;//ret�����������������ݵ�
	
	led_init();//����LED�Ƴ�ʼ���ĺ���
	buzzer_init();//���÷�������ʼ���ĺ���
	button_init();//���ð�����ʼ���ĺ���
	delay_init();//������ʱ��ʼ���ĺ���
	eint_init();//�����ⲿ�жϳ�ʼ���ĺ���
	usart_1_init();//����USART1��ʼ���ĺ���
	
	set_usart1_handler(recv_handler);//���ûص�����
	
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










