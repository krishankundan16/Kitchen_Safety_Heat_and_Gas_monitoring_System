//write ecp toggle p0.8 wrt 100ms delay
#include<lpc21xx.h>
#include"delay.h"
#define Al_led 8  //p0.8
int main()
{
	//cfg p0.8 as output pin
	IODIR0=1<<Al_led;
	while(1)
	{
		//write logic'1' for turn on led
		IOSET0=1<<Al_led;
		//delay 100ms
		delay_ms(50);
		//write logic '0' for turn off led
		IOCLR0=1<<Al_led;
		delay_ms(50);
	}
}