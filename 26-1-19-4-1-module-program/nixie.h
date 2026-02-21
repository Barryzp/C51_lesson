#ifndef __NIXIE_H__
#define __NIXIE_H__

#include <REGX52.H>
#include "delay.h"

void num0_display();
void num1_display();
void num2_display();
void num3_display();
void num4_display();
void num5_display();
void num6_display();
void num7_display();
void num8_display();
void num9_display();

void show_led_1();
void show_led_2();
void show_led_3();
void show_led_4();
void show_led_5();
void show_led_6();
void show_led_7();
void show_led_8();

void choose_num_pos(unsigned char pos);

void show_num_unit(unsigned char num);

void show_pos_num(unsigned char pos, unsigned char num);

unsigned char get_number_digits(unsigned long number);

void show_num_range(unsigned long number);

#endif