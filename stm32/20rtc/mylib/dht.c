#include "dht.h"
#include "bitband.h"
#include "delay.h"

void set_dht_output(void)//把PC10管脚初始化成输出模式
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO初始化的结构体类型变量
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择了推挽的输出模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//选择了10号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速率
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化PC10管脚
}

void set_dht_input(void)//把PC10管脚初始化成输入模式
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO初始化的结构体类型变量
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//选择了浮空输入模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//选择了10号管脚
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化PC10管脚
}

void dht_output_status(int state)
{
	set_dht_output();//把PC10管脚配置为输出模式
	PCOut(10) = state;//把管脚输出高低电平
}

int dht_input_status(void)
{
	set_dht_input();//把PC10管脚配置为输入模式
	return PCIn(10);
}

void dht_init(void)//初始化DHT的函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟
}

void get_dht_value(char *buf)//获取DHT11传感器的数据
{
	u8 flag = 0;
	u8 time = 0;
	u8 data = 0;
	u8 i = 0;
	
	dht_output_status(1);//把数据线拉高
	dht_output_status(0);//把数据线拉低
	delay_ms(20);//延时20毫秒
	dht_output_status(1);//把数据线拉高
	//while(dht_input_status());//以死等的方式等待数据线被拉低
	do
	{
		flag = dht_input_status();//获取数据线的电平状态
		time++;//计数自增
		delay_us(2);//延时2us
	}while(flag == 1 && time <= 20);//判断超时处理
	if(time > 20)//判断是否超时
		return ;//结束操作
	while(!dht_input_status());//等待数据线被拉高
	for(i = 0; i < 40; i++)//循环40次读取数据
	{
		while(dht_input_status());//等待数据线被拉低
		while(!dht_input_status());//等待数据线被拉高
		delay_us(40);//手动延时40us
		data <<= 1;//让data变量中的数据都左移一位
		if(dht_input_status() == 1)//判断经过延时后数据线是否还是高电平
			data |= 1;//以高位先出的方式读取数据
		if((i + 1) % 8 == 0)//另存i = 7 15 23 31 39
		{
			buf[i / 8] = data;//把数据另存到buf空间中
			data = 0;//把变量空间清空
		}
	}
	dht_output_status(1);//把数据线拉高
}






