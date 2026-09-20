#include <lpc21xx.h>
#include "types.h"
#include <stdlib.h>
#include "delay.h"
#define sw 4  //p0.4
#define CA_7SEG 8
u8 segLUT[7]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82};
u8 dice_value;

int main()
{
	s32 seed;
	IODIR0|=255<<CA_7SEG;
	IOPIN0= segLUT[dice_value]<<CA_7SEG;
	while(1)
	{
		while(((IOPIN0>>sw)&1)==0)
		{
			srand(seed++);
			dice_value=rand()%6+1;
			IOPIN0=segLUT[dice_value]<<CA_7SEG;
			delay_ms(50);
		}
		}
}
