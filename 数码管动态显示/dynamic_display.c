#include "reg52.h"
#define uchar unsigned char
	
uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8, 0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f};
uchar code value[]={2,0,2,0,0,8,1,1};
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
	P0=0x01<<(pos-1);
	HC138(7);
	P0=SMG[value];
}


void dynamic_show(){
	int length=sizeof(value)/sizeof(uchar);
	uchar *p=value;
	int i,j=0;
	for(i=0;i<length;i++){
		Show_SMG(++j,*p++);
		delayms(2);
	}
}

void main(){
	Init();
	while(1){
		dynamic_show();
	}
}