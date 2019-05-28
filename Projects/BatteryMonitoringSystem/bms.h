#ifndef BMS_H
#define BMS_H

#include "conbits.h"

typedef struct bms_data {
    float voltage;
    float current;
} bms_data;

void bms_begin(void);

void bms_get_data(bms_data *data);

#endif
