#include "types.h"

extern volatile u32 edit_mode;
void eint0_isr(void)__irq;
void eint0_enable(void);
void Edit_Menu(void);
void edit_rtc(void);
void edit_threshold(void);
#define EINT0_SW1 1
