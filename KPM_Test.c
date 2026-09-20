#include <lpc21xx.h>
#include "types.h"
#include "KPM.h"

int main()
{
	u32 keyv;
	IODIR0|=255<<8;
	InitKPM();
	keyv = keyscan();
	IOPIN0=(IOPIN0&~(255<<8))|((keyv^0x0f)<<8);
}
