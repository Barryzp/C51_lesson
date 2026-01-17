#include <REGX52.H>
#include <INTRINS.H>

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

void delay_for_ms(unsigned int ms){
	int i = 0;
	for(i = 0; i < ms; i++){
		delay1ms();
	}
}

unsigned int status[8] = {0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0xFE};

void main(void){
	int i = 0;
	while(1){
		for(i = 0; i < 8; i++){
			P2 = status[i];
			delay_for_ms(500);
			P2 = 0XFF;
			delay_for_ms(500);
		}
	}
}