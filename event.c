#include <lpc21xx.h>
#include "event.h"
#include "LCD.h"
#include "RTC.h"
#include "delay.h"
#include "types.h"



extern f32 TEMPC;
extern u32 gas_value;
extern u32 temp_unsafe;
extern u32 gas_unsafe;
SafetyEvent latest_event;
static u32 prev_temp_unsafe = 0;
static u32 prev_gas_unsafe = 0;

void Check_New_Event(void)
{
    s32 hour, min, sec;
    s32 date, month, year;

    /*
       Temperature SAFE -> UNSAFE
    */
    if((temp_unsafe == 1) && (prev_temp_unsafe == 0))
    {
        GetRTCTimeInfo(&hour, &min, &sec);
        GetRTCDateInfo(&date, &month, &year);

        latest_event.sensor = 1;
        latest_event.value = TEMPC;

        latest_event.hour   = hour;
        latest_event.minute = min;
        latest_event.second = sec;

        latest_event.date  = date;
        latest_event.month = month;
        latest_event.year  = year;
    }


    /*
       Gas SAFE -> UNSAFE
    */
    if((gas_unsafe == 1) && (prev_gas_unsafe == 0))
    {
        GetRTCTimeInfo(&hour, &min, &sec);
        GetRTCDateInfo(&date, &month, &year);

        latest_event.sensor = 2;

        latest_event.value = gas_value;

        latest_event.hour   = hour;
        latest_event.minute = min;
        latest_event.second = sec;

        latest_event.date  = date;
        latest_event.month = month;
        latest_event.year  = year;
    }


    /*
       Update previous states AFTER checking
    */
    prev_temp_unsafe = temp_unsafe;
    prev_gas_unsafe  = gas_unsafe;
}

void Normal_Display(void)
{
    s32 hour, minutes, second;
    //u8 date, month, year;

    GetRTCTimeInfo(&hour, &minutes, &second);

    WRITE_LCD_CMD(0x01);

    StrLCD("T:");
    U32LCD(TEMPC);
    StrLCD("C G:");
    U32LCD(gas_value);

    WRITE_LCD_CMD(0xC0);

    if(hour < 10)
        StrLCD("0");

    S32LCD(hour);
    StrLCD(":");

    if(minutes < 10)
        StrLCD("0");

    S32LCD(minutes);
    StrLCD(":");

    if(second < 10)
        StrLCD("0");

    S32LCD(second);
		
}

void Event_Display(void)
{
    WRITE_LCD_CMD(0x01);

    if(latest_event.sensor == 1)
    {
        StrLCD("TEMP UNSAFE");
        WRITE_LCD_CMD(0xC0);
        StrLCD("T:");
        F32LCD(latest_event.value,2);
        //StrLCD(" ");
    }
    else if(latest_event.sensor == 2)
    {
        StrLCD("GAS UNSAFE");
        WRITE_LCD_CMD(0xC0);
        StrLCD("G:");
        U32LCD(latest_event.value);
        //StrLCD(" ");
    }
		else
		{
			StrLCD("NO EVENT");
			return;
		}
     StrLCD(" ");
    /* Display event time */
    if(latest_event.hour < 10) WRITE_LCD_DATA('0');
    U32LCD(latest_event.hour);
    WRITE_LCD_DATA(':');

    if(latest_event.minute < 10) WRITE_LCD_DATA('0');
    U32LCD(latest_event.minute);
    WRITE_LCD_DATA(':');

    if(latest_event.second < 10) WRITE_LCD_DATA('0');
    U32LCD(latest_event.second);
	}


static u32 last_time = 0;
//static u32 event_display_start_time = 0;
//static u8 event_display_active = 0;

void Check_Event_Display(void)
{
    s32 hour, minute, second;
    u32 current_time;

    GetRTCTimeInfo(&hour, &minute, &second);

    current_time = ((u32)hour * 3600) +
                   ((u32)minute * 60) +
                   (u32)second;

    // Start event display every 10 seconds 
    if(latest_event.sensor == 0)
			return ;
       if((current_time - last_time) >= 10)
      { 
        last_time = current_time;

        Event_Display();
				delay_ms(2000);
				 Normal_Display();
    }
}




