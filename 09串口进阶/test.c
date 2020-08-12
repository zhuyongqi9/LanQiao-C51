#include "stc15f2k60s2.h"
#define uchar unsigned char

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

void init(){
	HC138(5);
	P0=0x00;
	HC138(4);
	P0=0xff;
}

//===============
uchar command=0x00;
void InitUart(){
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	
	SCON=0x50;
	AUXR=0x00;
	
	TR1=1;
	EA=1;
	ES=1;
}

void ServiceUart()interrupt 4{
	if(RI==1){
		command=SBUF;
	}
	if(TI==1){
		
	}
}

void SendByte(uchar dat){
	SBUF=dat;
	while(TI == 0);
	TI=0;
}

void SendString(uchar *str){
	while(*str!='\0') SendByte(*str++);
}
//===============

void Working(){
	if(command!=0x00){
		switch(command & 0xf0){
			case 0xa0:
			
			command=0x00;
			break;
			case 0xb0:
			
			command=0x00;
			break;
			case 0xc0:
			SendString("The system is running!\r\n");
			command=0x00;
			break;
		}
	}
}
void main(){
	init();
	InitUart();
	SendString("Welcome to Syetem! ÖìÓÂ÷è\r\n");
	while(1){
		Working();
	}
}