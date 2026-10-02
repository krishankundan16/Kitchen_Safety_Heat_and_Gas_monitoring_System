#include <lpc21xx.h>
#include "types.h"
#include "delay.h"
#include "KPM.h"
#include "LCD.h"
#include "RTC.h"
#include "RTC_define.h"
#include "CONFIG.h"
#include "ADC.h"
#include "security.h"
#include "eint0.h"
#include "LCD_defines.h"

#define EINT0_CHNO 14
volatile u32 edit_mode =0;

void eint0_isr(void)__irq
{
	// cfg p0.1 as SW1
	if(((IOPIN0>>EINT0_SW1)&1)==0)
	{
		edit_mode =1;
	}
	// End of isr
	VICVectAddr = 0;
	//clear extint0 flag
	EXTINT = 1<<0;
	
}

void eint0_enable(void)
{
	PINSEL0 &=~(3<<2);
	//cfg p0.1 as EINT0
	PINSEL0 |=(3<<2);
	EXTPOLAR &=~(1<<0); 
	EXTINT = 1<<0; 
	//select extint0 as irq
	VICIntSelect &= ~(0<<EINT0_CHNO);
	//enable extint0 source
	VICIntEnable  |= 1<<EINT0_CHNO;
	//load isr address
	VICVectAddr0 =(u32)eint0_isr;
	//select slot for extint0
	VICVectCntl0 =(1<<5)|EINT0_CHNO;
	//select edgetriggering
	EXTMODE =1<<0;
}


/*---------------------------------------------------Edit Menu open--------------------------------------------------------------------------------------*/
void Edit_Menu(void)
{
	// Declare choice
	u32 choice;
	// clear Lcd 
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("1:RTC 2:Thresh");
	// command for  second line
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	StrLCD("3:Pass 4:Exit");
	delay_ms(1000);
	// Lcd Clear Command
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("CHOICE=");
	// Enter The Choice Value from keypad
	choice = ReadNum1();
	U32LCD(choice);
	switch(choice)
	{
		case 1: edit_rtc(); // Edit Real Time and Date Function
		          break;
		case 2: edit_threshold(); //Edit Threshold Temperature and Gas value
		           break;
		case 3: change_password(); // Change Password
		           break;
		case 4: WRITE_LCD_CMD(0x01);
              StrLCD("Exiting...");
              delay_ms(1000);
              edit_mode = 0;
    default: break;
	}
}
/*----------------------------------------------Edit Time And Date Function--------------------------------------------------------------------------*/
void edit_rtc(void)	
{
		  // Declare choice
	u32 choice;
	// clear Lcd 
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("1:Time 2:Date");
	// command for second line
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	StrLCD("3:Exit");
	delay_ms(1000);
	// Lcd Clear Command
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("CHOICE=");
	// Enter The Choice Value from keypad
	choice = ReadNum1();
	U32LCD(choice);
	switch(choice)
	{
		case 1: edit_time(); // Edit Real Time 
		          break;
		case 2: edit_date(); //Edit Date
		           break;
		case 3: WRITE_LCD_CMD(CLEAR_LCD);
               StrLCD("Exiting...");
               delay_ms(1000);
               edit_mode = 0;
        default: break;
	}
}

void edit_time()
{
  // Declare choice
	u32 choice;
	// clear Lcd 
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("1:Hour 2:Min");
	// command for second line
	WRITE_LCD_CMD(GOTO_LINE2_POS0);
	StrLCD("3:Sec 4:All");
	delay_ms(1000);
	// Lcd Clear Command
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("CHOICE=");
	// Enter The Choice Value from keypad
	choice = ReadNum1();
	U32LCD(choice);
	switch(choice)
	{
		case 1: edit_hour(); // Edit Hour
		          break;
		case 2: edit_min(); //Edit Minute
		           break;
		case 3: edit_sec(); // Edit second
		           break;
		case 4: edit_Hr_Min_Sec();
		          break;
		default: WRITE_LCD_CMD(CLEAR_LCD);
                 StrLCD("Exiting...");
                  delay_ms(1000);
                  edit_mode = 0;
                    break;
	 }
}

void edit_hour()
{
   s32 temp_hr ,temp_min ,temp_sec ;
   u32 input;
   /*Read current RTC values */
    GetRTCTimeInfo(&temp_hr,&temp_min,&temp_sec);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter HR(0-23):");
	  input = ReadNum1();
	  if(input<24)
	  {
	   U32LCD(input);
	   temp_hr = input;
	   break;
	  }
	  else
	  {
	    invalid_input();
	  }
	}
		//commit time values directly to rtc register
		SetRTCTimeInfo(temp_hr,temp_min,temp_sec);
	   WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("Hour Updated!");
		delay_ms(1000);

}

void edit_min()
{
  s32 temp_hr ,temp_min ,temp_sec ;
   u32 input;
   /*Read current RTC values */
    GetRTCTimeInfo(&temp_hr,&temp_min,&temp_sec);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Min(0-59):");
	  input = ReadNum1();
	  if(input<60)
	  {
	   U32LCD(input);
	   temp_min = input;
	   break;
	  }
	  else
	  {
	    invalid_input();
	  }
	}
		//commit time values directly to rtc register
		SetRTCTimeInfo(temp_hr,temp_min,temp_sec);
	   WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("Min Updated!");
		delay_ms(1000);

}

void edit_sec()
{
  s32 temp_hr ,temp_min ,temp_sec ;
   u32 input;
   /*Read current RTC values */
    GetRTCTimeInfo(&temp_hr,&temp_min,&temp_sec);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Sec(0-59):");
	  input = ReadNum1();
	  if(input<60)
	  {
	   U32LCD(input);
	   temp_sec = input;
	   break;
	  }
	  else
	  {
	    invalid_input();
	  }
	}
		//commit time values directly to rtc register
		SetRTCTimeInfo(temp_hr,temp_min,temp_sec);
	   WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("sec Updated!");
		delay_ms(1000);

}

void edit_Hr_Min_Sec()
{
 s32 temp_hr ,temp_min ,temp_sec ;
   u32 input;
   /*Read current RTC values */
    GetRTCTimeInfo(&temp_hr,&temp_min,&temp_sec);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter HR(0-23):");
	  input = ReadNum1();
	  if(input<24)
	  {
	   U32LCD(input);
	   temp_hr = input;
	   break;
	  }
	  else
	  {
	    invalid_input();
	  }
	}

	// Get Minutes
		while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Min(0-59):");
	  input = ReadNum1();
	  if(input<60)
	  {
	   U32LCD(input);
	   temp_min = input;
	   break;
	  }
	  else
	  {
	    invalid_input();
	  }
	}

	//Get Second
		while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Sec(0-59):");
	  input = ReadNum1();
	  if(input<60)
	  {
	   U32LCD(input);
	   temp_sec = input;
	   break;
	  }
	  else
	  {
	    invalid_input();
	  }
	}
		//commit time values directly to rtc register
	SetRTCTimeInfo(temp_hr,temp_min,temp_sec);
	WRITE_LCD_CMD(CLEAR_LCD);
    StrLCD("Time Updated!");
	delay_ms(1000);

}

void edit_date()
{
   // Declare choice
	u32 choice;
	// clear Lcd 
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("1:Day 2:Month");
	// command for second line
	WRITE_LCD_CMD(0xC0);
	StrLCD("3:Year 4:All");
	delay_ms(1000);
	// Lcd Clear Command
	WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("CHOICE=");
	// Enter The Choice Value from keypad
	choice = ReadNum1();
	U32LCD(choice);
	switch(choice)
	{
		case 1: edit_day(); // Edit Hour
		          break;
		case 2: edit_month(); //Edit Minute
		           break;
		case 3: edit_year(); // Edit second
		           break;
		case 4: edit_day_month_year();
		          break;
		default: WRITE_LCD_CMD(CLEAR_LCD);
                 StrLCD("Exiting...");
                  delay_ms(1000);
                  edit_mode = 0;
                    break;
	 }
}

void edit_day()
{
  	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GetRTCDateInfo(&temp_day,&temp_mon,&temp_yr);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter DAY(0-31):");
	  input = ReadNum1();
	  if(input >0 && input <= 31)
	  {
	   U32LCD(input);
	   temp_day = input;
	   break;
	  }
	  else
	  {
	   invalid_input();
	  }
	}
	//commit Date values directly to rtc register
		SetRTCDateInfo(temp_day,temp_mon,temp_yr);
		
		WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("DAY Updated!");
		delay_ms(1000);

}

void edit_month()
{
  	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GetRTCDateInfo(&temp_day,&temp_mon,&temp_yr);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Mon(1-12):");
	  input = ReadNum1();
	  if(input >0 && input <= 12)
	  {
	   U32LCD(input);
	   temp_mon = input;
	   break;
	  }
	  else
	  {
	   invalid_input();
	  }
	}
	//commit Date values directly to rtc register
		SetRTCDateInfo(temp_day,temp_mon,temp_yr);
		
		WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("Month Updated!");
		delay_ms(1000);

}

void edit_year()
{
    s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GetRTCDateInfo(&temp_day,&temp_mon,&temp_yr);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Year(2s):");
	  input = ReadNum1();
	  if(input >= 2000 && input <= 2099)
	  {
	   U32LCD(input);
	   temp_yr = input;
	   break;
	  }
	  else
	  {
	   invalid_input();
	  }
	}
	//commit Date values directly to rtc register
		SetRTCDateInfo(temp_day,temp_mon,temp_yr);
		
		WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("Year Updated!");
		delay_ms(1000);

}

void edit_day_month_year()
{
  	s32 temp_day,temp_mon,temp_yr;
	u32 input;
	GetRTCDateInfo(&temp_day,&temp_mon,&temp_yr);
	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter DAY(0-31):");
	  input = ReadNum1();
	  if(input >0 && input <= 31)
	  {
	   U32LCD(input);
	   temp_day = input;
	   break;
	  }
	  else
	  {
	   invalid_input();
	  }
	}

	// Get Month
		while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Mon(1-12):");
	  input = ReadNum1();
	  if(input >0 && input <= 12)
	  {
	   U32LCD(input);
	   temp_mon = input;
	   break;
	  }
	  else
	  {
	   invalid_input();
	  }
	 }

	 // Get Year
	 	while(1)
	{
	  WRITE_LCD_CMD(CLEAR_LCD);
	  StrLCD("Enter Year(2s):");
	  input = ReadNum1();
	  if(input >= 2000 && input <= 2099)
	  {
	   U32LCD(input);
	   temp_yr = input;
	   break;
	  }
	  else
	  {
	   invalid_input();
	  }
	}
	//commit Date values directly to rtc register
		SetRTCDateInfo(temp_day,temp_mon,temp_yr);
		
		WRITE_LCD_CMD(CLEAR_LCD);
		StrLCD("Date Updated!");
		delay_ms(1000);
}	
/*------------------------------------------------------Edit Threshold Temperature And Gas Value------------------------------------------------*/ 		

void edit_threshold(void)
{
	u32 gas_in;
	f32 temp_in;
	// change Temperature by Edit Menu
	  WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("Set Temp Limit:");
		WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("Max (C):");
	// take input from keypad
	temp_in= ReadNum1();
	U32LCD(temp_in);
	// Check temperature Condition
	if(temp_in <=100)
	{
	  temp_threshold = temp_in; // put new temp in threshold temp
	 }
	// Gas threshold edit
	 WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("Set Gas Limit:");
		WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("Max (PPM):");
	// take input from keypad
		  gas_in= ReadNum1();
	U32LCD(gas_in);
	if(temp_in <=1000)
	{
	  gas_threshold = gas_in;
	 
	 }
	 WRITE_LCD_CMD(CLEAR_LCD);
	StrLCD("Limit Saved!");
	delay_ms(1000);
}

// define invalid input
void invalid_input(void)
{
   WRITE_LCD_CMD(CLEAR_LCD);
   StrLCD("Invalid input");
   delay_ms(1000);
}
