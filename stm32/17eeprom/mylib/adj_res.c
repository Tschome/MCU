#include "adj_res.h"

void adj_res_init(void)//��ʼ���߾��ȿɵ�����ĺ���
{
	GPIO_InitTypeDef Gpio_Value;//������GPIO��ʼ���ṹ�����͵ı���
	ADC_InitTypeDef Adc_Value;//������ADC��ʼ���ṹ�����͵ı���
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOC, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ADC1��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AIN;//ѡ����ģ������ģʽ
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//ѡ����0�Źܽ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�

	Adc_Value.ADC_ContinuousConvMode = DISABLE;//ѡ���˹ر�����ת��ģʽ
	Adc_Value.ADC_DataAlign = ADC_DataAlign_Right;//ѡ���������Ҷ���ķ�ʽ
	Adc_Value.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ѡ���˹ر��ⲿ����
	Adc_Value.ADC_Mode = ADC_Mode_Independent;//ѡ���˵�����ת��ģʽ
	Adc_Value.ADC_NbrOfChannel = 10;//ѡ����10��ͨ��
	Adc_Value.ADC_ScanConvMode = DISABLE;//ѡ���˹ر�ɨ��ģʽ
	ADC_Init(ADC1, &Adc_Value);//�����������ó�ʼ��ADC1
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
	//����ADC1��ͨ��10
	
	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1��ת������
}

int get_adj_res_value(void)//��ȡADת��֮��Ľ��
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//������ķ�ʽ����ADC1��ת��
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	//�����ȵķ�ʽ�ȴ�ADC1ת������
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);//���ADC1��ת��������־
	return ADC_GetConversionValue(ADC1);
	//��ȡADC1��ת��������Է���ֵ����ʽ����
}






