#include <REGX52.H>
#include "LCD1602.h"
#include "matrix_keyboard.h"

void main()
{
    unsigned char key = 0;
    LCD_Init();
    LCD_ShowString(1, 1, "Hello, World!");
    while (1)
    {
        key = matrix_key_scan();
        // 第一种方式
        // if (key != 0) {
        //     LCD_ShowString(1, 1, "Key Pressed: ");
        //     LCD_ShowNum(1, 14, key, 2);
        //     // Simple delay to allow user to see the key press（先暂停一下让我们可以看到显示）
        //     delay_for_ms(1000);
        // }else{
        //     LCD_ShowString(1, 1, "No Key Pressed.");
        // }
        // 第二种方式
        if (key)
        {
            LCD_ShowString(1, 1, "Key Pressed: ");
            LCD_ShowNum(1, 14, key, 2);
        }
    }
}