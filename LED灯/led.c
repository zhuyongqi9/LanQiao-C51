#include "reg52.h"

¡
void Delayms(unsigned int t){
	unsigned char i;
	while(t--){
		for(i=0;i<123;i++);
	}
}

void delay(unsigned int t){
	while(t--);
	while(t--);
}

//HC138ÒëÂëÆ÷Ñ¡Ôñ
void InitHC138(unsigned char n){
	switch(n)
	{
		case 4:
		P2= P2&0x1f|0x80;	
		break;
		case 5:
		P2= P2&0x1f|0xa0;	
		break;
		case 6:
		P2= P2&0x1f|0xc0;	
		break;
		case 7:
		P2= P2&0x1f|0xe0;	
		break;	
	}
}

 
void main(){
	//¹Ø±Õ·äÃùÆ÷
	InitHC138(5);
	P0=0x00;
	InitHC138(4);
	while(1){
		int i=0;
		for(i=1;i<=8;i++){
			P0=0xff<<i;
			 Delayms(1000);
		}
		for(i=1;i<=8;i++){
			P0=~(0xff<<i);
			 Delayms(1000);
		}
	}
}