#include<lpc21xx.h>
#include"delay.h"
#define CA_7seg 8
#define SEG1    17
unsigned char seglut[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int main()
{
	int i;
	IODIR0|=(0xFF<<9);
	IODIR0|=(1<<CA_7seg);
	IODIR0|=(1<<SEG1);
	while(1)
	{
	 for(i=0;i<10;i++)
		{
			IOCLR0=255<<9;
			IOSET0=seglut[i]<<9;
			delay_ms(500);
		}
  }
}
