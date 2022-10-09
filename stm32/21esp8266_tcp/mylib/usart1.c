#include "usart1.h"

usart1_handler u1_h;

void usart_1_init(void)//初始化的函数(初始化GPIO管脚和串口功能)
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO固件的结构体变量
	USART_InitTypeDef Usart_Value;//定义了USART固件的结构体变量
	NVIC_InitTypeDef Nvic_Value;//定义了NVIC固件的结构体变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	//通过APB2总线使能GPIOA组和USART1的时钟
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF_PP;//选择了推挽的复用模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_9;//选择了 9 号管脚(PA9是发送管脚)
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速度
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化GPIOA组的管脚

	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//选择了浮空的输入模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//选择了 10 号管脚(PA10是接收管脚)
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化GPIOA组的管脚
	
	Usart_Value.USART_BaudRate = 115200;//选择了115200的波特率
	Usart_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//选择了关闭硬件流控
	Usart_Value.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//选择了发送模式和接收模式
	Usart_Value.USART_Parity = USART_Parity_No;//选择了没有奇偶校验
	Usart_Value.USART_StopBits = USART_StopBits_1;//选择了1个停止位
	Usart_Value.USART_WordLength = USART_WordLength_8b;//选择了8个数据位
	USART_Init(USART1, &Usart_Value);//按照上述配置初始化USART1
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置组优先级和子优先级的所占比例
	Nvic_Value.NVIC_IRQChannel = USART1_IRQn;//选择了USART1中断源的中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//选择使能该中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//选择了组优先级的级别为2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//选择了子优先级的级别为2
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC中断控制器
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能了USART1的接收数据触发中断
	
	USART_Cmd(USART1, ENABLE);//使能USART1的功能
}

void usart_1_send_byte(unsigned char c)//发送一个字节的数据
{
	USART_SendData(USART1, c);//通过USART1把c变量保存的数据发送出去
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);//检验USART1的发送数据是否发送成功了(超时处理)
	USART_ClearFlag(USART1, USART_FLAG_TC);//清除USART1的发送成功的标志状态
}

void usart_1_send_data(char *buf)//发送一个字符串的数据
{
	while(*buf)//通过while循环把字符串中的有效字符遍历一遍
	{
		usart_1_send_byte(*buf);//把有效的字符进行发送
		buf++;//让buf指针指向下一个字符
	}
}

unsigned char usart_1_recv_byte(void)//接收一个字节数据
{
	unsigned char ret = 0;//ret变量用来接收USART1接到的数据
	
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)//判断USART1是否接收到了数据
	{
		ret = USART_ReceiveData(USART1);//把USART1接收到的数据保存到ret变量中
		USART_ClearFlag(USART1, USART_FLAG_RXNE);//清除USART1接收到数据的标志
	}
	
	return ret;
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//判断是否是由USART1的接收数据触发的中断
	{
		u1_h(USART_ReceiveData(USART1));//接收USART1的数据，并把接收到的数据以传参的形式传递给回调函数
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除USART1接收数据的中断标志
	}
}

void set_usart1_handler(usart1_handler h)//设置回调函数
{
	u1_h = h;//把形参h所存储的函数地址另存到全局变量u1_h中
}






