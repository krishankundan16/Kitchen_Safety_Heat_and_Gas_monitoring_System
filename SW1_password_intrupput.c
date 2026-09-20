#include <lpc214x.h>
#include "delay.h"
#include "LCD.h"
#include "KPM.h"
u32 password = 1234;
volatile u8 edit_request = 0;
void EINT3_ISR(void)__irq
{
	edit_request=1;
	EXTINT = (1<<3); //clear EITINT3
	VICVectAddr = 0; //end of intrrupt
}
void EINT3_Init(void)
{
	//p0.20 as EINT3
	PINSEL1 &=(3<<8);
	PINSEL1 |=(3<<8);
	//edge triggering
	EXTMODE |=(1<<3);
	//falling edge
	EXTPOLAR &= ~(1<<3);
	//EINT3 as select irq
	VICIntSelect &=~(1<<17);
	//VIC SLOT0 for EINT3(channel 17)
	VICVectCntl0 = 0x20 | 17;
	VICVectAddr0 = (unsigned long)EINT3_ISR;
	
	//Enable EINT3
	VICIntEnable |= (1<<17);
	//Clear any pending interrupt
	EXTINT = (1<<3);
}
void Editpassword(void)
{
	u32 new_password;
	WRITE_LCD_CMD(0x01);
	StrLCD("New Password");
	new_password = ReadNum();
	password = new_password ;
	
	WRITE_LCD_CMD(0x01);
	StrLCD("Password Saved");
	
	delay_ms(1000);
}
	
	