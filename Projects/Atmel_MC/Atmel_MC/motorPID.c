/*
 * motorPID.c
 *
 * Created: 1/12/2019 1:42:28 PM
 *  Author: Akhil Avula
 */ 

#include "top.h"

#define MOTOR_MODE_INDEX 4
#define MOTOR_MODE_PID 2
#define MOTOR_MODE_ENABLED 1

uint16_t kp, ki, kd;
int32_t target_pos;
int32_t max_pos;
int32_t pid_target; //position PID target (current)
uint8_t pid_target_inc; 

uint16_t motor_dir;
uint16_t pwm_val;
uint16_t pid_runs; 
uint16_t motor_power;
uint16_t motor_max_current;
uint8_t motor_mode; 

void motorPID(void *myPwmDataPtr) {
	pwmMotorData *pwmDataPtr = (pwmMotorData*) myPwmDataPtr;
	init_motor();
	set_motor_power(pwmDataPtr->motorPower);
}


void init_motor() {
	kp = DEFAULT_Kp;
	ki = DEFAULT_Ki;
	kd = DEFAULT_Kd;
	target_pos = 0;
	max_pos = 1024;
	pid_target = 0;
	pid_target_inc = 0;

	pid_runs;
	motor_power;
	motor_max_current;
	motor_mode;
}

void set_motor_power(void *myPwmDataPtr) {
	pwmMotorData *pwmDataPtr = (pwmMotorData*) myPwmDataPtr;
	if (pwmDataPtr->motorPower > 1023) {
		pwmDataPtr->motorPower = 1023;
	}
	if (pwmDataPtr->motorPower < -1023) {
		pwmDataPtr->motorPower = -1023;
	}
	if(pwmDataPtr->motorPower == 0) { //Shut down the motor if it isn't enabled or power is 0
		pwmControl(0, pwm_val);
		PWMPIN &= (1<<pwm_val);
		return;
	}
	if(pwmDataPtr->motorPower < 0){
		if(DIRPIN & (1<<motor_dir)){
			DIRPIN &= ~(1<<motor_dir); //Reverse
		}
		pwmDataPtr->motorPower = -pwmDataPtr->motorPower; //PWM is always positive
	} else {
		if(!(DIRPIN & (1<<DIRPIN))){
			DIRPIN |= (1<<DIRPIN); //Forward
		}
	}
	pwmControl(pwmDataPtr->motorPower, PWMPIN);
}

void pwmControl(uint16_t pwmVal, uint8_t pin) {
	pwmVal &= 1023;
	pin = pwmVal;
}

void set_PID(uint16_t p1, uint16_t i1, uint16_t d1) {
	if (p1 != 0) {
		kp = p1;
	}
	if (i1 != 0) {
		ki = i1;
	}
	if (d1 != 0) {
		kd = d1;
	}
}

void check_stall() {
	
}

void set_target_position(uint32_t pos) {
	target_pos = pos;
}

uint32_t get_target_position() {
	return target_pos;
}

