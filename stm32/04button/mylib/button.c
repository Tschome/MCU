#include "button.h"

void button_init(void)//按键初始化的函数
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOA组和GPIOC组的时钟
	
	GPIOA_CRL &= ~(15 << 0);//把PA0管脚配置为输入模式
	GPIOA_CRL |= (2 << 2);//把PA0管脚配置为上拉/下拉输入模式
	GPIOA_ODR &= ~(1 << 0);//默认把PA0管脚拉低
	
	GPIOC_CRH &= ~((15 << 0) | (15 << 4));//把PC9 PC8管脚配置为输入模式
	GPIOC_CRH |= ((2 << 2) | (2 << 6));//把PC9 PC8 管脚配置为上拉/下拉输入模式
	GPIOC_ODR |= ((1 << 8) | (1 << 9));//默认把PC9 PC8管脚拉高
}

int button_status(int nu)//通过nu来检测相应按键的状态
{
	//想要读取GPIOC_IDR寄存器的第9位
	int ret = 0;
	
	switch(nu)
	{
		case 0 : ret = (GPIOC_IDR >> 9) & 0x01; break;//获取PC9管脚的电平高低
		case 1 : ret = (GPIOC_IDR >> 8) & 0x01; break;//获取PC8管脚的电平高低
		case 2 : ret = GPIOA_IDR & 0x01; ret = !ret; break;//获取PA0管脚的电平高低
	}
	
	return !ret;
}






