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
void readEncoders(void *myEncoderDataPtr);
void pwmControl(void *myPwmDataPtr); // Compares the pwm values with the compare val
void pwmCalculator(void *myPwmDataPtr); // control calculator
void potRead(void *myPotDataPtr); // ??
void comms(void *myCanDataPtr);
void limit_switch(void); // warning system
void emergencyStop(void);

#endif /* FUNCTIONS_H_ */