#include "led.h"
#include "buzzer.h"
#include "button.h"

int flag = 0;//����ȫ�ֱ���,

void timing_delay(void)//ֻҪ�����жϸú����ͱ�����
{
	if(flag == 0)
		return ;
	flag--;
}

void my_delay_ms(int ms)//�Լ�ʵ�ֵĺ��뼶��ʱ
{
	flag = ms;//���β�ms��ֵ��ֵ��ȫ�ֱ���flag
	while(flag);//��ѯ�ȴ�flag��������ѭ��
}

int main(void)
{
	int i = 0;//ѭ������
	
	SysTick_Config(9000);//����ϵͳ��ʱ���ļ���ֵ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	//��ϵͳ��ʱ����ʱ��Ƶ������Ϊ9MHz
	//ϵͳ��ʱ����ʱ��Ƶ��Ϊ9MHz �����Ҫ����1ms����ʱ
	//��ô����ֵҪ��� 9000
	//�ٷ��̼�Ĭ�Ͽ������ⲿ����
	//������ֵ��9000->0,��ᴥ���ж�,���CPU,CPU����
	//�жϴ�������ִ����Ӧ������,ִ����֮��CPU��������
	//.s�ļ������쳣������,�쳣�������д洢�����жϴ������ĺ�����
	//�쳣�������д洢�����жϴ���������ڵ�ַ
	
	led_init();//���ó�ʼ��LED�Ƶĺ���
	buzzer_init();//���ó�ʼ���������ĺ���
	button_init();//���ð�����ʼ���ĺ���
	
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





