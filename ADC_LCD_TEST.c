#include "ADC.h"
#include "ADC_defines.h"
#include "LCD.h"

u32 dval;
f32 eAR;
int main()
{
	Init_LCD();
	Init_ADC();
	StrLCD("ADC TEST");
	while(1)
	{
		Read_ADC(CH0,&dval,&eAR);
		WRITE_LCD_CMD(0xc0);
		U32LCD(dval);
		WRITE_LCD_DATA('=');
		F32LCD(eAR,2);
	}
}