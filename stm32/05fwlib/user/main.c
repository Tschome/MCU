#include "led.h"
#include "buzzer.h"
#include "button.h"

int main(void)
{
	int i = 0;//ѭ������
	int ret = 0;//���ڻ�ȡ����״̬�ı���
	
	led_init();//���ó�ʼ��LED�Ƶĺ���
	buzzer_init();//���ó�ʼ���������ĺ���
	button_init();//���ð�����ʼ���ĺ���
	
	for(i = 0; i < 3; i = (i + 1) % 3)//i = 0 1 2
	{
		ret = button_status(i);
			ret == 1 ? buzzer_on(), led_on(i) : buzzer_off(), led_off(i);
	}
}
/*
���Դ�������һЩ������������
*/




