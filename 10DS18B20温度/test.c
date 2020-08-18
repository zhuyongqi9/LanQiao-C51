#include "stc15f2k60s2.h"
#include "absacc.h"
#include "onewire.h"
#define uchar unsigned char
	
uchar code SMG[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f};
unsigned int temp=000;

void delayms(unsigned int ms){
	uchar i;
	while(ms--){for(i=0;i<123;i++);}
}

void init(){
	XBYTE[0x8000]=0xff;
	XBYTE[0xa000]=0x00;
}
void displaySMG(uchar pos,uchar value){
	XBYTE[0xe000]=0xff;
	XBYTE[0xc000]=0x01<<pos;
	XBYTE[0xe000]=SMG[value];
}


void display_temp(){
	displaySMG(7,temp%10);
	delayms(10);
	displaySMG(6,17);
	delayms(10);
	displaySMG(5,temp%100/10);
	delayms(10);
	displaySMG(4,temp/100);
	delayms(10);
}

void delay(unsigned int t){
 while(t--){
   display_temp();
 }	 
}

void read_DS18B20_tmp(){
	uchar LSB,MSB;
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
	
	delay(1000);
	
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);
	
	LSB=Read_DS18B20();
	MSB=Read_DS18B20();
	
	temp=MSB;
	temp=temp << 8 | LSB;
  
	if((temp&0xf800) == 0x0000){
		temp =temp >> 4;
		temp *=10;
		temp=temp+(LSB&0x0f)*0.625;
	}
}

void main(){
	init();
	while(1){
		display_temp();
		read_DS18B20_tmp();
	}
}