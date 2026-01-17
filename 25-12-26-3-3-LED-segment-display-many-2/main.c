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

void delay_for_ms(unsigned long ms){
	unsigned long i = 0;
	for(i = 0; i < ms; i++){
		delay1ms();
	}
}

void num0_display(){
		// ��ʾ0����a,b,c,d,e,fλ��0011 1111
		P0 = 0x3F;
}

void num1_display(){
		// ��ʾ1����b, cλ��0000 0110
		P0 = 0x06;
}

void num2_display(){
		// ��ʾ2����a,b,g,e,gλ��0101 1011
		P0 = 0x5B;
}

void num3_display(){
		// ��ʾ3����a,b,c,d,g,λ��0100 1111
		P0 = 0x4F;
}

void num4_display(){
		// ��ʾ4����b,c,f,gλ��0110 0110
		P0 = 0x66;
}

void num5_display(){
		// ��ʾ5����a,c,d,f,gλ��0110 1101
		P0 = 0x6D;
}

void num6_display(){
		// ��ʾ6����a,c,d,e,f,gλ��0111 1101
		P0 = 0x7D;
}

void num7_display(){
		// ��ʾ7����a,b,cλ��0000 0111
		P0 = 0x07;
}

void num8_display(){
		// ��ʾ8����a,b,c,d,e,f,gλ��0111 1111
		P0 = 0x7F;
}

void num9_display(){
		// ��ʾ9����a,b,c,d,f,gλ��0110 1111
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

void show_pos_num(unsigned char pos, unsigned char num){
	choose_num_pos(pos);
	show_num_unit(num);
	delay1ms();		// 增加显示时间
	
	P0=0x00;		// 每位都要清空，防止显示混乱
}

unsigned char get_number_digits(unsigned long number){
	unsigned char count = 0;
	if(number == 0) return 0;
	
	while(number != 0){
		number = number / 10;
		count++;
	}
	return count;
}

void show_num_range(unsigned long number){
	
	unsigned char digit_num = get_number_digits(number);
	unsigned long integer = 0;
	unsigned long number_temp = 0;
	unsigned char remainder = 0;
	unsigned char i = 0;
	unsigned char j = 0;
	
	if(digit_num == 0) return;
	
	// 扫描10次每一位数字，让人眼能看清每一位
	for(j = 0; j < 10; j++){
		number_temp = number;
		for(i=0; i<digit_num; i++){
			remainder = number_temp % 10;
			integer = number_temp / 10;
			number_temp = integer;
			show_pos_num(i+1, remainder);
		}
	}
}

void main(void){
	unsigned long counter = 0;
	unsigned char display_buf[8] = {0, 0, 0, 0, 0, 0, 0, 0};	// 显示缓冲区
	unsigned long temp_num = 0;
	unsigned char i = 0;
	unsigned int scan_count = 0;
	
	while(1){
		// 每10次扫描更新一次数字（扫描周期固定，更新间隔固定）
		if(scan_count >= 10){
			scan_count = 0;
			counter++;
			
			// 将数字分解到缓冲区（从右到左，即个位到高位）
			temp_num = counter;
			for(i = 0; i < 8; i++){
				display_buf[i] = temp_num % 10;
				temp_num = temp_num / 10;
			}
		}
		
		// 固定显示8位，保证扫描时间恒定
		for(i = 0; i < 8; i++){
			show_pos_num(i+1, display_buf[i]);
		}
		
		scan_count++;
	}
}