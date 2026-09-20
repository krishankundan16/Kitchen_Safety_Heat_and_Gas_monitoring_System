#include "types.h"
#include "ADC.h"
#include "ADC_defines.h"

f32 LM35tc(void)
{
	u32 dval;
	f32 eAR;
	// p0.28 cfg for Lm35 Sensor
	Read_ADC(CH1,&dval,&eAR);
	return (eAR*100);
}
f32 LM35tf(void)
{
	f32
	tempc;
	tempc=LM35tc();
	return (tempc*(1.8)+32);
}




