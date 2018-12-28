#ifndef UTIL_H
#define UTIL_H

int16_t min(int16_t a, int16_t b);
int16_t max(int16_t a, int16_t b);
uint16_t int_abs(int16_t x);
void set_LED(uint8_t L, uint8_t state);
void update_LEDS(uint16_t count);
void read_string(char *buffer, char until);

#define false 0
#define true 1
#define FALSE 0
#define TRUE 1

#endif