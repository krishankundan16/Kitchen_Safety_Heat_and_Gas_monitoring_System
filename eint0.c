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
	PINSEL0 &=~(3<<2);//
	//cfg p0.1 as EINT0
	PINSEL0 |=(3<<2);
	EXTPOLAR &=~(1<<0); //
	EXTINT = 1<<0; //
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
	WRITE_LCD_CMD(0x01);
	StrLCD("1:RTC 2:Thresh");
	// command for second line
	WRITE_LCD_CMD(0xC0);
	StrLCD("3:Pass 4:Exit");
	delay_ms(1000);
	// Lcd Clear Command
	WRITE_LCD_CMD(0x01);
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
		s32 temp_hr ,temp_min ,temp_sec ;
		s32 temp_day ,temp_mon ,temp_yr ;
		u32 input;
	/*Read current RTC values */
    GetRTCTimeInfo(&temp_hr,&temp_min,&temp_sec);
    GetRTCDateInfo(&temp_day,&temp_mon,&temp_yr);
	// Get Hour by edit 
		WRITE_LCD_CMD(0x01);
		StrLCD("Set TIME (24h)");
		WRITE_LCD_CMD(0x01);
		StrLCD("Enter Hour:");
		input = ReadNum1();
	   U32LCD(input);
		if(input < 24)
			temp_hr = input;
		// Get minutes
		WRITE_LCD_CMD(0x01);
		StrLCD("Set TIME ");
		WRITE_LCD_CMD(0x01);
		StrLCD("Enter Min:");
		input = ReadNum1();
		U32LCD(input);
		if(input < 60)
			temp_min = input;
		//GET second
		
		WRITE_LCD_CMD(0x01);
		StrLCD("Set TIME ");
		WRITE_LCD_CMD(0x01);
		StrLCD("Enter Sec:");
		input = ReadNum1();
		U32LCD(input);
		if(input < 60)
			temp_sec = input;
		//commit time values directly to rtc register
		SetRTCTimeInfo(temp_hr,temp_min,temp_sec);
		
		// Get Day(Date)
		WRITE_LCD_CMD(0x01);
		StrLCD("Set Date");
		WRITE_LCD_CMD(0x01);
		StrLCD("Enter Day:");
		input = ReadNum1();
		U32LCD(input);
		if(input > 0 && input <= 31)
			temp_day = input;
		//GET Month by Edit Menu
		WRITE_LCD_CMD(0x01);
		StrLCD("Set Date");
		WRITE_LCD_CMD(0x01);
		StrLCD("Enter Month:");
		// take input from keypad
		input = ReadNum1();
		U32LCD(input);
		if(input > 0 && input <= 12)
		 temp_mon = input;
		
		// Get year by Edit Menu
		WRITE_LCD_CMD(0x01);
		StrLCD("Set Date");
		WRITE_LCD_CMD(0x01);
		StrLCD("Enter year:");
		// take input from keypad
		input = ReadNum1();
		U32LCD(input);
		if(input >= 2000 && input <= 2099)
		 temp_yr = input;
		
		//commit Date values directly to rtc register
		SetRTCDateInfo(temp_day,temp_mon,temp_yr);
		
		WRITE_LCD_CMD(0x01);
		StrLCD("RTC Updated!");
		delay_ms(1000);
	
/*------------------------------------------------------Edit Threshold Temperature And Gas Value------------------------------------------------*/ 		
}
void edit_threshold(void)
{
	u32 gas_in;
	f32 temp_in;
	// change Temperature by Edit Menu
	  WRITE_LCD_CMD(0x01);
	StrLCD("Set Temp Limit:");
		WRITE_LCD_CMD(0x01);
	StrLCD("Max (C):");
	// take input from keypad
	temp_in= ReadNum1();
	U32LCD(temp_in);
	// Check temperature Condition
	if(temp_in <=100)
	  temp_threshold = temp_in; // put new temp in threshold temp
	
	// Gas threshold edit
	 WRITE_LCD_CMD(0x01);
	StrLCD("Set Gas Limit:");
		WRITE_LCD_CMD(0x01);
	StrLCD("Max (PPM):");
	// take input from keypad
		  gas_in= ReadNum1();
	U32LCD(gas_in);
	if(temp_in <=1000)
	  gas_threshold = gas_in;
	
	 WRITE_LCD_CMD(0x01);
	StrLCD("Limit Saved!");
	delay_ms(1000);
}
