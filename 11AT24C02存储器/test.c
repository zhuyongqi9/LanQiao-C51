#include "stc15f2k60s2.h"
#include "iic.h"
#include "absacc.h"
#define uchar unsigned char

uchar dat1=0,dat2=0,dat3=0;

unsigned char code SMG[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
		 0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};

void delayms(unsigned int ms){
	uchar i;
	while(ms--) for(i=0;i<123;i++);
}

void display_SMG(uchar pos,uchar value){
	XBYTE[0xe000]=0xff;
	XBYTE[0xc000]=0x01<<pos;
	XBYTE[0xe000]=SMG[value];
}

void Write_24C02(uchar add,uchar dat){
  IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck(); 
	IIC_SendByte(add);
	IIC_WaitAck(); 
	IIC_SendByte(dat);
	IIC_WaitAck(); 
	IIC_Stop();
}

uchar Read_24C02(unsigned char add){
  uchar temp;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck(); 
	IIC_SendByte(add);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck(); 
	temp=IIC_RecByte();
	IIC_Stop();
	return temp;
}

void Read_Write(){
	dat1=Read_24C02(0x01);
	dat1=Read_24C02(0x03);
	dat1=Read_24C02(0x05);
	
	dat1+=1;
	dat2+=1;
	dat3+=1;
	
	if(dat1>10) dat1=0;
	if(dat2>10) dat2=0;
	if(dat3>10) dat3=0;
	
	Write_24C02(0x01,dat1);
	delayms(20);
	Write_24C02(0x03,dat2);
	delayms(20);
	Write_24C02(0x05,dat3);
	delayms(20);
}

void Display(){
	display_SMG(0,dat1/10);
	delayms(10);
	display_SMG(1,dat1%10);
	delayms(10);
	display_SMG(2,16);
	delayms(10);
	
	display_SMG(3,dat2/10);
	delayms(10);
	display_SMG(4,dat2%10);
	delayms(10);
	display_SMG(5,16);
	delayms(10);
	
	display_SMG(6,dat3/10);
	delayms(10);
	display_SMG(7,dat3%10);
	delayms(10);
}

void main(){
	XBYTE[0xa000]=0x00;
	XBYTE[0x8000]=0xff;
	Read_Write();
	while(1){
		Display();
	}
}