//toggle p0.7 infinitly wrt 500ms delay
#include<lpc21xx.h>
#include"delay.h"
int main()
{
	//cfg p0.7 as output
	IODIR0|=1<<7;
	while(1)
	{
		//write logic '1' on p0.7
		IOSET0=1<<7;
		delay_ms(500);
		IOCLR0=1<<7;
		delay_ms(500);
	}
}
	
