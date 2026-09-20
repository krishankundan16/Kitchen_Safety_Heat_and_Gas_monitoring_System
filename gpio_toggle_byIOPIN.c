//toggle p0.7 infinitly wrt 100ms delay
#include<lpc21xx.h>
#include"delay.h"
int main()
{
	//cfg p0.7 as output
	IODIR0|=1<<7;
	while(1)
	{
		//write logic '1' on p0.7
		IOPIN0|=1<<7;
		delay_ms(100);
		IOPIN0&=~(1<<7);
		delay_ms(100);
	}
}
	
