#ifndef BMS_H
#define BMS_H

#include "conbits.h"

typedef struct battery_data {
    float voltage;
    float current;
} bms_data;

void bms_begin(void);

// bms_get_data: update BMS data
bms_data bms_get_data(void);

// bms_convert_data: convert BMS data into readable formats:
bms_data bms_convert_data(uint8_t volt, uint8_t curr);

#endif