//print_fibon_in_Al_led.c
#include<lpc21xx.h>
#include"delay.h"
#define Al_sw 16
int main()
{
	int a=0,b=1,c;
	int t[4];
	int i=0;
	int index=0;
	IODIR0|=0xFF;
	IODIR0&=~(1<<Al_sw); //take input switch
	IOSET0=0xFF;
	while(a<=80)
	{
			if(a>=10)
			{
			  t[i]=a;
				i++;
			}
			c=a+b;
			a=b;
			b=c;
	}
	while(1)
	{
	   if(((IOPIN0>>Al_sw)&1)==0)
	 {
		delay_ms(20);
	
	
		IOSET0=0xFF; //led off
		IOCLR0=t[index]<<0;  //led display
		index++;
		 while(((IOPIN0>>Al_sw)&1)==0);
		delay_ms(100);
	 }
  }
}

	
	
	