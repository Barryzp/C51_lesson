#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"
#include "independent_key.h"

// REGX52.H中已经定义了sfr类型的特殊功能寄存器，但没有定义AUXR寄存器，所以我们需要自己定义它
sfr AUXR = 0x8E;

static unsigned int led_mod = 0;

static unsigned char t_hour = 23;
static unsigned char t_min = 59;
static unsigned char t_sec = 58;


void timer0_init(void) // 1000微秒@11.0592MHz
{
    AUXR |= 0x80;		//定时器时钟1T模式，定时器默认的是12T模式，改为1T模式后，定时器的计数频率将提高12倍
    TMOD &= 0xF0; // 设置定时器模式
    TL0 = 0xCD;   // 设置定时初值
    TH0 = 0xD4;   // 设置定时初值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时

    // 中断设置
    ET0 = 1; // 使能定时器0中断
    EA = 1;  // 使能总中断

    // 配置优先级，目前只有一个中断源可以不写，默认最低级0，为了完整还是写上
    PT0 = 0; // 定时器0中断优先级低
}

void main() {

    LCD_Init();
    timer0_init(); // 初始化定时器0
    LCD_ShowString(1, 1, "Time:");
	LCD_ShowString(2, 1, "  :  :");
    while (1)
    {
        LCD_ShowNum(2, 1, t_hour, 2);
        LCD_ShowNum(2, 4, t_min, 2);
        LCD_ShowNum(2, 7, t_sec, 2);
    }
}

void timer0_isr(void) interrupt 1
{
    static unsigned int t_count = 0;

    // 重新装载定时初值
    TL0 = 0xCD; // 设置定时初值
    TH0 = 0xD4; // 设置定时初值

    t_count++;
    if (t_count >= 1000) // 500ms到达
    {
        t_count = 0;
        t_sec++;
        if (t_sec >= 60)
        {
            t_sec = 0;
            t_min++;
            if (t_min >= 60)
            {
                t_min = 0;
                t_hour++;
                if (t_hour >= 24)
                {
                    t_hour = 0;
                }
            }
        }
    }
}