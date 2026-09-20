#include<lpc21xx.h>
#include"delay.h"
int main()
{
	int i;
	IODIR0|=0xff<<0;
	IOPIN0=0xf0;
	for(i=0;i<5;i++)
	{
		//led0&led7 on
		//IOCLR0=0xFF;
		//IOSET0=0x71;
		IOPIN0=0x71;
		delay_s(1);
		//led 1&6 on
		//IOCLR0=0xFF;
		//IOSET0=0xB2;
		IOPIN0=0xB2;
		delay_s(1);
		//led 2&5 on
		//IOCLR0=0xFF;
		//IOSET0=0xD4;
		IOPIN0=0xD4;
		delay_s(1);
		//led 3&4 on
		//IOCLR0=0xFF;
		//IOSET0=0xE8;
		IOPIN0=0xE8;
		delay_s(1);
	}
	//IOCLR0=0x0F;
	//IOSET0=0xF0;
	IOPIN0=0xF0;
	while(1);
}