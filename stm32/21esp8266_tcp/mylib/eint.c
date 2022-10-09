#include "eint.h"

eint_handler e_h0, e_h1, e_h2;

void eint_init(void)//初始化的函数(用于初始化GPIO管脚和NVIC和EXTI)
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO固件的结构体变量
	NVIC_InitTypeDef Nvic_Value;//定义了NVIC固件的结构体变量
	EXTI_InitTypeDef Exti_Value;//定义了EXTI固件的结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	//通过APB2总线使能GPIOA组和GPIOC组和AFIO的时钟
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPU;//选择上拉输入的模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;//选择了 9 8 号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz输出速度
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPD;//选择下拉输入的模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//选择 0 号管脚
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化GPIOA组的管脚
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	//为外部中断9选择由PC9管脚触发 为外部中断8选择由PC8管脚触发 为外部中断0选择由PA0触发
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置组优先级和子优先级的所占比例
	Nvic_Value.NVIC_IRQChannel = EXTI9_5_IRQn;//选择了中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//使能该中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//配置组优先级的级别为2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//配置子优先级的级别为2
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC中断控制器
	
	Nvic_Value.NVIC_IRQChannel = EXTI0_IRQn;//选择了中断号
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC中断控制器
	
	Exti_Value.EXTI_Line = EXTI_Line8 | EXTI_Line9;//选择外部中断号9 8
	Exti_Value.EXTI_LineCmd = ENABLE;//使能该外部中断
	Exti_Value.EXTI_Mode = EXTI_Mode_Interrupt;//选择中断模式
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Falling;//选择下降沿触发
	EXTI_Init(&Exti_Value);//按照上述的配置初始化EXTI
	
	Exti_Value.EXTI_Line = EXTI_Line0;//选择外部中断号0
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Rising;//选择上升沿触发
	EXTI_Init(&Exti_Value);//按照上述的配置初始化EXTI
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET)//判断是否是由EXTI9触发的中断
	{
		e_h0();//调用按下按键按下之后客户需要做的处理函数
		EXTI_ClearITPendingBit(EXTI_Line9);//清除外部中断9的中断标志
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)//判断是否是由EXTI8触发的中断
	{
		e_h1();//调用按下按键按下之后客户需要做的处理函数
		EXTI_ClearITPendingBit(EXTI_Line8);//清除外部中断8的中断标志
	}
}

void EXTI0_IRQHandler(void)
{
	e_h2();//调用按下按键按下之后客户需要做的处理函数
	EXTI_ClearITPendingBit(EXTI_Line0);//清除外部中断0的中断标志
}

void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2)//设置回调函数
{
	e_h0 = h0;//把形参h0所保存的函数地址转存到全局变量e_h0中
	e_h1 = h1;
	e_h2 = h2;
}








