#include "reg52.h"
#define uchar unsigned char
	
uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8, 0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f};

void HC138(uchar n){
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

void delayms(int n){
	uchar i;
	while(n--) for(i=0;i<123;i++);
}

void Init(){
	HC138(5);
	P0=0x00;
}

void Show_SMG(uchar pos,uchar value){
	HC138(6);
	P0=0x01<<pos;
	HC138(7);
	P0=SMG[value];
	
}

int scan(){
	P3=P3&0x0f;
	if(P3!=0x0f){
		delayms(10);
			if(P3!=0x0f){
				P3=P3&0x0f;
				if(P3==0x07) return 4;
				if(P3==0x0b) return 5;
				if(P3==0x0d) return 6;
				if(P3==0x0e) return 7;
			}
	}
}

void main(){
	Init();
	while(1){
		int num=scan();
		switch(num){
			case 4:
			Show_SMG(0,1);
			break;
			case 5:
			Show_SMG(0,2);	
			break;
			case 6:
			Show_SMG(0,3);	
			break;
			case 7:
			Show_SMG(0,4);	
			break;
		}			
	}
}
