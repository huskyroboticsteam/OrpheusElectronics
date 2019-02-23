/*
 * structs.h
 *
 * Created: 10/25/2018 7:38:26 PM
 *  Author: Akhil Avula
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

#define NUM_MOTORS 3 
#define PWM_COMPARE 248000

typedef struct {
	int16_t motorPower;
	int16_t pwmVal[NUM_MOTORS];
} pwmMotorData;

typedef struct {
	int encoderRaw[NUM_MOTORS];
} encoderData;

typedef struct {
	uint16_t kp;
	uint16_t ki;
	uint16_t kd;
	uint16_t canMsg;
	int txdata[16];
	int rxdata[16];
} canData; // comms

// typedef struct {} potData; // speed control

#endif /* STRUCTS_H_ */