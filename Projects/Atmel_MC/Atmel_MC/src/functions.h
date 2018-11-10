/*
 * functions.h
 *
 * Created: 10/25/2018 8:50:28 PM
 *  Author: Akhil Avula
 */ 


#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void initialize(void);
void scheduler(void);
void encoder(void *myEncoderDataPtr); // hardware?
void pwmControl(void *myPwmDataPtr); 
void pwmCalculator(void *myPwmDataPtr); // control calculator
void potRead(void *myPotDataPtr); // ??
void comms(void *myCanDataPtr);
void limit_switch(void); // Interrupt based?, warning system
void emergencyStop(void);

#endif /* FUNCTIONS_H_ */