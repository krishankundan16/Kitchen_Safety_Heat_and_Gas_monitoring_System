#include "types.h"
#include "ADC.h"
#include "LCD.h"
#include "LM35.h"
#include <lpc21xx.h>


int main()
{
	f32 tempc;
	f32 tempf;
	Init_LCD();
	Init_ADC();
	StrLCD("LM35 TEST");
	while(1)
	{
		tempc=LM35tc();
		WRITE_LCD_CMD(0xc0);
		F32LCD(tempc,2);
		WRITE_LCD_DATA(0xDF);
		WRITE_LCD_DATA('C');
		tempf=LM35tf();
		WRITE_LCD_CMD(0xC8);
		F32LCD(tempf,2);
		WRITE_LCD_DATA(0x0F);
		WRITE_LCD_DATA('F');
	}
}