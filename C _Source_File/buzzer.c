#include <lpc21xx.h>
#include "delay.h"
#include "types.h"
#include "CONFIG.h"
	
void BUZZER_ON()
{
	// p0.1 as output
	IODIR0 |=(1<<BUZZER_PIN);
	// buzzer on
	IOSET0=(1<<BUZZER_PIN);
}
void BUZZER_OFF()
{
	// p0.1 as output
	IODIR0 |=(1<<BUZZER_PIN);
	//buzzer on
	IOCLR0=1<<BUZZER_PIN;
}
void LED_ON()
{
	//LED p0.0 as output
	IODIR0 |=(1<<LED_PIN);
	// LED ON
	IOCLR0 =1<<LED_PIN;
}
void LED_OFF()
{
	//LED as output
	IODIR0 |=(1<<LED_PIN);
	// LED OFF
	IOSET0 =1<<LED_PIN;
}


