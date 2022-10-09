#include "iwdg.h"

void iwdg_init(int ms)//初始化的函数(可以在内部设置预分频器和计数值)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//开辟PR和RLR寄存器的写访问(关闭这两个寄存器的写保护)
	IWDG_SetPrescaler(IWDG_Prescaler_64);//选择64分频	40KHz / 64 = 625Hz
	IWDG_SetReload(ms);//设置重载值
	IWDG_ReloadCounter();//喂狗
	IWDG_Enable();//启动看门狗
}

void iwdg_feed_dog(void)//喂狗的功能函数
{
	IWDG_ReloadCounter();//喂狗
}








