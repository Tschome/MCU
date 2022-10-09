#include "ldt.h"
#include "bitband.h"
#include "delay.h"

#define HC595_SCLK	PBOut(5)
#define HC595_LCLK	PBOut(4)
#define HC595_DATA	PBOut(3)
#define HC138_A2		PDOut(2)	
#define HC138_A1		PCOut(12)	
#define HC138_A0		PCOut(11)

void ldt_init(void)//初始化的函数
{
	GPIO_InitTypeDef Gpio_Value;//定义GPIO初始化的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	//通过APB2总线使能GPIOB GPIOC GPIOD AFIO的时钟
	//需要把PB3管脚的JTAG功能关闭
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	//改变指定管脚的映射(JTAG-DP关闭 + SW-DP使能)
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择了推挽输出
	Gpio_Value.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;//选择了3 4 5号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速率
	GPIO_Init(GPIOB, &Gpio_Value);//按照上述配置初始化GPIOB组的管脚
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;//选择了11 12号管脚
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_2;//选择了2号管脚
	GPIO_Init(GPIOD, &Gpio_Value);//按照上述配置初始化GPIOD组的管脚
}

void hc138_out_data(u8 data)//通过74HC138选择数码管的公共端
{
	switch(data)
	{
		case 0 : HC138_A2 = 0; HC138_A1 = 0; HC138_A0 = 0; break;//选择了CH1公共端
		case 1 : HC138_A2 = 0; HC138_A1 = 0; HC138_A0 = 1; break;//选择了CH2公共端
		case 2 : HC138_A2 = 0; HC138_A1 = 1; HC138_A0 = 0; break;//选择了CH3公共端
		case 3 : HC138_A2 = 0; HC138_A1 = 1; HC138_A0 = 1; break;//选择了CH4公共端
	}
}

void hc595_send_data(u8 data)//通过74HC595把串行数据data转换成并行数据
{
	u8 i = 0;//循环变量
	
	for(i = 0; i < 8; i++)
	{
		HC595_SCLK = 0;//把移位寄存器的时钟线拉低
		if(data & 0x80)//判断data变量保存的数据最高位是否为1
			HC595_DATA = 1;//把最高位数据交给DS数据线
		else
			HC595_DATA = 0;//把最高位数据交给DS数据线
		data <<= 1;//把data变量中存储的数据左移1位
		HC595_SCLK = 1;//把移位寄存器的时钟线拉高
	}
	HC595_LCLK = 0;//把存储寄存器的时钟线拉低
	HC595_LCLK = 1;//把存储寄存器的时钟线拉高
}

void digit_show_data(int data)//把data变量中存储的数据显示到数码管中
{
	char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
	//定义共阴极数码管的编码
	u8 d[4] = {0};//用于存储data变量中的每一位
	u8 i = 0;//循环变量,选择数码管显示数据
	
	d[0] = data / 1000;//存储千位
	d[1] = data / 100 % 10;//存储百位
	d[2] = data / 10 % 10;//存储十位
	d[3] = data % 10;//存储个位

	for(i = 0; i < 4; i++)
	{
		hc138_out_data(i);//通过循环变量i的值选择公共端
		hc595_send_data(table[d[i]]);
		//通过d数组找到数据,再通过table数组找到数据的编码
		//再把编码交给hc595进行转换
		delay_ms(1);//延时1ms
		hc595_send_data(0);//手动清空74HC595模块中的8bit移位寄存器
	}
}






