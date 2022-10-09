#include "usart1.h"
#include "stdio.h"

usart1_handler u1_h;//定义全局变量(函数指针)

//禁用半主机模式
#pragma import(__use_no_semihosting)

struct __FILE
{
	int a;
};

FILE __stdout;
FILE __stdin;

void _sys_exit(int x)
{
	
}

int fputc(int c, FILE *f)
{
	usart_1_send_byte(c);
	return c;
}

int fgetc(FILE *f)//使用轮询的方式
{
	return usart_1_recv_byte();
}

void usart_1_init(void)//初始化的函数(初始化GPIO管脚和串口功能)
{
	GPIO_InitTypeDef Gpio_Value;//定义了GPIO初始化的结构体类型变量
	USART_InitTypeDef Usart_Value;//定义了USART初始化的结构体类型变量
	NVIC_InitTypeDef Nvic_Value;//定义了NVIC初始化的结构体类型变量
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
	//通过APB2总线使能GPIOA组和USART1的时钟
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AF_PP;//选择了推挽的复用模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_9;//选择了9号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择了50MHz的输出速率
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化PA9管脚

	Gpio_Value.GPIO_Mode = GPIO_Mode_IN_FLOATING;//选择了浮空输入模式
	Gpio_Value.GPIO_Pin = GPIO_Pin_10;//选择了10号管脚
	GPIO_Init(GPIOA, &Gpio_Value);//按照上述配置初始化PA10管脚

	Usart_Value.USART_BaudRate = 115200;//配置为115200的波特率
	Usart_Value.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//选择关闭硬件流控
	Usart_Value.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//选择了发送和接收模式
	Usart_Value.USART_Parity = USART_Parity_No;//选择了没有奇偶校验
	Usart_Value.USART_StopBits = USART_StopBits_1;//选择了一个停止位
	Usart_Value.USART_WordLength = USART_WordLength_8b;//选择了8个数据位
	USART_Init(USART1, &Usart_Value);//按照上述配置初始化USART1
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置组优先级和子优先级的所占比例
	Nvic_Value.NVIC_IRQChannel = USART1_IRQn;//选择了USART1的中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//选择使能该中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//选择了组优先级的级别为2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//选择了子优先级的级别为2
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//使能了USART1的接收数据触发中断
	
	USART_Cmd(USART1, ENABLE);//使能USART1的功能
}

void usart_1_send_byte(u8 c)//发送一个字节的数据
{
	USART_SendData(USART1, c);//把形参c存储的数据通过USART1串口进行发送
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	//以死等的方式等待USART1的发送数据,发送成功
	USART_ClearFlag(USART1, USART_FLAG_TC);//清除USART1的发送数据成功的标志状态
}

void usart_1_send_data(char *buf)//发送字符串
{
	while(*buf)
	{
		usart_1_send_byte(*buf);
		buf++;
	}
}

u8 usart_1_recv_byte(void)//接收一个字节数据
{
	u8 ret = 0;//ret变量用来接收USART1接收到的数据
	
	if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	//判断USART1是否接收到了数据
	{
		ret = USART_ReceiveData(USART1);//把USART1接收到的数据保存到ret变量中
		USART_ClearFlag(USART1, USART_FLAG_RXNE);//清除USART1接收到数据的标志
	}
	
	return ret;//把接收到的数据返回
}

void USART1_IRQHandler(void)//USART1的中断处理函数
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)//判断是否是由USART1接收数据触发的中断
	{
		u1_h(USART_ReceiveData(USART1));//把从USART1中读取到的数据交给客户的数据处理函数
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//清除USART1接收数据的中断标志
	}
}

void set_usart1_handler(usart1_handler h)//设置回调函数
{
	u1_h = h;
}



