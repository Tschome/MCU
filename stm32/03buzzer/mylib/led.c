#include "led.h"

void led_init(void)//初始化LED灯
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟

	GPIOC_CRL |= ((3 << 4) | (3 << 8) | (3 << 12));
	//把PC1 2 3管脚配置为输出模式,并且是50MHz的输出速率
	GPIOC_CRL &= ~((3 << 6) | (3 << 10) | (3 << 14));
	//把PC1 2 3管脚配置为推挽的输出模式
	GPIOC_ODR &= ~((1 << 1) | (1 << 2) | (1 << 3));
	//把PC1 2 3管脚输出低电平
}

void led_on(int nu)//通过形参nu选择点亮相应的LED灯
{
	switch(nu)
	{
		case 0 : GPIOC_ODR |= (1 << 1); break;
		case 1 : GPIOC_ODR |= (1 << 2); break;
		case 2 : GPIOC_ODR |= (1 << 3); break;
	}
}

void led_off(int nu)//通过形参nu选择灭掉相应的LED灯
{
	switch(nu)
	{
		case 0 : GPIOC_ODR &= ~(1 << 1); break;
		case 1 : GPIOC_ODR &= ~(1 << 2); break;
		case 2 : GPIOC_ODR &= ~(1 << 3); break;
	}
}





