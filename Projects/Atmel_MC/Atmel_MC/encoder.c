/*
 * encoder.c
 *
 *  Author: Akhil Avula
 */ 

#include "top.h"

volatile int32_t encoder_ticks; //Raw encoder ticks

void readEncoders(void *myEncoderDataPtr) {
	encoderData *encoderDataPtr = (encoderData*) myEncoderDataPtr;
	for (int i = 0; i < NUM_MOTORS; i++) {
		encoderDataPtr->encoderRaw[i] = ENCPIN[i];
	}
}

ISR(INT6_vect) {
	encoder_ticks--;
}

ISR(INT7_vect) {
	encoder_ticks++;
}

void set_encoder_ticks(int32_t ticks) {
	encoder_ticks = ticks;
}

int32_t get_encoder_ticks() {
	return encoder_ticks;
}
