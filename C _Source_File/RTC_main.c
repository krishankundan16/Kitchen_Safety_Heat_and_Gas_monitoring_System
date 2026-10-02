//RTC_main.c
#include "LCD.h"
#include <lpc214x.h>
#include "lcd_defines.h"
#include "RTC_define.h"
#include "RTC.h"

s32 hour,min,sec,date,month,year,day;

int main()
{
    // Initialize RTC 
		RTC_Init();
    // Initialize the LCD
		Init_LCD();
	
    // Set the initial time (hours, minutes, seconds)
		SetRTCTimeInfo(15,58,0);
    // Set the initial date (date, month, year)
		SetRTCDateInfo(5,9,2026);
    // Set initial day (SUN to SAT )
		SetRTCDay(SAT);

while (1) 
    {
      // Get and display the current time info on LCD
			GetRTCTimeInfo(&hour,&min,&sec);
			DisplayRTCTime(hour,min,sec);
			// Get and display the current date info on LCD
			GetRTCDateInfo(&date,&month,&year);
			DisplayRTCDate(date,month,year);
		  // Get and display the current day info on LCD
			GetRTCDay(&day);
			DisplayRTCDay(day);
			

    }
}


