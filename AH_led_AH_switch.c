//one active high led and one active high switch
#include<lpc21xx.h>
#define Ah_led 8 //p0.8
#define Ah_sw  16  //p0.4

int main()
{
	IODIR0|=1<<Ah_led;
	while(1)
	{
		if(((IOPIN0>>Ah_sw)&1)==1)
		{
			//turn on led because of Al_led
			IOSET0=1<<Ah_led;
		}
		else
		{
			//turn off led
			IOCLR0=1<<Ah_led;
		}
	}
}