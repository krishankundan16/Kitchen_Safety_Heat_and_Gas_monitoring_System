#include "types.h"
#include "ADC.h"
#include "ADC_defines.h"

u32 dval;
f32 eAR;
u32 chno;
int main()
{
	Init_ADC();
	while(1)
	{
		Read_ADC(CH0,&dval,&eAR);
	}
}
		