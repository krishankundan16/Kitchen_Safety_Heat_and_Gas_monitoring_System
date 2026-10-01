#include <lpc21xx.h>
#include "ADC_defines.h"
#include "pin_connect_block.h"
#include "delay.h"

void Init_ADC(void)
{
	// make p0.28-->AD0.1 and p0.29--->AD0.2
	PINSEL1 &= ~((3<<24)|(3<<26));
	PINSEL1 |= ((1<<24)|(1<<26));
	
	// cfg p0.27 as AIN0
	 //PINSEL1 |=AIN1;
	 //cfg port pin(0,27,1);
	// PINSEL1 |=0x15400000;
	ADCR = (1<<PDN_BIT)|(clkDiv_value<<CLKDIV);
}
void Read_ADC(u32 chno,u32 *dval,f32 *eAR)
{
	// clear previous channel value
	ADCR &=~(0xFF);
	//select channel & start conversion
	//ADCR |=1<<chno |1<<START_CONV;
	// select required channel
	ADCR |=(1<<chno);
	//for Clear Start Bit
	ADCR &= ~(7<<24);
	// Start conversion
	ADCR |= (1<<START_CONV);
	// wait for 3 usec
	delay_us(3);
	// check the done bit status
	while(((ADDR>>DONE_BIT)&1)==0);
	// extract 10 digital op
	*dval=((ADDR>>RESULT)&1023);
	//find Ear value
	*eAR=(3.3/1023)*(*dval);
	// Stop Conversion
	ADCR &= ~(7<<24);
}
