#include "types.h"
#include "LCD.h"
#include "delay.h"
#include "KPM.h"
#include "flash.h"
u32 System_Password =4444;
u32 Wrong_attempt=3;

u32 CheckPassword(void)
{
	u32 Password;
	WRITE_LCD_CMD(0x01);
	StrLCD("ENTER Password");
	//delay_ms(500);
	Password = ReadNum();
	if(Password ==System_Password )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Access_Granted(void)
{
	
				WRITE_LCD_CMD(0x01);
	      StrLCD("Access Granted"); 
		    delay_ms(1000);
				WRITE_LCD_CMD(0x01);
	      StrLCD("EDIT MODE");
				delay_ms(1000);
}
void Access_Denied(void)
{
	WRITE_LCD_CMD(0x01);
	      StrLCD("ACCESS DENIED");
				Wrong_attempt--;
				if(Wrong_attempt>=1)
				{
				WRITE_LCD_CMD(0xC0);
				StrLCD("ATTEMPT LEFT");
				U32LCD(Wrong_attempt);
				}
			
				else
				{
					WRITE_LCD_CMD(0x01);
					StrLCD("SYSTEM LOCKED");
				   delay_ms(5000);
					Wrong_attempt=3;
				}
				delay_ms(1000);
}

void change_password(void)
{
	u32 new_p1;
	u32 new_p2;
	u32 check;
	WRITE_LCD_CMD(0x01);
		StrLCD("Security Check");
		WRITE_LCD_CMD(0x01);
		StrLCD("Old Password:");
		check = ReadNum1();
	if(check != System_Password)
	{
		WRITE_LCD_CMD(0x01);
		StrLCD("Access Denied!");
		delay_ms(1000);
		return;
	}
	  WRITE_LCD_CMD(0x01);
		StrLCD("Authenticated");
		WRITE_LCD_CMD(0x01);
		StrLCD("New Password:");
		 new_p1 = ReadNum1();
	  
	 WRITE_LCD_CMD(0x01);
		StrLCD("Confirm Pass");
		WRITE_LCD_CMD(0x01);
		StrLCD("Repeat:");
		 new_p2 = ReadNum();
	
	 WRITE_LCD_CMD(0x01);
	if(new_p1==new_p2)
	{
		System_Password = new_p1;

		StrLCD("Password change");
	}
	else
		StrLCD("Mismatch Error!");
	delay_ms(1000);
}

