#include "CONFIG.h"
#include <lpc21xx.h>
#include "types.h"
#include "LM35.h"
#include "buzzer.h"
#include "MQ2.h"
#include "LCD.h"
#include "delay.h"
#include "flash.h"

u32 buzzer_muted = 0;
u32 temp_threshold = DEFAULT_TEMP_THRESHOLD;
u32 gas_threshold = DEFAULT_GAS_THRESHOLD;
f32 TEMPC;
u32 gas_value;
u8 temp_unsafe;
u8 gas_unsafe;	

void Read_Temperature(void)
{
	// Read temperature 
	TEMPC = LM35tc();
	// display temperature in celsieus
	WRITE_LCD_CMD(0x88);
	WRITE_LCD_DATA(' ');
	//WRITE_LCD_DATA('T');
	//WRITE_LCD_DATA(':');
	F32LCD(TEMPC,2);
  // DISPLAY CELSIEUS
	WRITE_LCD_DATA(0xDF);
	WRITE_LCD_DATA('C');
}

void Read_Gas(void)
{
	//read gas value
  gas_value = MQ2_Read();
	//display gas_value on Lcd
	WRITE_LCD_CMD(0xCA);
	WRITE_LCD_DATA(' ');
	WRITE_LCD_DATA('G');
	WRITE_LCD_DATA(':');
	U32LCD(gas_value);
}

void Safety_status(void)
{
	TEMPC = LM35tc();
	gas_value = MQ2_Read();
	IODIR0 &= ~(1<<SW2);
	//temperature safety check
	if(TEMPC >= temp_threshold)
		temp_unsafe = 1;
	else
		temp_unsafe = 0;
	
	//gas safety check
	if(gas_value >=gas_threshold)
		gas_unsafe = 1;
	else
		gas_unsafe = 0;
	// HAzard detected
	if(temp_unsafe || gas_unsafe)
	{
		//LED On
		LED_ON();
		BUZZER_ON();
		//switch pressed
		if((IOPIN0 &(1<<SW2))==0)
		{
			buzzer_muted = 1;
			//BUZZER OFF
			BUZZER_OFF();
		}
		if(buzzer_muted == 0)
		{
			BUZZER_ON();
		}
	}		
	else
	{
		// safe
		LED_OFF();
		BUZZER_OFF();
		buzzer_muted = 0;
	}
	
}


