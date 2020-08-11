#include "STC15F2K60S2.h"

#define uchar unsigned char
	
uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8, 0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f};

//表示读取的值
int num=0;
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

void scan(){
	int col,row;
	int kp=0;
	P3=0x0f;
	P42=0;
	P44=0;
	P3=P3&0x0f;
	if(P3!=0x0f && kp==0){
		delayms(10);
		  //读行
			if(P3!=0x0f && kp==0){
				kp=1;
				if((P3&0x0f)==0x0e) row=0;
				if((P3&0x0f)==0x0d) row=1;
				if((P3&0x0f)==0x0b) row=2;
				if((P3&0x0f)==0x07)	row=3;		
			}
			
			//读列
			P3=0xf0;
			P42=1;
			P44=1;
			if(P44 == 0) col=1;
			if(P42 == 0) col=2;
			if(P35 == 0) col=3;
			if(P34 == 0) col=4;	
	}
	
	if(kp==1){
		num= row*4+col;
	}
}

void main(){
	Init();
	while(1){
	 scan();
	 delayms(5);
		//延时程序，可消残影
	 Show_SMG(0,num);
	}
}
