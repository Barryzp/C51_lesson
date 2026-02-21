#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"
#include "ds1302.h"
#include "independent_key.h"
#include "timer0.h"

unsigned char key_value = 0, mode = 0; // mode: 0-正常显示，1-设置年，2-设置月，3-设置日，4-设置时，5-设置分，6-设置秒
unsigned char time_setting_index = 0;  // 0-年，1-月，2-日，3-时，4-分，5-秒
unsigned char date_ani_flag = 0;       // 时间设置的动画标志

void Refresh_Time()
{
    LCD_ShowNum(1, 1, date_time[0], 2);
    LCD_ShowNum(1, 4, date_time[1], 2);
    LCD_ShowNum(1, 7, date_time[2], 2);
    LCD_ShowNum(2, 1, date_time[3], 2);
    LCD_ShowNum(2, 4, date_time[4], 2);
    LCD_ShowNum(2, 7, date_time[5], 2);
}

void Show_Time()
{
    DS1302_Get_Time();
    Refresh_Time();
}

unsigned char Get_Max_Day()
{
    unsigned char max_day;
    // 判断闰年和不同月份的天数
    unsigned char month = date_time[1];
    unsigned char year = date_time[0] + 2000; // 假设年份是2000年以后的两位数
    if (month == 2)                           // 二月
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // 闰年
        {
            max_day = 29;
        }
        else
        {
            max_day = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) // 小月
    {
        max_day = 30;
    }
    else // 大月
    {
        max_day = 31;
    }
    return max_day;
}

void Time_Set(unsigned char operation)
{
    unsigned char temp, month, year, max_day;
    switch (time_setting_index)
    {
    case 0:
        temp = date_time[0];         // 保存当前设置项的值，万一用户设置过程中按错了需要恢复
        operation ? temp++ : temp--; // 根据操作类型增加或减少
        if (temp > 99)
        {
            if (temp == 255)
                temp = 99; // 因为temp是unsigned char，所以当它小于0时会变成255
            else
                temp = 0;
        }
        date_time[0] = temp; // 更新设置项的值
        break;
    case 1:
        temp = date_time[1];
        operation ? temp++ : temp--;
        if (temp > 12)
            temp = 1;
        if (temp < 1)
            temp = 12;
        date_time[1] = temp;
        break;
    case 2:
        temp = date_time[2];
        max_day = Get_Max_Day();

        if (operation)
        {
            temp++;
            if (temp > max_day)
            {
                temp = 1;
            }
        }else{
            if (temp == 1)
            {
                temp = max_day;
            }else temp--;
        }
        date_time[2] = temp;
        break;
    case 3:
        temp = date_time[3];
        operation ? temp++ : temp--;
        if (temp > 23)
            temp = 0;
        if (temp < 0)
            temp = 23;
        date_time[3] = temp;
        break;
    case 4:
        temp = date_time[4];
        operation ? temp++ : temp--;
        if (temp > 59)
            temp = 0;
        if (temp < 0)
            temp = 59;
        date_time[4] = temp;
        break;
    case 5:
        temp = date_time[5];
        operation ? temp++ : temp--;
        if (temp > 59)
            temp = 0;
        if (temp < 0)
            temp = 59;
        date_time[5] = temp;
        break;
    default:
        break;
    }

    // 最后判断设置了月份和年份时每个月的最大天数，避免用户设置了不合法的日期
    // 判断闰年和不同月份的天数
    month = date_time[1];
    year = date_time[0] + 2000; // 假设年份是2000年以后的两位数
    if (month == 2)             // 二月
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // 闰年
        {
            max_day = 29;
        }
        else
        {
            max_day = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) // 小月
    {
        max_day = 30;
    }
    else // 大月
    {
        max_day = 31;
    }
    
    if (date_time[2] > max_day)
    {
        date_time[2] = max_day; // 如果用户设置的日期超过了当月最大天数，就自动调整为最大天数
    }

    Refresh_Time(); // 刷新显示
}

void Time_Set_Ani()
{
    if (mode == 0)
        return; // 只有在设置模式下才执行动画

    // 需要有一个显示的动画
    switch (time_setting_index)
    {
    case 0:
        date_ani_flag ? LCD_ShowString(1, 1, "  ") : LCD_ShowNum(1, 1, date_time[0], 2);
        break;
    case 1:
        date_ani_flag ? LCD_ShowString(1, 4, "  ") : LCD_ShowNum(1, 4, date_time[1], 2);
        break;
    case 2:
        date_ani_flag ? LCD_ShowString(1, 7, "  ") : LCD_ShowNum(1, 7, date_time[2], 2);
        break;
    case 3:
        date_ani_flag ? LCD_ShowString(2, 1, "  ") : LCD_ShowNum(2, 1, date_time[3], 2);
        break;
    case 4:
        date_ani_flag ? LCD_ShowString(2, 4, "  ") : LCD_ShowNum(2, 4, date_time[4], 2);
        break;
    case 5:
        date_ani_flag ? LCD_ShowString(2, 7, "  ") : LCD_ShowNum(2, 7, date_time[5], 2);
        break;
    default:
        break;
    }
}

void main()
{
    unsigned char key_value;
    LCD_Init();
    DS1302_Init();
    timer0_init();

    LCD_ShowString(1, 3, "-");
    LCD_ShowString(1, 6, "-");
    LCD_ShowString(2, 3, ":");
    LCD_ShowString(2, 6, ":");

    DS1302_Set_Time();

    while (1)
    {
        key_value = independent_key_scan();
        if (mode == 1)
        {
            switch (key_value)
            {            
                case 1:
                mode = 0;
                time_setting_index = 0; // 退出设置模式时重置设置项索引，避免下次进入设置模式时从上次的设置项开始
                date_ani_flag = 0; // 退出设置模式时关闭动画
                DS1302_Set_Time(); // 退出设置模式时把设置的时间写入DS1302
                break;
            case 2:
                Time_Set(0); // 减少时间
                break;
            case 3:
                Time_Set(1); // 增加时间
                break;
            case 4:                                                // 切换设置项目
                time_setting_index = (time_setting_index + 1) % 6; // 循环切换设置项
                Refresh_Time();                                    // 切换设置项时刷新显示，避免动画残影
                break;
            default:
                break;
            }
        }else{
            if (key_value == 1) mode = 1; // 进入设置模式
            Show_Time();
        }

        Time_Set_Ani(); // 执行时间设置动画
        LCD_ShowNum(2, 10, date_ani_flag, 1);
    }
}

void timer0_isr(void) interrupt 1
{
    static unsigned int t_count = 0;

    // 重新装载定时初值
    TL0 = 0xCD; // 设置定时初值
    TH0 = 0xD4; // 设置定时初值

    t_count++;
    if (t_count >= 500) // 500ms到达
    {
        t_count = 0;
        if (mode == 1)
        {
            date_ani_flag = !date_ani_flag; // 切换动画标志
        }
    }
}