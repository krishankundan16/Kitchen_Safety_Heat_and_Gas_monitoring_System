//basic_cal.c
#include "LCD.h"
#include "KPM.h"
#include "types.h"
int main()
{
	u32 num1,num2,result;
	u8 op;
	Init_LCD();
	InitKPM();
	StrLCD("BASIC CAL");
	while(1)
	{
		WRITE_LCD_CMD(0XC0);
		num1=ReadNum();
		U32LCD(num1);
		op=keyscan();
		WRITE_LCD_DATA(op);
		num2=ReadNum();
		U32LCD(num2);
		switch(op)
		{
			case '+': result=num1+num2;
									break;
			case '-': result=num1-num2;
									break;
			case '*': result=num1*num2;
									break;
			case '/': result=num1/num2;
									break;
		}
		op=keyscan();
		if(op=='=')
		{
			WRITE_LCD_DATA(op);
			U32LCD(result);
			op=keyscan();
			if(op=='C')
			{
				WRITE_LCD_CMD(0XC0);
				StrLCD("                ");
			}
		}
			
	}
}