#include "iwdg.h"

void iwdg_init(int ms)//初始化的函数(函数内部设置预分频值和重装载值)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//开启了PR寄存器和RLR寄存器的写访问
	IWDG_SetPrescaler(IWDG_Prescaler_64);//选择了64分频 时钟频率 40KHz/64=625Hz
	IWDG_SetReload(ms);//设置重装载值
	IWDG_ReloadCounter();//喂狗(把重装载值加载到计数器中)
	IWDG_Enable();//开启看门狗
}

void iwdg_feed_dog(void)//喂狗的操作
{
	IWDG_ReloadCounter();//喂狗(把重装载值加载到计数器中)	
}





