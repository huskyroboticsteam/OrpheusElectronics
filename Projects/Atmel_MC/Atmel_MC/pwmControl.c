/*
 * pwmControl.c
 *
 *  Author: Akhil Avula
 */ 

#include "top.h"
/*
pa8
*/

int SPEED_RES = 255; // input speed resolution
int CLK_FREQ = 12000000; // input clock frequency to PWM block
int PWM_FREQ = 333; //Hz, 100kHz max
int PWM_PERIOD = CLK_FREQ / PWM_FREQ; 

// Compares the pwm values
/*
void pwmControl(void *myPwmDataPtr) {
	pwmMotorData *pwmDataPtr = (pwmMotorData*) myPwmDataPtr;
	int i;
	for (i = 0; i < NUM_MOTORS; i++) {
		PWMPIN = pwmDataPtr->pwmVal[i];
	}
}
*/

/*
void pwmCalculator(void *myPwmDataPtr) {
	pwmMotorData *pwmDataPtr = (pwmMotorData*) myPwmDataPtr;
	// Pololu G2 High-Power Motor Driver 24v21
	int i;
	for (i = 0; i < NUM_MOTORS; i++) {
		pwmDataPtr->pwmMotorData[i] = (pwmDataPtr->pwmMotorData[i])* PWM_PERIOD / SPEED_RES; // to be changed
	}
}
*/

