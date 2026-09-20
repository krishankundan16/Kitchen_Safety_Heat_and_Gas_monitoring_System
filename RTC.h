#include "types.h"
void RTC_Init(void);
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second);
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second);
void DisplayRTCTime(u32 hour, u32 minute, u32 second);
void SetRTCDateInfo(u32 date, u32 month, u32 year);
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year);
void DisplayRTCDate(u32 date, u32 month, u32 year);
void SetRTCDay(u32 dow);
void GetRTCDay(s32 *dow);
void DisplayRTCDay(u32 day);

