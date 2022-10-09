#include "rtc.h"
#include "string.h"

const uint8_t monthTable[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//���ڴ洢ÿ���µ�����(2�·���Ҫ+1)
static struct time_st T;//�洢ÿһ�λ�ȡ������������ʱ����

static uint8_t isLeapYear(uint16_t y)   
{
	return (((!(y % 4)) && (y % 100)) || (!(y % 400)));
}

void RTC_IRQHandler(void)//RTC���жϴ�����
{
	if(RTC_GetITStatus(RTC_IT_SEC) == SET)//�ж��Ƿ�����RTC�����жϴ������ж�
	{
		conv_time(&T);//�ѻ�ȡ���ļ���ֵת�������������浽ȫ�ֱ�����
		RTC_ClearITPendingBit(RTC_IT_SEC);//���RTC���жϵ��жϱ�־
	}
}

void rtc_config(struct time_st *t)//����RTC
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP | RCC_APB1Periph_PWR, ENABLE);
	//ͨ��APB1����ʹ��BKP��PWR��ʱ��(Ϊ�˿���д����)
	
	PWR_BackupAccessCmd(ENABLE);//ͨ��PWRʹ�ܺ������д����
	BKP_DeInit();//��λ������
	RCC_LSEConfig(RCC_LSE_ON);//ͨ��RCC����LSEʱ��Դ
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);//�����ȵķ�ʽ�ȴ�LSE�ȶ�
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);//ͨ��RCCΪRTCѡ����LSE�ṩʱ��Դ
	RCC_RTCCLKCmd(ENABLE);//ͨ��RCCʹ��RTC��ʱ��
	RTC_WaitForSynchro();//�ȴ�RTCʱ��ͬ��
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ���д���������
	RTC_ITConfig(RTC_IT_SEC, ENABLE);//ʹ��RTC�����ж�
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ���д���������
	RTC_EnterConfigMode();//����RTC������ģʽ
	RTC_SetPrescaler(32767);//����RTC��Ԥ��Ƶֵ
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ���д���������
	set_time(t);//����ʱ��(���ü���ֵ)
	RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ���д���������
	RTC_ExitConfigMode();//�˳�RTC������ģʽ
}

void rtc_init(struct time_st *t)//��ʼ��RTC
{
	NVIC_InitTypeDef Nvic_Value;//������NVIC��ʼ���ṹ�����͵ı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���������ȼ��������ȼ��ļ���
	Nvic_Value.NVIC_IRQChannel = RTC_IRQn;//ѡ����RTC���жϺ�
	Nvic_Value.NVIC_IRQChannelCmd = ENABLE;//ѡ��ʹ�ܸ��ж�
	Nvic_Value.NVIC_IRQChannelPreemptionPriority = 2;//ѡ�������ȼ��ļ���Ϊ2
	Nvic_Value.NVIC_IRQChannelSubPriority = 2;//ѡ�������ȼ��ļ���Ϊ2
	NVIC_Init(&Nvic_Value);//�����������ó�ʼ��NVIC

	if(BKP_ReadBackupRegister(BKP_DR10) != 0x9527)//�ж��Ƿ��ǵ�һ�β���RTC
	{
		rtc_config(t);//�����ǵ�һ�β���RTC,��Ҫ����RTC
		BKP_WriteBackupRegister(BKP_DR10, 0x9527);//���ض�ֵд���ض��Ĵ�����
	}
	else
	{
		RTC_WaitForSynchro();//�ȴ�RTC��ʱ��ͬ��
		RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������
		RTC_ITConfig(RTC_IT_SEC, ENABLE);//ʹ��RTC�����ж�
		RTC_WaitForLastTask();//�ȴ����һ�ζ�RTC�Ĵ�����д�������		
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

void get_time(struct time_st *t)//��ȡʱ��
{
	memcpy(t, &T, sizeof(T));//��ȫ�ֱ�����ȡ������ת�浽�β���
}









