#include<lpc21xx.h>
#include"delay.h"
int main()
{
	int i;
	IODIR0|=255<<8;
	//all 8 led off
	IOSET0=0xF0<<8;
	delay_s(1);
	for(i=7;i>=0;i--)
	{
		//first we take AH_led and second AL led
		//turn on led one by onr left to right
		IOPIN0=(IOPIN0&~(255<<8))|(((1<<i)^0xF0)<<8);
		delay_s(1);
		//all led off
	}
 
    IOCLR0=0x0F<<8;	
		IOSET0=0xF0<<8;
		while(1);
}