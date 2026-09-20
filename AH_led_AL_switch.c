//one active high led and one active low switch
#include<lpc21xx.h>
#define Ah_led 8 //p0.8
#define Al_sw  16  //p0.4

int main()
{
	IODIR0|=1<<Ah_led;
	while(1)
	{
		if(((IOPIN0>>Al_sw)&1)==0)
		{
			//turn on led because of Al_led
			//IOCLR0=1<<Ah_led;
			IOSET0=1<<Ah_led;
		}
		else
		{
			//turn off led
			//IOSET0=1<<Ah_led;
			IOCLR0=1<<Ah_led;
		}
	}
}