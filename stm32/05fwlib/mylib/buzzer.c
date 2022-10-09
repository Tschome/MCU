#include "buzzer.h"

void buzzer_init(void)//蜂鸣器的初始化
{
	GPIO_InitTypeDef Buzzer_Value;//定义了GPIO初始化的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOC组的时钟
	
	Buzzer_Value.GPIO_Mode = GPIO_Mode_Out_PP;//选择了推挽的输出模式
	Buzzer_Value.GPIO_Pin = GPIO_Pin_7;//选择了7号管脚
	Buzzer_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速率
	GPIO_Init(GPIOC, &Buzzer_Value);//按照上述配置初始化GPIOC组的管脚
	
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);//把PC7管脚输出低电平
}

void buzzer_on(void)//蜂鸣器响
{
	GPIO_SetBits(GPIOC, GPIO_Pin_7);//把PC7管脚输出低电平
}

void buzzer_off(void)//蜂鸣器不响
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_7);//把PC7管脚输出低电平
}


