#include "delay.h"

void delay1ms()		//@11.0592MHz
{
	unsigned char i, j;
	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void delay_for_ms(unsigned long ms){
	unsigned long i = 0;
	for(i = 0; i < ms; i++){
		delay1ms();
	}
}