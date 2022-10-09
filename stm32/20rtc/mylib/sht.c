#include "sht.h"//IIC总线
#include "gpio_iic.h"
#include "delay.h"

void sht_init(void)//初始化SHT30的函数(初始化管脚)
{
	IIC_Init();//初始化SHT30所使用的GPIO管脚
}

void sht_write_mode(void)//配置SHT30的采样频率
{
	IIC_Start();//产生开始信号
	IIC_Send_Byte(SLAVE_ADDR);//发送设备地址 + 写的标志
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH >> 8);//发送采样指令的高字节
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(PERIODIC_MODE_HIGH & 0xFF);//发送采样指令的低字节
	while(IIC_Wait_Ack());//等待ACK
	IIC_Stop();//产生结束信号
}

void sht_write_read_cmd(void)//发送读取SHT30数据的指令
{
	IIC_Start();//产生开始信号
	IIC_Send_Byte(SLAVE_ADDR);//发送设备地址 + 写的标志
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE >> 8);//发送读取数据的指令的高字节
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(READOUT_PERIODIC_MODE & 0xFF);//发送读取数据的指令的低字节
	while(IIC_Wait_Ack());//等待ACK
}

void sht_read_data(double sht_data[2])//读取SHT30传感器的数据
{
	u8 i = 0;//循环变量
	u8 data[6] = {0};//用于存储从SHT30中直接读出的数据
	u16 temp = 0;//用来存储温度的16bit数据
	u16 hum = 0;//用来存储湿度的16bit数据
	
	IIC_Start();//产生开始信号
	IIC_Send_Byte(SLAVE_ADDR | 0x01);//发送设备地址 + 读的标志
	while(IIC_Wait_Ack());//等待ACK
	for(i = 0; i < 6; i++)
	{
		if(i == 5)
			data[i] = IIC_Recv_Byte(0);//读取数据并且不产生ACK
		else
			data[i] = IIC_Recv_Byte(1);//读取数据并且产生ACK
	}
	IIC_Stop();//产生结束信号
	
	temp = data[0] & 0xFF;//获取温度的高字节数据
	temp <<= 8;//把之前获取的数据移到高字节
	temp |= data[1] & 0xFF;//获取温度的低字节数据
	hum = data[3] & 0xFF;//获取湿度的高字节数据
	hum <<= 8;//把之前获取的数据移到高字节
	hum |= data[4] & 0xFF;//获取湿度的低字节数据
	
	sht_data[0] = (double)(-45 + 175 * (double)(temp) / 65535);
	sht_data[1] = (double)(100 * (double)(hum) / 65535);
}







