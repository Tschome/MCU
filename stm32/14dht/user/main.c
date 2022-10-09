#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "delay.h"
#include "eint.h"
#include "iwdg.h"
#include "usart1.h"
#include "stdio.h"
#include "dht.h"
/*
	C���� �ַ�������ַ�ָ��
		atoi();	//���ַ���ת������������
//myatoi();	mystrcpy mystrcat mystrcmp mystrlen
//mystrchr(); �Լ���ȥ�Ժ��Լ�ȥʵ��
//	itoa(); //��C��׼����û�иú���(�Լ�ʵ��itoa����)
//�ײ�->�����������
//printf scanf
//myprintf
	printf sprintf fprintf
*/
struct data
{
	int Pm_Value;
	double Temp_Value;
	double Hum_Value;
	char buf[16];
};

/*
����״̬��
"ON"	BUZZER_ON
"OFF"	BUZZER_OFF
*/

#define O_FLAG 0
#define N_FLAG 1
#define F_FLAG 2
int flag = O_FLAG;

void recv_handler(u8 c)
{
	switch(flag)
	{
		case O_FLAG : if(c == 'O')
										flag = N_FLAG;
									break;
		case N_FLAG : if(c == 'N')
									{
										buzzer_on();
										flag = O_FLAG;
									}
									else if(c == 'F')
										flag = F_FLAG;
									else
										flag = O_FLAG;
									break;
		case F_FLAG : if(c == 'F')
										buzzer_off();
									flag = O_FLAG;
									break;
	}
}

int main(void)
{
//	u8 c = 'A';//c�����洢���������������͵�
	u8 ret = 0;//ret�����������������ݵ�
	struct data d = {9527, 23.45, 34.56, "uplooking"};
	char str[64] = {0};//str������Žṹ�����ݵ��ַ���
	char dht_buf[5] = {0};
	
	led_init();//����LED�Ƴ�ʼ���ĺ���
	buzzer_init();//���÷�������ʼ���ĺ���
	button_init();//���ð�����ʼ���ĺ���
	delay_init();//������ʱ��ʼ���ĺ���
	eint_init();//�����ⲿ�жϳ�ʼ���ĺ���
	usart_1_init();//����USART1��ʼ���ĺ���
	dht_init();//����DHT11��ʼ���ĺ���
		
	set_usart1_handler(recv_handler);//���ûص�����
	
	while(1)
	{
		get_dht_value(dht_buf);
		printf("Hum:%d Temp:%d\n", dht_buf[0], dht_buf[2]);
//		scanf("%c", &ret);
//		switch(ret)
//		{
//			case 'a' : buzzer_on(); break;
//			case 'b' : buzzer_off(); break;
//		}
//		usart_1_send_data(str);
//		usart_1_send_byte(c++);
//		if(c > 'Z')
//			c = 'A';
		led_on(0);
		delay_ms(500);
		led_off(0);
		delay_ms(500);
	}
}










