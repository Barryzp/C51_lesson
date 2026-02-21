#include "matrix_keyboard.h"

// Placeholder function for matrix keyboard scanning
unsigned char matrix_key_scan() {

    unsigned char key = 0; // No key pressed

    // 都设置为高电平
    P1 = 0xff; // Set all rows high

    P1_3 = 0;  //第一列设置为低电平，检测第一列按键的按下信号
    if (P1_7 == 0) //检测第一行按键
    {
        delay_for_ms(20); //消抖
        while (P1_7 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 1;
    }
    else if (P1_6 == 0) //检测第二行按键
    {
        delay_for_ms(20); //消抖
        while (P1_6 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 5;
    }
    else if (P1_5 == 0) //检测第三行按键
    {
        delay_for_ms(20); //消抖
        while (P1_5 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 9;
    }
    else if (P1_4 == 0) //检测第四行按键
    {
        delay_for_ms(20); //消抖
        while (P1_4 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 13;
    }
    
    // 都设置为高电平
    P1 = 0xff; // Set all rows high
    P1_2 = 0;  //第二列设置为低电平，检测第二列按键的按下信号
    if (P1_7 == 0) //检测第一行按键
    {
        delay_for_ms(20); //消抖
        while (P1_7 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 2;
    }
    else if (P1_6 == 0) //检测第二行按键
    {
        delay_for_ms(20); //消抖
        while (P1_6 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 6;
    }
    else if (P1_5 == 0) //检测第三行按键
    {
        delay_for_ms(20); //消抖
        while (P1_5 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 10;
    }
    else if (P1_4 == 0) //检测第四行按键
    {
        delay_for_ms(20); //消抖
        while (P1_4 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 14;
    }

    // 都设置为高电平
    P1 = 0xff; // Set all rows high
    P1_1 = 0;  //第三列设置为低电平，检测第三列按键的按下信号
    if (P1_7 == 0) //检测第一行按键
    {
        delay_for_ms(20); //消抖
        while (P1_7 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 3;
    }
    else if (P1_6 == 0) //检测第二行按键
    {
        delay_for_ms(20); //消抖
        while (P1_6 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 7;
    }
    else if (P1_5 == 0) //检测第三行按键
    {
        delay_for_ms(20); //消抖
        while (P1_5 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 11;
    }
    else if (P1_4 == 0) //检测第四行按键
    {
        delay_for_ms(20); //消抖
        while (P1_4 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 15;
    }

    // 都设置为高电平
    P1 = 0xff; // Set all rows high
    P1_0 = 0;  //第四列设置为低电平，检测第四列按键的按下信号
    if (P1_7 == 0) //检测第一行按键
    {
        delay_for_ms(20); //消抖
        while (P1_7 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 4;
    }
    else if (P1_6 == 0) //检测第二行按键
    {
        delay_for_ms(20); //消抖
        while (P1_6 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 8;
    }
    else if (P1_5 == 0) //检测第三行按键
    {
        delay_for_ms(20); //消抖
        while (P1_5 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 12;
    }
    else if (P1_4 == 0) //检测第四行按键
    {
        delay_for_ms(20); //消抖
        while (P1_4 == 0); //等待按键释放
        delay_for_ms(20); //消抖
        key = 16;
    }

    return key;
}