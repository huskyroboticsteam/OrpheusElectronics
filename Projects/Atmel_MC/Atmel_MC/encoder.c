/*
 * encoder.c
 *
 *  Author: Akhil Avula
 */ 

#include "top.h"

volatile int32_t encoder_ticks; //Raw encoder ticks

void readEncoders(void *myEncoderDataPtr) {
	encoderData *encoderDataPtr = (encoderData*) myEncoderDataPtr;
	if (LIMIT1PIN > 0) {
		resetEncoders();	
	}
	if (LIMIT2PIN > 0) {
		set_encoder_ticks(encoder_ticks--);	
	}
	int32_t temp = get_encoder_ticks();
	encoderDataPtr->encoderRaw[0] = temp;
	encoderDataPtr->encoderRaw[1] = temp;
	encoderDataPtr->encoderRaw[2] = temp;
	// for (int i = 0; i < NUM_MOTORS; i++) {
	// 	encoderDataPtr->encoderRaw[i] = ENCPIN[i];
	// }
}

void resetEncoders() {
	set_encoder_ticks(0);
}

ISR(INT6_vect) {
	set_encoder_ticks(encoder_ticks--);
}

ISR(INT7_vect) {
	set_encoder_ticks(encoder_ticks++);
}

void set_encoder_ticks(int32_t ticks) {
	encoder_ticks = ticks;
}

int32_t get_encoder_ticks() {
	return encoder_ticks;
}
