#include "button.h"

void button_init(void)//按键初始化的函数
{
	GPIO_InitTypeDef Button_Value;//定义了GPIO初始化的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOA组和GPIOC组的时钟
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPU;//选择了上拉输入的模式
	Button_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;//选择了9 8号管脚
	GPIO_Init(GPIOC, &Button_Value);//按照上述配置初始化GPIOC组的管脚
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPD;//选择了下拉输入的模式
	Button_Value.GPIO_Pin = GPIO_Pin_0;//选择了0号管脚
	GPIO_Init(GPIOA, &Button_Value);//按照上述配置初始化GPIOA组的管脚
}

int button_status(int nu)//通过nu来检测相应按键的状态
{
	int ret = 0;//用于读取管脚的电平高低
	
	switch(nu)
	{
		case 0 :ret = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_9); break;//读取PC9管脚的电平高低
		case 1 :ret = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_8); break;//读取PC8管脚的电平高低
		case 2 :ret = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0); ret = !ret; break;//读取PA0管脚的电平高低
	}
	
	return !ret;
}






