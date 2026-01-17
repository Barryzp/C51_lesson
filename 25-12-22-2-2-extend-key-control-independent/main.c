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
		if(P3_1 == 0){
			delay_for_ms(20);
			while(P3_1 == 0);
			delay_for_ms(20);
			P2_0 = ~P2_0;
		}
	}
}