//seg.c
#include "defines.h"
#include "types.h"
#include "delay.h"
#include <lpc21xx.h>
#define CA_7SEG 8
#define DSEL1 16
#define DSEL2 17
u8 segLUT[10]={0xC0,0XF9,0XA4,0XB0,0X99,0X92,0X82,0XF8,0X80,0X90};

u8 dp=0xFF;
void Init_7seg(void)
{
	//cfg p0.8 to p0.15 as output pins
	WRITEBYTE(IODIR0,CA_7SEG,0xFF);  //(WORD=(WORD&~(255<<SBITPOS))| (BYTE<<SBITPOS))
	//cfp p0.16 as output
	SETBIT(IODIR0,DSEL1);
	//cfg p0.17 as output
	SETBIT(IODIR0,DSEL2);
}
void disp_1_7seg(u32 n)
{
	WRITEBYTE(IOPIN0,CA_7SEG,(segLUT[n]));
}

void disp_2mux_7seg(u32 n)
{
	s32 dly;
	for(dly=10; dly>0; dly--)
	{
	WRITEBYTE(IOPIN0,CA_7SEG,(segLUT[n/10]&dp));
		//turn on seg1
		SSETBIT(IOSET0,DSEL1);
		delay_ms(1);
		//turn off seg1
		SCLRBIT(IOCLR0,DSEL1);
		
		WRITEBYTE(IOPIN0,CA_7SEG,segLUT[n%10]);
		//turn on seg2
		SSETBIT(IOSET0,DSEL2);
		delay_ms(1);
		//turn off seg2
		SCLRBIT(IOCLR0,DSEL2);
	}
}

void disp_2fmux_7seg(f32 f)
{
	u32 n;
	if(f>=0.0 && f<=9.9)
	{
	dp=0x7F;
	n=f*10;
	}
	disp_2mux_7seg(n);
	dp=0xFF;
}
