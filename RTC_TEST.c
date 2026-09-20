//RTC_test.c
#include <lpc21xx.h>
#include "lcd.h"
#define PCLK 15000000
#define PREINT_VAL ((PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

int main()
{
	//CTC reset
	Init_LCD();
	CCR=1<<1;
	PREINT=PREINT_VAL;
	PREFRAC= PREFRAC_VAL;
	CCR=1<<0;
	SEC=50;
	MIN=59;
	HOUR=15;
	DOM=5;
	MONTH=9;
	YEAR=2026;
	DOW=6;// SAT
	while(1)
	{
		WRITE_LCD_CMD(0x80);
		WRITE_LCD_DATA(HOUR/10+'0');
		WRITE_LCD_DATA(HOUR%10+'0');
		WRITE_LCD_DATA(':');
		
		WRITE_LCD_DATA(MIN/10+'0');
		WRITE_LCD_DATA(MIN%10+'0');
		WRITE_LCD_DATA(':');
		
		WRITE_LCD_DATA(SEC/10+'0');
		WRITE_LCD_DATA(SEC%10+'0');
		
		WRITE_LCD_CMD(0xC0);
		WRITE_LCD_DATA(DOM/10+'0');
		WRITE_LCD_DATA(DOM%10+'0');
		WRITE_LCD_DATA('/');
		
		WRITE_LCD_DATA(MONTH/10+'0');
		WRITE_LCD_DATA(MONTH%10+'0');
		WRITE_LCD_DATA('/');
		
		U32LCD(YEAR);
		WRITE_LCD_CMD(0X8A);
		switch(DOW)
		{
			case 0 : StrLCD("SUN");
								break;
			case 1 : StrLCD("MON");
								break;
			case 2 : StrLCD("TUE");
								break;
			case 3 : StrLCD("WED");
								break;
			case 4 : StrLCD("THU");
								break;
			case 5 : StrLCD("FRI");
								break;
			case 6 : StrLCD("SAT");
								break;
		}
	}
	
	
}