#include "types.h"
#ifndef __CONFIG_H
#define __CONFIG_H

void Read_Temperature(void);
void Read_Gas(void);
void Safety_status(void);
#define DEFAULT_TEMP_THRESHOLD 40
#define DEFAULT_GAS_THRESHOLD  500

extern u32 temp_threshold;
extern u32 gas_threshold;
#define LED_PIN 0
#define BUZZER_PIN 3
#define SW2 2

#endif

