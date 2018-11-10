/*
 * encoder.c
 *
 *  Author: Akhil Avula
 */ 

#include "top.h"

void readEncoders(void *myEncoderDataPtr) {
	encoderData *encoderDataPtr = (encoderData*) myEncoderDataPtr;
	for (int i = 0; i < NUM_MOTORS; i++) {
		encoderDataPtr->encoderRaw[i];
	}
}

