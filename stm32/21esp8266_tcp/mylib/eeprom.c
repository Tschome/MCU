#include "eeprom.h"
#include "gpio_iic.h"

void eeprom_init(void)//初始化eeprom的函数
{
	IIC_Init();//初始化IIC实用到的GPIO管脚
}

void eeprom_byte_write(u8 daddr, u8 waddr, u8 data)//按字节来写
{
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr);//发送设备地址
	IIC_Wait_Ack();//等待ACK
	IIC_Send_Byte(waddr);//发送存储空间内部的地址
	IIC_Wait_Ack();//等待ACK
	IIC_Send_Byte(data);//发送数据
	IIC_Wait_Ack();//等待ACK
	IIC_Stop();//产生结束信号
}

void eeprom_page_write(u8 daddr, u8 waddr, u8 *buf, u8 size)//按页来写
{
	u8 i = 0;//i变量为循环变量
	
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr);//发送设备地址 + 写的标志
	IIC_Wait_Ack();//等待ACK
	IIC_Send_Byte(waddr);//发送EEPROM内部存储空间的地址
	IIC_Wait_Ack();
	for(i = 0; i < size; i++)
	{
		IIC_Send_Byte(buf[i]);//发送数据
		IIC_Wait_Ack();//等待ACK
	}
	IIC_Stop();//产生结束信号
}
	
u8 eeprom_cur_addr_read(u8 daddr)//当前地址读
{
	u8 data = 0;
	
	IIC_Start();
	IIC_Send_Byte(daddr | 1);
	IIC_Wait_Ack();
	data = IIC_Recv_Byte(0);
	IIC_Stop();
	
	return data;
}

u8 eeprom_rand_read(u8 daddr, u8 waddr)//随机地址读
{
	u8 data = 0;//data变量用来保存读取到的数据
	
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr);//发送设备地址
	IIC_Wait_Ack();//等待ACK
	IIC_Send_Byte(waddr);//发送存储空间内部的地址
	IIC_Wait_Ack();//等待ACK
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr | 1);//发送设备地址
	IIC_Wait_Ack();//等待ACK
	data = IIC_Recv_Byte(0);//读取数据
	IIC_Stop();//产生结束信号
	
	return data;//把data变量中保存到的数据返回
}

void eeprom_sequ_read(u8 daddr, u8 waddr, u8 *buf, u8 size)//顺序地址读
{
	u8 i = 0;//i变量为循环变量
	
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr);//发送设备地址
	IIC_Wait_Ack();//等待ACK
	IIC_Send_Byte(waddr);//发送EEPROM内部存储空间的地址
	IIC_Wait_Ack();//等待ACK
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr | 1);//发送设备地址 + 读的标志
	IIC_Wait_Ack();//等待ACK
	for(i = 0; i < size; i++)
	{
		if(i == size - 1)
			buf[i] = IIC_Recv_Byte(0);//读取数据不产生ACK
		else
			buf[i] = IIC_Recv_Byte(1);//读取数据产生ACK
	}
	IIC_Stop();//产生结束信号
}











