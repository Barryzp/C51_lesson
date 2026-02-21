#include <REGX52.H>
#include <INTRINS.H>
#include "LCD1602.h"
#include "independent_key.h"

void timer0_init(void) // 1000微秒@11.0592MHz
{
    // AUXR |= 0x80;		//定时器时钟1T模式
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

static unsigned int led_mod = 0;

void main()
{
    P2 = 0xFE;
    timer0_init(); // 初始化定时器0

    while (1)
    {
        unsigned char key_value = independent_key_scan();
        if (key_value != 0)
        {
            if (key_value == 1)
            {
                led_mod = 0;
            }
            else if (key_value == 2)
            {
                led_mod = 1;
            }
        }
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
        if (led_mod == 1)
        {
            P2 = _crol_(P2, 1);
        }
        else if (led_mod == 0)
        {
            P2 = _cror_(P2, 1);
        }
    }
}