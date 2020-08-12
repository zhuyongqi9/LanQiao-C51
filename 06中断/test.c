#include "reg52.h"
#define uchar unsigned char;9
void HC138(unsigned char n){
	switch(n){
		case 4:
		P2=P2&0x1f|0x80; 	
		break;
		case 5:
		P2=P2&0x1f|0xa0; 	
		break;
		case 6:
		P2=P2&0x1f|0xc0; 	
		break;
		case 7:
		P2=P2&0x1f|0xe0; 	
		break;
	}
}

void delayms(unsigned int n){
	unsigned char i;
	while(n--) for(i=0;i<123;i++);
}

void working(){
	//8个灯循环亮灭
	HC138(4);
	P0=0x00;
	delayms(1000);
	P0=0xff;
	delayms(1000);
}

void INTO() interrupt 0{
	int i;
	//流水灯循环
	HC138(4);
	P0=0xfe;
	for(i=0;i<8;i++){
		delayms(2000);
		P0= (P0<<1)|0x01;
	}
}

void init(){
	HC138(5);
	P0=0x00;
}
void main(){
	init();
	//打开中断
	EA=1;
	EX0=1;
	IT0=1;
	while(1){
		working();
	}
}