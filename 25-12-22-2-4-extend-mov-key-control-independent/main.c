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
	unsigned char LED_num = 0;
	
	P2 = 0xFE;
	
	while(1){
		if(P3_0 == 0){
			// 按键消抖
			delay_for_ms(20);
			while(P3_0 == 0);
			// 按键消抖
			delay_for_ms(20);
			
			LED_num++;
			if(LED_num >= 8) LED_num = 0;
			P2 = ~(0x01 << LED_num);
		}
		
		if(P3_1 == 0){
			// 按键消抖
			delay_for_ms(20);
			while(P3_1 == 0);
			// 按键消抖
			delay_for_ms(20);
			
			if(LED_num <= 0) LED_num = 8;
			LED_num--;
			P2 = ~(0x01 << LED_num);
		}
	}
}