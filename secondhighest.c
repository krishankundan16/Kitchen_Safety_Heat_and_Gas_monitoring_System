//Write an ECP to find the second highest digit in a given integer and display its binary
//equivalent on 8-LEDS (4-Active High LEDS& 4-Active Low LEDS)
#include<lpc21xx.h>
#include"delay.h"
#define AL_sw 16
int main()
{
	int t,digit;
	int high=0,sh=0;
	int led_data[3];
	int index=0;
	int n[3]={9872,6532,423};  //given integer
	int i=0;
	IODIR0|=0xFF<<8;
	t=n[i];
	while(t>0)
	{
		digit=t%10;
		if(digit>high)
		{
			sh=high;
			high=digit;
		}
		else if((digit>sh) && (digit!=high))
		{
			sh=digit;
		}
		i++;
		t=t/10;
		led_data[index]=sh;
		index++;
	}
	while(1)
	{
		if(((IOPIN0>>AL_sw)&1)==0)
		{
	    IOSET0=0xFF<<8;
	    IOCLR0=led_data[index]<<8; //ah p0.8 to p.11
			index++;
			delay_ms(100);
		}
		while(((IOPIN0>>AL_sw)&1)==0);
	    delay_ms(100);
	
	}
}
	