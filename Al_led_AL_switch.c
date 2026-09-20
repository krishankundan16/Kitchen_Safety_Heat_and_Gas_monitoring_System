//four active low led and one active low switch
#include<lpc21xx.h>

#define Al_sw  16  //p0.4

int main()
{
	IODIR0|=0xf0<<8;
	while(1)
	{
		if(((IOPIN0>>Al_sw)&1)==0)
		{
			//turn on led because of Al_led
			IOCLR0=0xf0<<8;
			//IOSET0=1<<Al_led;
		}
		else
		{
			//turn off led
			IOSET0=0xf0<<8;
			//IOCLR0=1<<Ah_led;
		}
	}
}