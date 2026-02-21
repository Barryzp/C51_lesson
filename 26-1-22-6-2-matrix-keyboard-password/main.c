#include <REGX52.H>
#include "LCD1602.h"
#include "matrix_keyboard.h"

void main()
{
    unsigned int password = 9527;

    unsigned int input = 0;
    unsigned char key = 0;
    LCD_Init();
    LCD_ShowString(1, 1, "Password: ");
    while (1)
    {
        key = matrix_key_scan();
        if (key)
        {
            // (input / 1000)==0是为了防止超出四位数还在输入
            if (key <= 10 && (input / 1000)==0)
            {
                input = input * 10;
                // 密码左移，作为首位
                input += key % 10;
            }
            
            LCD_ShowNum(2, 1, input, 4);
            // 判断密码
            if (key == 11)
            {
                if (input == password)
                {
                    LCD_ShowString(2, 1, "Correct!");
                    delay_for_ms(500);
                    input = 0;
                    LCD_ShowString(2, 1, "         ");
                    LCD_ShowNum(2, 1, input, 4);
                }
                else
                {
                    LCD_ShowString(2, 1, "Wrong!");
                    delay_for_ms(500);
                    input = 0;
                    LCD_ShowString(2, 1, "       ");
                    LCD_ShowNum(2, 1, input, 4);
                }
            }

            // 清除
            if (key == 12){
                input = 0;
                LCD_ShowNum(2, 1, input, 4);
            }
        }
    }
}