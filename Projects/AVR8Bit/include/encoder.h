#ifndef ENCODER_H
#define ENCODER_H

uint32_t get_encoder_ticks();
uint16_t get_encoder_velocity();
void init_encoder();
void reset_encoder();

#endif