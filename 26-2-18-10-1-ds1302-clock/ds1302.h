#ifndef __DS1302_H__
#define __DS1302_H__

#include <REGX52.H>

// 宏定义DS1302寄存器地址
#define DS1302_SECONDS_REG 0x80
#define DS1302_MINUTES_REG 0x82
#define DS1302_HOURS_REG 0x84
#define DS1302_DATE_REG 0x86
#define DS1302_MONTH_REG 0x88
#define DS1302_DAY_REG 0x8A
#define DS1302_YEAR_REG 0x8C
#define DS1302_CONTROL_REG 0x8E

// 定义全局变量(需要加extern修饰符，表示这个变量在别的文件中定义了，在这里只是声明一下)
extern unsigned char date_time[]; // 年月日时分秒，星期不设置

sbit DS1302_SCLK = P3 ^ 6;
sbit DS1302_CE = P3 ^ 5;
sbit DS1302_IO = P3 ^ 4;

void DS1302_Init();
void DS1302_Write_Byte(unsigned char command, unsigned char byte);
unsigned char DS1302_Read_Byte(unsigned char command);

void DS1302_Set_Time();
void DS1302_Get_Time();
unsigned char BCD2DEC(unsigned char bcd);

#endif