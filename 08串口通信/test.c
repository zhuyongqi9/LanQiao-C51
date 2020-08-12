#include "STC15F2K60S2.h"

unsigned char urdat;
void SendByte(unsigned char dat);
void init(){
	P2=(P2&0x1f) | 0xa0;
	P0=0x00;
}

void InitUart(){
	
	EA=1;
	ES=1;
	ET1=0;
	TR1=1;
	
	SCON=0x50;
	AUXR = 0x00;		

	TMOD = 0x20;               
	TH1=0xfd;
	TL1=0xfd;
}

void ServiceUart()interrupt 4{
	if(RI==1){
		RI=0;
		urdat=SBUF;
		SendByte(urdat+1);
	}
}

void SendByte(unsigned char dat){
	SBUF=dat;
	while(TI==0);
	TI=0;
}

void main(){
	init();
	InitUart();
	SendByte(0x5a);
	SendByte(0xa5);
	while(1);
}