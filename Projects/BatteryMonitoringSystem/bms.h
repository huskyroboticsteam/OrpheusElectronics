#ifndef BMS_H
#define BMS_H

#include "conbits.h"

typedef struct bms_data {
    float voltage;
    float current;
} bms_data;

void bms_begin(void);

void bms_get_data(bms_data *data);

void adc_get_data(uint16_t *data, uint8_t adc_channel);

bms_data bms_convert_data(uint16_t adc_v, uint16_t adc_c);

#endif
