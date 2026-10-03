#include "types.h"
#include "ADC.h"
#include "LCD.h"
#include "LM35.h"
#include <lpc21xx.h>
#include "buzzer.h"
#include "RTC.h"
#include "RTC_define.h"
#include "delay.h"
#include "CONFIG.h"
#include "MQ2.h"
#include "eint0.h"
#include "security.h"
#include "KPM.h"
#include "event.h"



s32 hour,min,sec,date,month,year,day;

int main()
{
	
	
	// Initialize LCD
	Init_LCD();
	// Initialize ADC
	Init_ADC();
// Initialize RTC	
	RTC_Init();
	
	eint0_enable();
	InitKPM();

	while (1) 
    {
       // Get and display the current time info on LCD
			GetRTCTimeInfo(&hour,&min,&sec);
			//WRITE_LCD_CMD(0x80);
			DisplayRTCTime(hour,min,sec);
			// Get and display the current date info on LCD
			GetRTCDateInfo(&date,&month,&year);
			//WRITE_LCD_CMD(0xC0);
			DisplayRTCDate(date,month,year);
		  // Get and display the current day info on LCD
			
			//Display the temperature in celseius
		  Read_Temperature();
     
		  Read_Gas();
          delay_ms(1000);
		  Safety_status();
			//delay_ms(500);
			Check_New_Event();
			//delay_ms(500);
			Check_Event_Display();
			//delay_ms(1000);
			if(edit_mode == 1)
	   {
			edit_mode =0;
			// Check password function
			if(CheckPassword())
			{	// If password is correct display access granted
				Access_Granted();
				// By using Edit_menu function we can edit time , date, temp and password
				Edit_Menu();
			}
			else
			{	// If password is wrong display access denied
				Access_Denied();
			}
			
		}
		 
	
		}
}
