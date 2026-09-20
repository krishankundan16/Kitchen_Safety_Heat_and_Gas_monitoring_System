#define IPIN 0 //p0.0
#define OPIN 7 //p0.7
#include<lpc21xx.h>
int main()
{
	IODIR0|=1<<OPIN;
	while(1)
	{
		((IOPIN0>>IPIN)&1)?(IOSET0=1<<OPIN):(IOCLR0=1<<OPIN);
	}
}

