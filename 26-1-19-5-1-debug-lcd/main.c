#include <REGX52.H>
#include "LCD1602.h"

void main(void){
    LCD_Init();
    while(1){
        LCD_ShowString(1,1,"Hello, World!");
    }
}
