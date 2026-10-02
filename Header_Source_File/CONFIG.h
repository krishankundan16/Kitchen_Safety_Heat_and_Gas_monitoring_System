#include "types.h"
#ifndef __CONFIG_H
#define __CONFIG_H

void Read_Temperature(void);
void Read_Gas(void);
void Safety_status(void);
#define DEFAULT_TEMP_THRESHOLD 30
#define DEFAULT_GAS_THRESHOLD  500


#define LED_PIN 0
#define BUZZER_PIN 5
#define SW2 2

#endif

