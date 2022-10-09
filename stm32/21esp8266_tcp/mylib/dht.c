#include "dht.h"
#include "bitband.h"
#include "delay.h"

void set_dht_gpio_output(void)//把PC10管脚初始化成输出模式
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO固件的结构体变量
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择了推挽的输出模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//选择了 10 号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速度
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
}	

void set_dht_gpio_input(void)//把PC10管脚初始化成输入模式
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO固件的结构体变量
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//选择了浮空输入的模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//选择了 10 号管脚
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
}

void dht_output_state(int status)//通过参数status来控制数据线高低电平
{
	set_dht_gpio_output();//把数据线初始化成输出模式
	if(status == 0)//判断参数status是否为0
		PCOut(10) = 0;//拉低数据线
	else
		PCOut(10) = 1;//拉高数据线
}

int dht_input_state(void)//检测数据线的高低电平以返回值的形式返回
{
	set_dht_gpio_input();//把数据线初始化成输入模式
	return PCIn(10);//通过位带把PC10管脚的电平高低返回
}

void dht_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟
}

void get_dht_value(char *buf)
{
	char flag = 0;//flag变量用来获取数据线的高低电平
	char time = 0;//time变量用来超时处理的计数
	char i = 0;//i变量为循环变量
	char tmp = 0;//用来接收数据
	
	dht_output_state(1);//拉高数据线
	dht_output_state(0);//拉低数据线
	delay_ms(20);				//延时20毫秒
	dht_output_state(1);//拉高数据线
	//while(dht_input_state());//死等(等数据线拉低)
	do//超时处理(等待数据线拉低)
	{
		flag = dht_input_state();//获取数据线的高低电平
		delay_us(2);//延时2微秒
		time++;//计数值自增
	}while(flag == 1 && time <= 20);//判断flag是否是1并且time小于等于20
	if(time > 20)//如果time大于20,超时
		return;
	while(!dht_input_state());//等待数据线拉高
	for(i = 0; i < 40; i++)//循环40次,接收40位的数据
	{
		while(dht_input_state());//等待数据线拉低
		while(!dht_input_state());//等待数据线拉高
		delay_us(40);//延时40微秒
		tmp <<= 1;
		if(dht_input_state())//判断数据线是否为高电平
			tmp |= 1;//高位先出
		if((i + 1) % 8 == 0)//i = 7 15 23 31 39(每获取8位数据转存一次)
		{
			buf[i / 8] = tmp;//把8位的数据转存到buf中
			tmp = 0;//清空tmp
		}
	}
	dht_output_state(1);//拉高数据线
}








