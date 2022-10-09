#include "led.h"
#include "bitband.h"

void led_init(void)//初始化的函数(初始化LED灯所连接的GPIO管脚)
{
	GPIO_InitTypeDef Led_Value;//定义了GPIO固件的结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟
	
	Led_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择了推挽的输出模式
	Led_Value.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//选择了 1 2 3 号管脚
	Led_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速度
	GPIO_Init(GPIOC, &Led_Value);//按照上述的配置初始化GPIOC组的管脚
	
	PCOut(1) = 0;//把PC1管脚拉低
	PCOut(2) = 0;//把PC2管脚拉低
	PCOut(3) = 0;//把PC3管脚拉低
}

void led_on(int nu)//根据nu参数点亮相应的LED灯
{
	switch(nu)
	{
		case 0 : PCOut(1) = 1; break;
		case 1 : PCOut(2) = 1; break;
		case 2 : PCOut(3) = 1; break;
	}
}

void led_off(int nu)//根据nu参数灭掉相应的LED灯
{
	switch(nu)
	{
		case 0 : PCOut(1) = 0; break;
		case 1 : PCOut(2) = 0; break;
		case 2 : PCOut(3) = 0; break;
	}
}





