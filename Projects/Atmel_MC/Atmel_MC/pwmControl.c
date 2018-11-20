/*
 * pwmControl.c
 *
 *  Author: Akhil Avula
 */ 

#include "top.h"


int SPEED_RES = 255; // input speed resolution
int CLK_FREQ = 12000000; // input clock frequency to PWM block
int PWM_FREQ = 333; //Hz, 100kHz max
int PWM_PERIOD = CLK_FREQ / PWM_FREQ; 

// Compares the pwm values
void pwmControl(void *myPwmDataPtr) {
	pwmData *pwmDataPtr = (pwmData*) myPwmDataPtr;
	int i;
	for (i = 0; i < NUM_MOTORS; i++) {
		pwmDataPtr->pwmVal[i] = ;
	}
}

void pwmCalculator(void *myPwmDataPtr) {
	pwmData *pwmDataPtr = (pwmData*) myPwmDataPtr;
	// Pololu G2 High-Power Motor Driver 24v21
	int i;
	for (i = 0; i < NUM_MOTORS; i++) {
		pwmDataPtr->pwmData[i] = (pwmDataPtr->pwmData[i])* PWM_PERIOD / SPEED_RES; // to be changed
	}
}


