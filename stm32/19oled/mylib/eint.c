#include "eint.h"

eint_handler eh0, eh1, eh2;//定义了全局变量(函数指针)

void eint_init(void)//初始化的函数(用于初始化GPIO和EXTI以及NVIC)
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO初始化的结构体类型变量
	NVIC_InitTypeDef Nvic_Value;//定义了NVIC初始化的结构体类型变量
	EXTI_InitTypeDef Exti_Value;//定义了EXTI初始化的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);
	//通过APB2总线使能GPIOC组和GPIOA组的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//通过APB2总线使能AFIO的时钟
	//(由于需要通过AFIO为外部中断选择触发的GPIO管脚)
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPU;//选择了上拉输入的模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;//选择了9 8 号管脚
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_IPD;//选择了下拉输入的模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//选择了0号管脚
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化GPIOA组的管脚

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource9);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource8);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	//为EXTI9选择由PC9管脚触发 为EXTI8选择由PC8管脚触发
	//为EXTI0选择由PA0管脚触发
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置组优先级和子优先级的所占比例
	Nvic_Value.NVIC_IRQChannel = EXTI9_5_IRQn;//选择了中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//选择使能该中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//配置组优先级的级别为2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//配置子优先级的级别为2
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC

	Nvic_Value.NVIC_IRQChannel = EXTI0_IRQn;//选择了中断号
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC
	
	Exti_Value.EXTI_Line = EXTI_Line9 | EXTI_Line8;//选择了外部中断号9 8
	Exti_Value.EXTI_LineCmd = ENABLE;//选择使能该外部中断
	Exti_Value.EXTI_Mode = EXTI_Mode_Interrupt;//选择了中断的模式
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Falling;//选择了下降沿触发
	EXTI_Init(&Exti_Value);//按照上述配置初始化EXTI9 EXTI8
	
	Exti_Value.EXTI_Line = EXTI_Line0;//选择了EXTI0外部中断号
	Exti_Value.EXTI_Trigger = EXTI_Trigger_Rising;//选择了上升沿触发
	EXTI_Init(&Exti_Value);//按照上述配置初始化EXTI0	
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET)//判断是否是由EXTI9触发的中断
	{
		eh0();//调用PC9按键按下之后客户需要做的处理
		EXTI_ClearITPendingBit(EXTI_Line9);//清除EXTI9的中断标志位
	}
	if(EXTI_GetITStatus(EXTI_Line8) == SET)//判断是否是由EXTI9触发的中断
	{
		eh1();//调用PC8按键按下之后客户需要做的处理
		EXTI_ClearITPendingBit(EXTI_Line8);//清除EXTI9的中断标志位
	}
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)//判断是否是由EXTI9触发的中断
	{
		eh2();//调用PC9按键按下之后客户需要做的处理
		EXTI_ClearITPendingBit(EXTI_Line0);//清除EXTI9的中断标志位
	}
}

void set_eint_handler(eint_handler h0, eint_handler h1, eint_handler h2)//设置回调函数
{
	eh0 = h0;//把形参指针保存的地址另存到全局指针中
	eh1 = h1;
	eh2 = h2;
}





