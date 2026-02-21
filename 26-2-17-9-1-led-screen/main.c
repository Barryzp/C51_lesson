#include <REGX52.H>
#include "delay.h"

sbit RCK = P3^5; // 74HC595 RCLK pin (latch pin)
sbit SCK = P3^6; // 74HC595 SRCLK pin (shift clock pin)
sbit SER = P3^4; // 74HC595 SER pin (serial data input pin)

#define LED_MATRIX_PORT P0 // Define the port connected to the LED matrix

// 演示如何将一个字节的数据写入74HC595移位寄存器
void test_write_byte_74595(unsigned char byte) {
    SER&=0x80; //取第8位数据，并将SER的其他位清零，非0即1
    SCK = 1; //上升沿将数据移入74HC595的移位寄存器
    SCK = 0; //下降沿准备下一位数据的输入

    // 继续移次高位就是第7位数据，依次类推
    SER&=0x40; //取第7位数据，并将SER的其他位清零，非0即1
    SCK = 1; //上升沿将数据移入74HC595的移位寄存器
    SCK = 0; //下降沿准备下一位数据的输入

    // 继续移次高位就是第6位数据，依次类推
    // ... 
}

void write_byte_74595(unsigned char byte) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        SER = (byte >> (7 - i)) & 0x01; // 取当前位数据，并将SER的其他位清零，非0即1，代码等价于SER = (byte & (0x80 >> i)) ? 1 : 0;
        SCK = 1; // 上升沿将数据移入74HC595的移位寄存器
        SCK = 0; // 下降沿准备下一位数据的输入
    }
    RCK = 1; // 锁存数据到输出端
    RCK = 0; // 准备下一次数据输入
}

// 显示一个字节的数据在LED矩阵的指定列上
// column: 0-7,从左到右依次对应LED矩阵的列, byte: 8位数据，每位对应LED矩阵的一行，1表示点亮，0表示熄灭
void matrix_led_show_column(unsigned char column, unsigned char byte){
    write_byte_74595(byte); // 将行数据写入74HC595, data是关键字，不能用作变量名
    LED_MATRIX_PORT = ~(0x80 >> column); // 选择当前列，其他列保持高电平,因为74HC595的输出是低电平有效

    delay_for_ms(1); // 延时，保持显示稳定
    LED_MATRIX_PORT = 0xFF; // 清除显示，准备下一次显示
}

void main() {

    SCK = 0; // Initialize shift clock to low
    RCK = 0; // Initialize latch clock to low

    // matrix_led_show_column(7, 0xaa); // Example: Show pattern 0xAA on column 0

    while (1) {
        // region 显示一个简单的斜线
        // matrix_led_show_column(0, 0x01); // Show pattern 0x01 on column 0
        // matrix_led_show_column(1, 0x02); // Show pattern 0x 02 on column 1
        // matrix_led_show_column(2, 0x04); // Show pattern 0x
        // matrix_led_show_column(3, 0x08); // Show pattern 0x08 on column 3
        // matrix_led_show_column(4, 0x10); // Show pattern 0x
        // matrix_led_show_column(5, 0x20); // Show pattern 0x20 on column 5
        // matrix_led_show_column(6, 0x40); // Show pattern 0x40 on column 6
        // matrix_led_show_column(7, 0x80); // Show pattern 0x
        // endregion

        // 显示一个笑脸
        matrix_led_show_column(0, 0x3C); // Show pattern 0x3C on column 0
        matrix_led_show_column(1, 0x42); // Show pattern 0x42 on column 1
        matrix_led_show_column(2, 0xA5); // Show pattern 0xA5 on column 2
        matrix_led_show_column(3, 0x81); // Show pattern 0x
        matrix_led_show_column(4, 0xA5); // Show pattern 0xA5 on column 4
        matrix_led_show_column(5, 0x99); // Show pattern 0x
        matrix_led_show_column(6, 0x42); // Show pattern 0x42 on column 6
        matrix_led_show_column(7, 0x3C); // Show pattern 0x3C on column 7
    }
}
