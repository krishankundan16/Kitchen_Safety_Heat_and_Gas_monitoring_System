// by using switch case check status of pin
#define IPIN 0 //p0.0
#define OPIN 7 //p0.7
#include<lpc21xx.h>
int main()
{
	IODIR0|=1<<OPIN;
	while(1)
	{
		switch(((IOPIN0<<IPIN)&1))
		{
			case 0: IOCLR0=1<<OPIN;
			break;
			case 1: IOSET0=1<<OPIN;
			break;
		}
	}
}
