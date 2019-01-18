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

uint16_t pid_runs; 
uint16_t motor_power;
uint16_t motor_max_current;
uint8_t motor_mode; 

void init_motor() {
	kp = ;
	ki = ;
	kd = ;
	target_pos = 0;
	max_pos = 1024;
	pid_target = 0;
	pid_target_inc = 0;

	uint16_t pid_runs;
	uint16_t motor_power;
	uint16_t motor_max_current;
	uint8_t motor_mode;
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

