#include <lpc21xx.h>
#include "delay.h"
u32 dval;
f32 eAR;
int main()
{
	Init_ADC();
	IODIR0=1<<7;
	while(1)
	{
		READ_ADC(CH0,&dval,&eAR);
		IOSET0=1<<7;
		delay_ms(dval);
		IOCLR0=1<<7;
		delay_ms(dval);
	}
}