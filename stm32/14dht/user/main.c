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
	C语言 字符数组和字符指针
		atoi();	//把字符串转换成整型数据
//myatoi();	mystrcpy mystrcat mystrcmp mystrlen
//mystrchr(); 自己下去以后自己去实现
//	itoa(); //在C标准库中没有该函数(自己实现itoa功能)
//底层->裸板驱动程序
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
有限状态机
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
//	u8 c = 'A';//c变量存储的数据是用来发送的
	u8 ret = 0;//ret变量是用来接收数据的
	struct data d = {9527, 23.45, 34.56, "uplooking"};
	char str[64] = {0};//str用来存放结构体数据的字符串
	char dht_buf[5] = {0};
	
	led_init();//调用LED灯初始化的函数
	buzzer_init();//调用蜂鸣器初始化的函数
	button_init();//调用按键初始化的函数
	delay_init();//调用延时初始化的函数
	eint_init();//调用外部中断初始化的函数
	usart_1_init();//调用USART1初始化的函数
	dht_init();//调用DHT11初始化的函数
		
	set_usart1_handler(recv_handler);//设置回调函数
	
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










