#include "eeprom.h"
#include "gpio_iic.h"

void eeprom_init(void)//初始化的函数(可以直接调用IIC_Init初始化函数)
{
	IIC_Init();//初始化IIC所使用到的GPIO管脚
}

void eeprom_byte_write(u8 daddr, u8 waddr, u8 data)//按字节来写
{
	IIC_Start();//产生开始信号
	IIC_Send_Byte(daddr);//发送设备地址0xA0
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(waddr);//发送内部存储空间的地址
	while(IIC_Wait_Ack());//等待ACK
	IIC_Send_Byte(data);//发送数据
	while(IIC_Wait_Ack());//等待ACK
	IIC_Stop();//产生结束信号
}

void eeprom_page_write(u8 daddr, u8 waddr, u8 *buf, u8 size)//按页来写
{
}

u8 eeprom_cur_addr_read(u8 daddr)//当前地址读
{
}

u8 eeprom_rand_addr_read(u8 daddr, u8 waddr)//随机地址读
{
}

void eeprom_sequ_read(u8 daddr, u8 waddr, u8 *buf, u8 size)//顺序地址读
{
}






