#include "adj_res.h"

void adc_init(void)//��ʼ��GPIO�ܽź�AD����
{
	GPIO_InitTypeDef Gpio_Value;
	ADC_InitTypeDef Adc_Value;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);
	//ͨ��APB2����ʹ��GPIOC���ADC1��ʱ��
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AIN;//ѡ��ģ�����빦��
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//ѡ�� 0 �Źܽ�
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//ѡ��50MHz������ٶ�
	GPIO_Init(GPIOC, &Gpio_Value);//�����������ó�ʼ��GPIOC��Ĺܽ�
	
	Adc_Value.ADC_ContinuousConvMode = DISABLE;//ѡ��ر�����ת��ģʽ
	Adc_Value.ADC_DataAlign = ADC_DataAlign_Right;//ѡ�������Ҷ���ķ�ʽ
	Adc_Value.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//ѡ��ر��ⲿ����
	Adc_Value.ADC_Mode = ADC_Mode_Independent;//ѡ�񵥶���ת��ģʽ
	Adc_Value.ADC_NbrOfChannel = 10;//ѡ����ͨ��10
	Adc_Value.ADC_ScanConvMode = DISABLE;//ѡ��ر�ɨ��ת��ģʽ
	ADC_Init(ADC1, &Adc_Value);//�������������ó�ʼ��ADC1

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
	//����ADC1��ͨ��10
	
	ADC_Cmd(ADC1, ENABLE);//ʹ��ADC1��ת������
}

void adc_start(void)//����ת��(������ķ�ʽ����ADת��)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//����ķ�ʽ����ADC1��ת��
}

void adc_wait(void)//�ȴ�ADת������
{
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//���ȵķ�ʽ�ȴ�ADC1ת������
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);//���ADC1��ת�������ı�־״̬
}

int get_adc_value(void)//��ȡADת���Ľ��
{
	return ADC_GetConversionValue(ADC1);//��ȡADC1��ת�����,�����Է���ֵ����ʽ����
}

void adj_res_init(void)//��ʼ���߾��ȿɵ�����ĺ���(��ʼ����ʹ�õ���GPIO�ܽ��Լ�AD����)
{
	adc_init();//���ó�ʼ���ĺ���
}

int get_adj_res_value(void)//��ȡADת��֮��Ľ��
{
	adc_start();//����ADת��
	adc_wait();//�ȴ�ADת������
	return get_adc_value();//��ȡADת���Ľ��,���Է���ֵ����ʽ����
}







