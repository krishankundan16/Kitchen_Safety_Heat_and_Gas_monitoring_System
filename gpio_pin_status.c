#define IPIN 0 //p0.0
#define OPIN 7 //p0.7
#include <lpc21xx.h>
int main()
{
	IODIR0|=1<<OPIN;
	while(1)
	{
		// read status of IPIN (p0.0)
		if(((IOPIN0>>IPIN)&1)==0)
		{
			//if status '0' then write logic '0' on p0.0
			IOCLR0=1<<OPIN;
		}
		else
		{
			//else status '1' then write logic '1' on p0.0
			IOSET0=1<<OPIN;
		}
	}
}
