#include "types.h"

extern volatile u32 edit_mode;
void eint0_isr(void)__irq;
void eint0_enable(void);
void Edit_Menu(void);
void edit_rtc(void);
void edit_time(void);
void edit_date(void);
void edit_hour(void);
void edit_min(void);
void edit_sec(void);
void edit_Hr_Min_Sec(void);
void edit_day(void);
void edit_month(void);
void edit_year(void);
void edit_day_month_year(void);
void edit_threshold(void);
void invalid_input(void);
#define EINT0_SW1 1
