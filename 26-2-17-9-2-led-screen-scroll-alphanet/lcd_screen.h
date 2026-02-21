#ifndef __LCD_SCREEN_H__
#define __LCD_SCREEN_H__

#include <REGX52.H>
#include "delay.h"

sbit RCK = P3^5; // 74HC595 RCLK pin (latch pin)
sbit SCK = P3^6; // 74HC595 SRCLK pin (shift clock pin)
sbit SER = P3^4; // 74HC595 SER pin (serial data input pin)

#define LED_MATRIX_PORT P0 // Define the port connected to the LED matrix


void write_byte_74595(unsigned char byte);
void matrix_led_show_column(unsigned char column, unsigned char byte);
void matrix_led_init();

#endif