//gpio_0_to_255.c

#include<lpc21xx.h>
#include"delay.h"
int main()
{
	int i;
	//cfg p0.8 to p0.15 as output pins
	IODIR0=255<<8;
	for(i=0;i<256;i++)
	{
		//turn on led when i=1 to 255
		IOSET0=i<<8;
		delay_ms(500);		//delay 100ms
		IOCLR0=255<<8;     //turn off led
		delay_ms(500);
	}
	while(1);
}
	