#include <REGX52.H>
#include "delay.h" 
#include "nixie.h"


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