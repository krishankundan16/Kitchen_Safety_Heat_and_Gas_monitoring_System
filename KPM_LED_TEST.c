#include "LCD.h"
#include "KPM.h"
#include "types.h"
#include "delay.h"
int main()
{
	
	u32 key;
	Init_LCD();
	InitKPM();
	StrLCD("KPM TEST");
	while(1)
	{
		WRITE_LCD_CMD(0XC0);
		key=keyscan();
			U32LCD(key);
		delay_ms(500);
			WRITE_LCD_CMD(0XC0);
			StrLCD("  ");
		
	}
}
