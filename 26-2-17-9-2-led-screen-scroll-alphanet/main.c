#include "lcd_screen.h"

unsigned char ani[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0xFF,0x7C,0x1C,0x08,0xFF,0x7F,0x00,0xFF,
    0x5B,0x49,0xC9,0xC9,0x00,0xFC,0x07,0x1E,
    0x1C,0x07,0xFE,0x98,0x00,0xFF,0x41,0x4D,
    0x4D,0x7F,0x00,0x7F,0x43,0x43,0x42,0x42,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

void main() {
    unsigned char i, offset = 0, counter = 0;

    matrix_led_init(); // 初始化LED矩阵

    while (1) {
        // // 显示前面部分
        // matrix_led_show_column(0, ani[0]); // Show pattern 0x3C on column 0
        // matrix_led_show_column(1, ani[1]); // Show pattern 0x42 on column 1
        // matrix_led_show_column(2, ani[2]); // Show pattern 0xA5 on column 2
        // matrix_led_show_column(3, ani[3]); // Show pattern 0x
        // matrix_led_show_column(4, ani[4]); // Show pattern 0xA5 on column 4
        // matrix_led_show_column(5, ani[5]); // Show pattern 0x
        // matrix_led_show_column(6, ani[6]); // Show pattern 0x42 on column 6
        // matrix_led_show_column(7, ani[7]); // Show pattern 0x3C on column 7
        for (i = 0; i < 8; i++) {
            matrix_led_show_column(i, ani[offset + i]);
        }

        counter++;
        if (counter > 10) { // 每10次刷新后滚动一次
            counter = 0;
            offset++;
            if (offset > 48) { // 当偏移超过动画数组长度时重置
                offset = 0;
            }
        }
    }
}
