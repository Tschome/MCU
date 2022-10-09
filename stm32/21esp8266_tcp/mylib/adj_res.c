#include "adj_res.h"

void adc_init(void)//初始化GPIO管脚和AD功能
{
	GPIO_InitTypeDef Gpio_Value;
	ADC_InitTypeDef Adc_Value;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_ADC1, ENABLE);
	//通过APB2总线使能GPIOC组和ADC1的时钟
	
	Gpio_Value.GPIO_Mode = GPIO_Mode_AIN;//选择模拟输入功能
	Gpio_Value.GPIO_Pin = GPIO_Pin_0;//选择 0 号管脚
	Gpio_Value.GPIO_Speed = GPIO_Speed_50MHz;//选择50MHz的输出速度
	GPIO_Init(GPIOC, &Gpio_Value);//按照上述配置初始化GPIOC组的管脚
	
	Adc_Value.ADC_ContinuousConvMode = DISABLE;//选择关闭连续转换模式
	Adc_Value.ADC_DataAlign = ADC_DataAlign_Right;//选择数据右对齐的方式
	Adc_Value.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//选择关闭外部出发
	Adc_Value.ADC_Mode = ADC_Mode_Independent;//选择单独的转换模式
	Adc_Value.ADC_NbrOfChannel = 10;//选择了通道10
	Adc_Value.ADC_ScanConvMode = DISABLE;//选择关闭扫描转换模式
	ADC_Init(ADC1, &Adc_Value);//按照上述的配置初始化ADC1

	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_239Cycles5);
	//配置ADC1的通道10
	
	ADC_Cmd(ADC1, ENABLE);//使能ADC1的转换功能
}

void adc_start(void)//开启转换(以软件的方式开启AD转换)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件的方式开启ADC1的转换
}

void adc_wait(void)//等待AD转换结束
{
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//死等的方式等待ADC1转换结束
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);//清除ADC1的转换结束的标志状态
}

int get_adc_value(void)//获取AD转换的结果
{
	return ADC_GetConversionValue(ADC1);//获取ADC1的转换结果,并且以返回值的形式返回
}

void adj_res_init(void)//初始化高精度可调电阻的函数(初始化所使用到的GPIO管脚以及AD功能)
{
	adc_init();//调用初始化的函数
}

int get_adj_res_value(void)//获取AD转换之后的结果
{
	adc_start();//开启AD转换
	adc_wait();//等待AD转换结束
	return get_adc_value();//获取AD转换的结果,并以返回值的形式返回
}







