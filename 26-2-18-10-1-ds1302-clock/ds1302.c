#include "ds1302.h"

// 全局变量定义
unsigned char date_time[] = {26, 2, 21, 15, 13, 55, 6}; // 年月日时分秒，星期不设置

void DS1302_Init(){
	DS1302_CE = 0;
	DS1302_SCLK = 0;
}

void DS1302_Write_Byte(unsigned char command, unsigned char byte){

	// 还是一步一步来介绍地进行演示，最后再合并成为一个循环
	unsigned char i;
	DS1302_CE = 1;

	// DS1302写入命令字和数据字都是低位先写入
	for(i = 0; i < 8; i++){
		DS1302_IO = command&(0x01<<i); // 或者(0x01 << i) & command
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	for(i = 0; i < 8; i++){
		DS1302_IO = byte&(0x01<<i); // 或者(0x01 << i) & byte
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
	}
	DS1302_CE = 0;
}

unsigned char DS1302_Read_Byte(unsigned char command){
	unsigned char i;
	unsigned char byte = 0x00;

	command |= 0x01; // 读命令的最低位是1，写命令的最低位是0，所以直接把最低位置1就好了

	DS1302_CE = 1;

	// DS1302写入命令字和数据字都是低位先写入
	for(i = 0; i < 8; i++){
		DS1302_IO = command&(0x01<<i); // 或者(0x01 << i) & command
		DS1302_SCLK = 0;
		DS1302_SCLK = 1;
	}

	// 读取的时候波形会少一个，也就是读取完命令字后就会直接读取数据字了，所以锁存的上升沿和下降沿的顺序反了一下
	for(i = 0; i < 8; i++){
		DS1302_SCLK = 1;
		DS1302_SCLK = 0;
		if (DS1302_IO)
		{
			byte |= (0x01 << i);
		}
	}
	DS1302_CE = 0;
	DS1302_IO = 0; // 读取完数据后把IO口拉低，防止对DS1302造成干扰
	return byte;
}

void DS1302_Set_Time(){
    DS1302_Write_Byte(DS1302_CONTROL_REG, 0x00); // 关闭写保护
    DS1302_Write_Byte(DS1302_YEAR_REG, date_time[0] / 10 * 16 + date_time[0] % 10); // 年
    DS1302_Write_Byte(DS1302_MONTH_REG, date_time[1] / 10 * 16 + date_time[1] % 10); // 月
    DS1302_Write_Byte(DS1302_DATE_REG, date_time[2] / 10 * 16 + date_time[2] % 10); // 日
    DS1302_Write_Byte(DS1302_HOURS_REG, date_time[3] / 10 * 16 + date_time[3] % 10); // 时
    DS1302_Write_Byte(DS1302_MINUTES_REG, date_time[4] / 10 * 16 + date_time[4] % 10); // 分
    DS1302_Write_Byte(DS1302_SECONDS_REG, date_time[5] / 10 * 16 + date_time[5] % 10); // 秒
    DS1302_Write_Byte(DS1302_DAY_REG, date_time[6]); // 星期
    DS1302_Write_Byte(DS1302_CONTROL_REG, 0x80); // 开启写保护
}

unsigned char BCD2DEC(unsigned char bcd){
    return bcd / 16 * 10 + bcd % 16;
}

void DS1302_Get_Time(){
    date_time[0] = BCD2DEC(DS1302_Read_Byte(DS1302_YEAR_REG));
    date_time[1] = BCD2DEC(DS1302_Read_Byte(DS1302_MONTH_REG));
    date_time[2] = BCD2DEC(DS1302_Read_Byte(DS1302_DATE_REG));
    date_time[3] = BCD2DEC(DS1302_Read_Byte(DS1302_HOURS_REG));
    date_time[4] = BCD2DEC(DS1302_Read_Byte(DS1302_MINUTES_REG));
    date_time[5] = BCD2DEC(DS1302_Read_Byte(DS1302_SECONDS_REG));
    date_time[6] = DS1302_Read_Byte(DS1302_DAY_REG);
}