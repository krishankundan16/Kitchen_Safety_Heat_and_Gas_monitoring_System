#include <lpc21xx.h>
#include "MQ2.h"
#include "ADC.h"
#include "types.h"
#include "ADC_defines.h"

#define MQ2_CHANNEL CH2

u32 MQ2_Read(void)
{
	u32 adc_value;
	f32 voltage;
	// p0.29 cfg for Mq2 sensor
	Read_ADC(MQ2_CHANNEL,&adc_value,&voltage);
	return adc_value;
}



