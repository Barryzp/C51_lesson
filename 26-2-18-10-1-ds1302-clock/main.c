#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"
#include "ds1302.h"


void main()
{
    LCD_Init();
    DS1302_Init();

    LCD_ShowString(1, 3, "-");
    LCD_ShowString(1, 6, "-");

    LCD_ShowString(2, 3, ":");
    LCD_ShowString(2, 6, ":");
    // (1)
    // DS1302_Write_Byte(0x8E, 0x00); // 关闭写保护(现象是读出了一个大于59的数)

    // LCD_ShowString(1, 1, "RTCB");
    // DS1302_Write_Byte(0x80, 0x55);

    // (4)
    DS1302_Set_Time();

    while (1)
    {
        // (1) DS1302的数据是以BCD码的形式存储的，直接进行十进制显示就容易出现跳变
        // second = DS1302_Read_Byte(0x81);
        // min = DS1302_Read_Byte(0x83);
        // // (2)通过十六进制数显示即可
        // // LCD_ShowHexNum(2, 1, second, 3);
        // // (3)也可以通过计算的方式把BCD码转换成十进制数显示
        // LCD_ShowNum(2, 1, second / 16 * 10 + second % 16, 2);
		// LCD_ShowNum(2, 3, min / 16 * 10 + min % 16, 2);

        // (4)
        DS1302_Get_Time();
        LCD_ShowNum(1, 1, date_time[0], 2);
        LCD_ShowNum(1, 4, date_time[1], 2);
        LCD_ShowNum(1, 7, date_time[2], 2);
        LCD_ShowNum(2, 1, date_time[3], 2);
        LCD_ShowNum(2, 4, date_time[4], 2);
        LCD_ShowNum(2, 7, date_time[5], 2);
    }
}