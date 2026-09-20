// toggle p0.5 infinitly wrt 500ms delay
#include<lpc21xx.h>
#include"delay.h"
int main()
{
	IODIR0=1<<5;
	while(1)
	{
		//by using xor write logic'1' and logic'0'
		IOPIN0^=1<<5;
		delay_ms(500);
	}
	
		
}