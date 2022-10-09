#include "buzzer.h"

void buzzer_init(void)//蜂鸣器的初始化
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟
	
	GPIOC_CRL |= (3 << 28);//把PC7管脚配置为50MHz的输出模式
	GPIOC_CRL &= ~((unsigned int )3 << 30);//把PC7管脚配置为推挽输出
	GPIOC_ODR &= ~(1 << 7);//把PC7管脚输出低电平
}

void buzzer_on(void)//蜂鸣器响
{
	GPIOC_ODR |= (1 << 7);//把PC7管脚输出高电平
}

void buzzer_off(void)//蜂鸣器不响
{
	GPIOC_ODR &= ~(1 << 7);//把PC7管脚输出低电平
}


