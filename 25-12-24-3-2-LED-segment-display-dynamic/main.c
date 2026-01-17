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

void num0_display(){
		// 显示0就是a,b,c,d,e,f位亮0011 1111
		P0 = 0x3F;
}

void num1_display(){
		// 显示1就是b, c位亮0000 0110
		P0 = 0x06;
}

void num2_display(){
		// 显示2就是a,b,g,e,g位亮0101 1011
		P0 = 0x5B;
}

void num3_display(){
		// 显示3就是a,b,c,d,g,位亮0100 1111
		P0 = 0x4F;
}

void num4_display(){
		// 显示4就是b,c,f,g位亮0110 0110
		P0 = 0x66;
}

void num5_display(){
		// 显示5就是a,c,d,f,g位亮0110 1101
		P0 = 0x6D;
}

void num6_display(){
		// 显示6就是a,c,d,e,f,g位亮0111 1101
		P0 = 0x7D;
}

void num7_display(){
		// 显示7就是a,b,c位亮0000 0111
		P0 = 0x07;
}

void num8_display(){
		// 显示8就是a,b,c,d,e,f,g位亮0111 1111
		P0 = 0x7F;
}

void num9_display(){
		// 显示9就是a,b,c,d,f,g位亮0110 1111
		P0 = 0x6F;
}

void show_num_unit(unsigned char num){
		if(num == 0){
			num0_display();
		}else if(num == 1){
			num1_display();
		}else if(num == 2){
			num2_display();
		}else if(num == 3){
			num3_display();
		}else if(num == 4){
			num4_display();
		}else if(num == 5){
			num5_display();
		}else if(num == 6){
			num6_display();
		}else if(num == 7){
			num7_display();
		}else if(num == 8){
			num8_display();
		}else if(num == 9){
			num9_display();
		}
}

// 选择哪个数码管，从右到左1，2，3，4，...
void show_led_1(){
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 0;
}

void show_led_2(){
		P2_4 = 0;
		P2_3 = 0;
		P2_2 = 1;
}

void show_led_3(){
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 0;
}

void show_led_4(){
		P2_4 = 0;
		P2_3 = 1;
		P2_2 = 1;
}

void show_led_5(){
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 0;
}

void show_led_6(){
		P2_4 = 1;
		P2_3 = 0;
		P2_2 = 1;
}
void show_led_7(){
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 0;
}

void show_led_8(){
		P2_4 = 1;
		P2_3 = 1;
		P2_2 = 1;
}

void choose_num_pos(unsigned char pos){
	if(pos == 1){
		show_led_1();
	}else if(pos == 2){
		show_led_2();
	}else if(pos == 3){
		show_led_3();
	}else if(pos == 4){
		show_led_4();
	}else if(pos == 5){
		show_led_5();
	}else if(pos == 6){
		show_led_6();
	}else if(pos == 7){
		show_led_7();
	}else if(pos == 8){
		show_led_8();
	}
}

void main(void){
	
	// 段选线-选择哪个管亮，通过38译码器
	// 我想要第7个数码管亮，那么对应二进制为110(从0开始)
	// 这是共阴极，那么就是需要高电平接通
	
	unsigned char i = 0;
	unsigned char j = 0;
	while(1){
		for(j=0; j<8; j++){
			choose_num_pos(j+1);
			for(i=0; i<=9; i++){
					show_num_unit(i);
					delay_for_ms(500);
			}
		}
	}
}