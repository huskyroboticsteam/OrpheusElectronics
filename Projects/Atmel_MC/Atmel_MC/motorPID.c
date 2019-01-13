/*
 * motorPID.c
 *
 * Created: 1/12/2019 1:42:28 PM
 *  Author: Akhil Avula
 */ 

#include "top.h"

void init_motor() {
	
}

void set_motor_power(void *myPwmDataPtr) {
	pwmMotorData *pwmDataPtr = (pwmMotorData*) myPwmDataPtr;
	int i;
	for (i = 0; i < NUM_MOTORS; i++) {}
		pwmDataPtr->pwmVal[i];
	}
	pwmControl();
}

void pwmControl(uint16_t pwmVal) {
	int i;
	for (i = 0; i < NUM_MOTORS; i++) {
		PWMPIN1 = pwmVal[i];
	}
}

void set_PID() {
	
}

void check_stall() {
	 
}