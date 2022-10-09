#include "sht.h"
#include "gpio_iic.h"
#include "delay.h"
#include "led.h"

void sht_init(void)//初始化的函数
{
	IIC_Init();//初始化SHT30所使用到的GPIO管脚
}

void sht_write_mode(void)//配置SHT30传感器内部采样速率
{
	IIC_Start();//产生开始信号
	IIC_Send_Byte(SLAVE_ADDR);//发送设备地址
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH >> 8);//发送采样命令的高字节
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH & 0xFF);//发送采样命令的低字节
	while(IIC_Wait_Ack());//等待ACK
	IIC_Stop();//产生结束信号
	delay_ms(5);//5毫秒的延时
}

void sht_write_read_cmd(void)//发送读取SHT30采集数据的命令
{
	IIC_Start();//产生开始信号
	IIC_Send_Byte(SLAVE_ADDR);//发送设备地址
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE >> 8);//发送获取数据命令的高字节
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE & 0xFF);//发送获取数据命令的低字节
	while(IIC_Wait_Ack());//等待ACK
}

void sht_read_data(double sht_data[2])//读取SHT30采集到的数据
{
	u8 buf[6] = {0};//存储SHT30读出的数据
	u16 Temp = 0;
	u16 Hum = 0;
	u8 i = 0;//i变量为循环变量
	
	IIC_Start();//产生开始信号
	IIC_Send_Byte(SLAVE_ADDR | 0x01);//发送设备地址 + 读的标志
	delay_us(5);//5微秒的延时
	while(IIC_Wait_Ack());//等待ACK
	for(i = 0; i < 6; i++)
	{
		if(i == 5)
			buf[i] = IIC_Recv_Byte(0);//读数据，不需要产生ACK
		else
			buf[i] = IIC_Recv_Byte(1);//读数据，产生ACK
	}
	IIC_Stop();
	//////////////////////////////////转换数据
	
	Temp = buf[0] & 0xFF;
	Temp <<= 8;
	Temp |= buf[1] & 0xFF;
	Hum = buf[3] & 0xFF;
	Hum <<= 8;
	Hum |= buf[4] & 0xFF;
	
	sht_data[0] = (double)(-45 + 175 * (double)(Temp) / 65535);
	sht_data[1] = (double)(100 * (double)(Hum) / 65535);
}







