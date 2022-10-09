#include "ldt.h"
#include "bitband.h"
#include "delay.h"

#define HC138_A0		PCOut(11)
#define HC138_A1		PCOut(12)
#define HC138_A2		PDOut(2)
#define HC595_SCLK	PBOut(5)
#define HC595_LCLK	PBOut(4)
#define HC595_DATA	PBOut(3)

void ldt_init(void)//初始化的函数(初始化模块使用到的管脚)
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO固件的结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
	RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);
	//通过APB2总线使能GPIOC组 GPIOB组 GPIOD组 和AFIO的时钟
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//改变指定管脚的映射
	//JTAG-DP 关闭功能 + SW-DP 使能
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择推挽的输出模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;//选择 11 12 号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz的输出速度
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_2;//选择 2 号管脚
	GPIO_Init(GPIOD, &Gpio_Value);//按照上述配置初始化GPIOD组的管脚
	
	Gpio_Value.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;//选择3 4 5号管脚
	GPIO_Init(GPIOB, &Gpio_Value);//按照上述配置初始化GPIOB组的管脚
	
	HC138_A0 = 0;
	HC138_A1 = 0;
	HC138_A2 = 0;
	HC595_SCLK = 0;
	HC595_LCLK = 0;
	HC595_DATA = 0;
}

void hc138_out_data(uint8_t data)//通过hc138选择数码管的公共端
{//按照74HC138的官方手册上的真值表配置函数
	switch(data)//通过分支语句区分数码管的公共端
	{
		case 0 : HC138_A0 = 0; HC138_A1 = 0; HC138_A2 = 0; break;//选择的是CH1数码管
		case 1 : HC138_A0 = 1; HC138_A1 = 0; HC138_A2 = 0; break;//选择的是CH2数码管
		case 2 : HC138_A0 = 0; HC138_A1 = 1; HC138_A2 = 0; break;//选择的是CH3数码管
		case 3 : HC138_A0 = 1; HC138_A1 = 1; HC138_A2 = 0; break;//选择的是CH4数码管
	}
}

void hc595_send_data(uint8_t data)//通过hc595把串行数据转换成并行数据
{//按照74HC595的官方手册上的流程配置函数
	uint8_t i = 0;//i变量为循环变量
	
	for(i = 0; i < 8; i++)
	{
		HC595_SCLK = 0;//把移位寄存器的时钟线拉低
		if(data & 0x80)//判断data数据的最高位是否为真
			HC595_DATA = 1;
		else
			HC595_DATA = 0;
		data <<= 1;//把最高位的数据移出,次高位的数据移到了最高位上
		HC595_SCLK = 1;//把移位寄存器的时钟线拉高
	}
	HC595_LCLK = 0;//把存储寄存器的时钟线拉低
	HC595_LCLK = 1;//把存储寄存器的时钟线拉高
}

void digit_show_data(int data)//在数码管中显示数据
{//使用的是4位共阴极的数码管,自己去找编码 0x3F 0x06 ... (0 ~ 9 A ~ F)
	uint8_t table[] = {0x3f,0x06,0x5b,0x4f,
	0x66,0x6d,0x7d,0x07,
	0x7f,0x6f,0x77,0x7c,
	0x39,0x5e,0x79,0x71};//存放数码管的编码
	uint8_t d[4] = {0};//把数据分解成一位一位的存到数组中
	uint8_t i = 0;//I变量是循环变量用于做分时显示
	
	d[0] = data / 1000;
	d[1] = data / 100 % 10;
	d[2] = data / 10 % 10;
	d[3] = data % 10;
	
	for(i = 0; i < 4; i++)
	{
		hc138_out_data(i);//选择公共端(选择让哪个数码管显示数据)
		hc595_send_data(table[d[i]]);//把编码通过函数转换成并行数据
		delay_ms(1);
		hc595_send_data(0);//手动清空74HC595模块中8位位移寄存器中的数据
	}
}










