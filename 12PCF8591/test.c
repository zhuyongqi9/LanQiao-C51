#include "reg52.h"
#include "absacc.h"
#include "intrins.h"
#include "iic.h"
 
sbit S4 = P3^3;
 
unsigned char dat_rd1;
unsigned char dat_rb2;
unsigned char stat = 0;
 
unsigned char code SMG_duanma[18]=
		{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
		 0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
 
void DelaySMG(unsigned int t)
{
	while(t--);
}
 
void DisplaySMG_Bit(unsigned char pos, unsigned char value)
{
	XBYTE[0xE000] = 0xFF;
	XBYTE[0xC000] = 0x01 << pos;
	XBYTE[0xE000] = value;
}
 
void DisplaySMG_ADC(unsigned char channel, unsigned char dat)
{
	DisplaySMG_Bit(0, SMG_duanma[16]);
	DelaySMG(100);
	DisplaySMG_Bit(1, SMG_duanma[channel]);
	DelaySMG(100);
	DisplaySMG_Bit(2, SMG_duanma[16]);
	DelaySMG(100);
			
	DisplaySMG_Bit(3, 0xFF);
	DisplaySMG_Bit(4, 0xFF);
	
	DisplaySMG_Bit(5, SMG_duanma[dat / 100]);
	DelaySMG(100);
	DisplaySMG_Bit(6, SMG_duanma[(dat % 100) / 10]);
	DelaySMG(100);
	DisplaySMG_Bit(7, SMG_duanma[dat % 10]);
	DelaySMG(100);
}
 
void Read_RD1()
{
	IIC_Start();									
	IIC_SendByte(0x90); 				
	IIC_WaitAck();  							
	IIC_SendByte(0x01); 				
	IIC_WaitAck();  							
	IIC_Stop(); 								
	
	DisplaySMG_ADC(1,dat_rd1);
	
	IIC_Start();									
	IIC_SendByte(0x91); 					
	IIC_WaitAck(); 								
	dat_rd1 = IIC_RecByte(); 			
									
	IIC_Stop(); 									
	DisplaySMG_ADC(1,dat_rd1);
}
 
void Read_RB2()
{
	IIC_Start();								
	IIC_SendByte(0x90); 					
	IIC_WaitAck();  							
	IIC_SendByte(0x03); 				
	IIC_WaitAck();  						
	IIC_Stop(); 									
	
	DisplaySMG_ADC(3,dat_rb2);
	
	IIC_Start();								
	IIC_SendByte(0x91); 				
	IIC_WaitAck(); 							
	dat_rb2 = IIC_RecByte(); 		
	
							
	IIC_Stop(); 									
	DisplaySMG_ADC(3,dat_rb2);
}
 
void Scan_Keys()
{
	if(S4 == 0)
	{
		DelaySMG(100);
		if(S4 == 0)
		{
			if(stat == 0)
			{
				stat = 1;
				while(S4 == 0)
				{
					DisplaySMG_ADC(1,dat_rd1);
				}
			}
			else if(stat == 1)
			{
				stat = 0;
				while(S4 == 0)
				{
					DisplaySMG_ADC(3,dat_rb2);
				}
			}
		}
	}
}
 
main()
{
	XBYTE[0x8000] = 0xff;
	XBYTE[0xa000] = 0x00;
	while(1)
	{
		Scan_Keys();
		if(stat == 0)
		{
			Read_RD1();
		}
		else if(stat == 1)
		{
			Read_RB2();
		}
	}
}