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
void pwmControl(uint16_t pwmVal, uint8_t pin); // Compares the pwm values with the compare val
// void pwmCalculator(void *myPwmDataPtr); // control calculator
// void comms(void *myCanDataPtr);
// void limit_switch(void); // warning system
void emergencyStop(void);
void initTC3(void);
void tx(uint32_t id_value, uint8_t *data, void *canDataPtr);
void rx(uint32_t id_value, uint8_t *data, void *canDataPtr);
void set_encoder_ticks(int32_t ticks);
int32_t get_encoder_ticks(void);
void set_motor_power(void *myPwmDataPtr);
void init_motor(void);
void resetEncoders(void);
void executeTask(TCB* node);
void addTask(TCB* node); 
void removeTask(TCB* node);
#endif /* FUNCTIONS_H_ */