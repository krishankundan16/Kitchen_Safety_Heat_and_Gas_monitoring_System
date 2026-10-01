#ifndef EVENT_H
#define EVENT_H

#include "types.h"

typedef struct
{
	u8 sensor;
	f32 value;
	
	u8 hour;
	u8 minute;
	u8 second;
	
	u8 date;
	u8 month;
	u32 year;
} SafetyEvent;

extern SafetyEvent latest_event;

void Check_New_Event(void);
void Normal_Display(void);
void Event_Display(void);
void Check_Event_Display(void);

#endif
