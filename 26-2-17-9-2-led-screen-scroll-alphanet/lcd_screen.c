#include "lcd_screen.h"

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

void matrix_led_init(){
	// 初始化74HC595的控制引脚
	SCK = 0; // 初始化移位时钟为低电平
	RCK = 0; // 初始化锁存时钟为低电平
	SER = 0; // 初始化串行数据输入为低电平
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