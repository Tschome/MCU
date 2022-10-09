#include "rtc.h"
#include "string.h"

const uint8_t monthTable[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//用于存储每个月的天数(2月份需要+1)
static struct time_st T;//存储每一次获取的年月日星期时分秒

static uint8_t isLeapYear(uint16_t y)   
{
	return (((!(y % 4)) && (y % 100)) || (!(y % 400)));
}

void RTC_IRQHandler(void)//RTC的中断处理函数
{
	if(RTC_GetITStatus(RTC_IT_SEC) == SET)//判断是否是由RTC的秒中断触发的中断
	{
		conv_time(&T);//把获取到的计数值转换成万年历保存到全局变量中
		RTC_ClearITPendingBit(RTC_IT_SEC);//清除RTC秒中断的中断标志
	}
}

void rtc_config(struct time_st *t)//配置RTC
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
	//通过APB1总线使能BKP和PWR的时钟(为了开启写访问)
	
	PWR_BackupAccessCmd(ENABLE);//通过PWR使能后备区域的写访问
	BKP_DeInit();//复位后备区域
	RCC_LSEConfig(RCC_LSE_ON);//通过RCC开启LSE时钟源
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);//以死等的方式等待LSE稳定
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//通过RCC为RTC选择由LSE提供时钟源
	RCC_RTCCLKCmd(ENABLE);//通过RCC使能RTC的时钟
	RTC_WaitForSynchro();//等待RTC时钟同步
	RTC_WaitForLastTask();//等待最后一次对RTC寄存器写操作的完成
	RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC的秒中断
	RTC_WaitForLastTask();//等待最后一次对RTC寄存器写操作的完成
	RTC_EnterConfigMode();//进入RTC的配置模式
	RTC_SetPrescaler(32767);//设置RTC的预分频值
	RTC_WaitForLastTask();//等待最后一次对RTC寄存器写操作的完成
	set_time(t);//设置时间(设置计数值)
	RTC_WaitForLastTask();//等待最后一次对RTC寄存器写操作的完成
	RTC_ExitConfigMode();//退出RTC的配置模式
}

void rtc_init(struct time_st *t)//初始化RTC
{
	NVIC_InitTypeDef Nvic_Value;//定义了NVIC初始化结构体类型的变量
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//配置组优先级和子优先级的级别
	Nvic_Value.NVIC_IRQChannel = RTC_IRQn;//选择了RTC的中断号
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//选择使能该中断
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//选择组优先级的级别为2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//选择子优先级的级别为2
	NVIC_Init(&Nvic_Value);//按照上述配置初始化NVIC

	if(BKP_ReadBackupRegister(BKP_DR10) != 0x9527)//判断是否是第一次操作RTC
	{
		rtc_config(t);//由于是第一次操作RTC,需要配置RTC
		BKP_WriteBackupRegister(BKP_DR10, 0x9527);//把特定值写入特定寄存器中
	}
	else
	{
		RTC_WaitForSynchro();//等待RTC的时钟同步
		RTC_WaitForLastTask();//等待最后一次对RTC寄存器的写操作完成
		RTC_ITConfig(RTC_IT_SEC, ENABLE);//使能RTC的秒中断
		RTC_WaitForLastTask();//等待最后一次对RTC寄存器的写操作完成		
	}
}

void set_time(struct time_st* t)
{
	uint32_t secCount = 0;
	uint16_t i;

	if(t->Y < 1970 || t->Y > 2099)
		return ;
	
	for(i = 1970; i < t->Y; i++)
	{
		if(isLeapYear(i))
			secCount += 31622400;
		else
			secCount += 31536000;
	}

	for (i = 0; i < t->M - 1; i++)
	{
		secCount += ((uint32_t)monthTable[i] * 86400);
		if (isLeapYear(t->Y) && i == 1)
			secCount += 86400;
	}
	secCount += (uint32_t)(t->D - 1) * 86400;    
	secCount += (uint32_t)(t->h) * 3600;
	secCount += (uint32_t)(t->m) * 60;
	secCount += (uint32_t)(t->s);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP, ENABLE);
	PWR_BackupAccessCmd(ENABLE);
	RTC_SetCounter(secCount);
	RTC_WaitForLastTask();
}

void conv_time(struct time_st* t)
{
	uint32_t timeCount = 0;
	uint32_t Count = 0;
	uint16_t tmp = 0;
	
	timeCount = RTC_GetCounter();
	Count = timeCount / 86400;
	t->W = (4 + Count) % 7;
	if(Count != 0)
	{
		tmp = 1970;
		while(Count >= 365)
		{
			if(isLeapYear(tmp))
			{
				if(Count>= 366)
				{
					Count -= 366;
				}
				else
				{
					tmp++;
					break;
				}
			}
			else
			{
					Count -= 365;
			}
			tmp++;
		}
		t->Y = tmp;
		tmp = 0;
		while(Count >= 28)
		{
			if(isLeapYear(t->Y) && tmp == 1)
			{
				if(Count >= 29) 
						Count -= 29;
				else    
						break;
			}
			else
			{
				if(Count >= monthTable[tmp]) 
					Count -= monthTable[tmp];
				else
					break;
			}
			tmp++;
		}
		t->M = tmp + 1;
		t->D = Count + 1;
    }
    Count = timeCount % 86400;
    t->h = Count / 3600;
    t->m = (Count % 3600) / 60;
    t->s = (Count % 3600) % 60;
}

void get_time(struct time_st *t)//获取时间
{
	memcpy(t, &T, sizeof(T));//把全局变量获取的数据转存到形参中
}









