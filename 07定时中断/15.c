#include "reg52.h"
#define uchar unsigned char

uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8, 0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f};
int con,s,m,h;
void delayms(unsigned int ms){
	uchar i;
	while(ms--) for(i=0;i<123;i++);
}

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

void display(uchar pos,uchar value){
	HC138(6);
	P0=0x01<<pos;
	HC138(7);
	P0=SMG[value];
}
/*
  *显示时间函数
  *参数n为延时函数的时间
*/
void showSMG(uchar n){
	display(0,h/10);
	delayms(n);
	display(1,h%10);
	delayms(n);
	display(2,16);
	delayms(n);
	display(3,m/10);
	delayms(n);
	display(4,m%10);
	delayms(n);
	display(5,16);
	delayms(n);
	display(6,s/10);
	delayms(n);
	display(7,s%10);
	delayms(n);
}
//===================
void initTimer(){
	EA=1;
	ET0=1;
	TMOD=0x01;
	TH0=15536/256;
	TL0=15536%256;
	TR0=1;
}

void TimerService() interrupt 1{
	TH0=15536/256;
	TL0=15536%256;
	if(++con==20) {con=0;s++;}
	if(s==60) {m++;s=0;}
	if(m==60) {h++;m=0;}
}
//===================
void init(){
	HC138(5);
	P0=0x00;
	HC138(4);
	P0=0xff;
}
void main(){
	init();
	initTimer();
	while(1){
		showSMG(15);
	}
}