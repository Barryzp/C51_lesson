#include <REGX52.H> // <REG52.H>没有位操作，如P2_0是没有的
#include <INTRINS.H>

void main(void){
	
	char toggle = 0;
	P2_0 = 0;

//  一样的效果
//	P2_0 = !toggle;
//	toggle = !P3_1;
	
	while(1){
	
		if(P3_1 == 0){
			P2_0 = 0;
		}else{
			P2_0 = 1;
		}
	}
}