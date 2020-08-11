#include "reg52.h"
#define uchar unsigned char 

//数码管断码
uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f};

void HC138(unsigned char n){
	switch(n){
		case 4:
		P2=(P2&0x1f) | 0x80;
		break;
		case 5:
		P2=(P2&0x1f) | 0xa0;
		break;
		case 6:
		P2=(P2&0x1f) | 0xc0;
		break;
		case 7:
		P2=(P2&0x1f) | 0xe0;
		break;
	}
}

void init(){
	HC138(5);
	P0=0x00;
}

void delayms(unsigned int ms){
	unsigned char i;
	while(ms--) for(i=0;i<123;i++);
}

//点亮第一个数码管，数值为6
void ShowSMG(){
	HC138(6);
	P0=0x01;
	HC138(7);
	P0=0x82;
}

//按位显示
void ShowSMG_Bit(uchar pos,uchar value){
	HC138(6);
	P0=0x01<<pos;
	HC138(7);
	P0=SMG[value];
}

//每一位显示对应的数值
void SMG_Static(){
	uchar i;
	for(i=0;i<8;i++){
		ShowSMG_Bit(i,i);
		delayms(1000);
	}
}
void main (){
	init();
	while(1){
		SMG_Static();
	}
}