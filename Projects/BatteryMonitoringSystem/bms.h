#ifndef BMS_H
#define BMS_H

#include "conbits.h"

typedef struct bms_data {
    float voltage;
    float current;
} bms_data;

// bms_begin: Initialize pins used for ADC current and voltage measurement
void bms_begin(void);

// bms_get_data: Update pointed bms_data structure with voltage and current
// measurements, which are converted automatically. Make sure to measure and
// redefine R_6, R_2, R_SENSE with the actual measurements.
void bms_get_data(bms_data *data);

// adc_get_data: Get adc data at the given channel. In this case, it will
// either be 0xA for voltage sense resistor at RB1 or 0x3 for current sense
// amplifier at RA3.
void adc_get_data(uint16_t *data, uint8_t adc_channel);

// bms_convert_data: Convert 10 bit ADC values for voltage and current
// into float and in units of volts and amperes, respectively.
bms_data bms_convert_data(uint16_t adc_v, uint16_t adc_c);

#endif
