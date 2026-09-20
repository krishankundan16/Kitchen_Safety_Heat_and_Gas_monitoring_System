#include<lpc21xx.h>
#include"delay.h"
int main()
{
	int i;
	IODIR0|=255<<8;
	//all 8 led off
	IOSET0=0x0F<<8;
	delay_s(1);
	for(i=0;i<=7;i++)
	{
		//first we take AL_led and second AH led
		//turn on led one by onr right to left
		IOPIN0=(IOPIN0&~(255<<8))|(((1<<i)^0x0F)<<8);
		delay_s(1);
		//all led off
	}
 
    IOCLR0=0xF0<<8;	
		IOSET0=0x0F<<8;
		while(1);
}