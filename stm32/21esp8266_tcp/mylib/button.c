#include "button.h"
#include "bitband.h"

void button_init(void)//初始化的函数(初始化按键所连接的GPIO管脚)
{
	GPIO_InitTypeDef Button_Value;//定义了GPIO固件的结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	//通过APB2总线使能GPIOA组的 和 GPIOC组的时钟
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPU;//选择了上拉输入的模式
	Button_Value.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;//选择了 8 9 号管脚
	Button_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速度
	GPIO_Init(GPIOC, &Button_Value);//按照上述配置初始化GPIOC组的管脚
	
	Button_Value.GPIO_Mode = GPIO_Mode_IPD;//选择下拉输入的模式
	Button_Value.GPIO_Pin = GPIO_Pin_0;//选择了 0 号管脚
	GPIO_Init(GPIOA, &Button_Value);//按照上述配置初始化GPIOA组的管脚
}

int button_status(int nu)//根据参数nu检测相应的功能按键是否被按下
{
	int ret = 0;//ret变量用来获取GPIO寄存器中的数据
	
	switch(nu)
	{
		case 0 : ret = PCIn(9); break;//读PC9管脚的电平高低
		case 1 : ret = PCIn(8); break;//读PC8管脚的电平高低
		case 2 : ret = PAIn(0); ret = !ret; break;//读PA0管脚的电平高低
	}
	return !ret;//把读到的数据做逻辑非的操作再返回
}










