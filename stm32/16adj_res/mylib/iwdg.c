#include "iwdg.h"

void iwdg_init(int ms)//��ʼ���ĺ���(�����ڲ�����Ԥ��Ƶֵ����װ��ֵ)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//������PR�Ĵ�����RLR�Ĵ�����д����
	IWDG_SetPrescaler(IWDG_Prescaler_64);//ѡ����64��Ƶ ʱ��Ƶ�� 40KHz/64=625Hz
	IWDG_SetReload(ms);//������װ��ֵ
	IWDG_ReloadCounter();//ι��(����װ��ֵ���ص���������)
	IWDG_Enable();//�������Ź�
}

void iwdg_feed_dog(void)//ι���Ĳ���
{
	IWDG_ReloadCounter();//ι��(����װ��ֵ���ص���������)	
}





