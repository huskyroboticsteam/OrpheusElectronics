/*
 * structs.h
 *
 * Created: 10/25/2018 7:38:26 PM
 *  Author: Akhil Avula
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

#define NUM_MOTORS 3 

typedef struct {
	int pwmVal[NUM_MOTORS];
} pwmData;

typedef struct {
	int encoderRaw[NUM_MOTORS];
} encoderData;

typedef struct {
	
} canData; // comms

typedef struct {
	
} potData; // speed control

#endif /* STRUCTS_H_ */