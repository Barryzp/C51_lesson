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


void main(void){
	while(1){
		P2 = 0XFE;
		delay_for_ms(500);
		P2 = 0XFF;
	}
}