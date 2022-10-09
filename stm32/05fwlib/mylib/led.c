#include "led.h"

void led_init(void)//初始化LED灯
{
	GPIO_InitTypeDef Led_Value;//定义了GPIO初始化的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟

	Led_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择了推挽的输出模式
	Led_Value.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;//选择了1 2 3号管脚
	Led_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速率
	GPIO_Init(GPIOC, &Led_Value);//按照上述配置初始化GPIOC组的管脚

	GPIO_ResetBits(GPIOC, GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
	//把PC1 PC2 PC3管脚输出低电平
}

void led_on(int nu)//通过形参nu选择点亮相应的LED灯
{
	switch(nu)
	{
		case 0 : GPIO_SetBits(GPIOC, GPIO_Pin_1); break;//把PC1管脚输出高电平
		case 1 : GPIO_SetBits(GPIOC, GPIO_Pin_2); break;//把PC2管脚输出高电平
		case 2 : GPIO_SetBits(GPIOC, GPIO_Pin_3); break;//把PC3管脚输出高电平
	}
}

void led_off(int nu)//通过形参nu选择灭掉相应的LED灯
{
	switch(nu)
	{
		case 0 : GPIO_ResetBits(GPIOC, GPIO_Pin_1); break;//把PC1管脚输出低电平
		case 1 : GPIO_ResetBits(GPIOC, GPIO_Pin_2); break;//把PC2管脚输出低电平
		case 2 : GPIO_ResetBits(GPIOC, GPIO_Pin_3); break;//把PC3管脚输出低电平
	}
}





