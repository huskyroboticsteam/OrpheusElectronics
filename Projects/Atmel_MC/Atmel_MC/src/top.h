/*
 * top.h
 *
 *  Author: Akhil Avula
 */ 

#ifndef TOP_H_
#define TOP_H_

#include <can.h>
#include <stdio.h>
#include <interrupt.h>

#include "structs.h"
#include "TCB.h"
#include "functions.h"

#define NUM_TASKS 6

#define ENCPIN[3] {PIN_PA00, PIN_PA01, PIN_PA02}
#define LIMIT1PIN //?
#define LIMIT2PIN //?

#define PWMPIN1 PIN_PA08
#define PWMPIN2 PIN_PA09
#define CANRXPIN PIN_PB11
#define CANTXPIN PIN_PB10

// for pwm
int SPEED_RES = 255; // input speed resolution
int CLK_FREQ = 12000000; // input clock frequency to PWM block
int PWM_FREQ = 333; //Hz, 100kHz max
int PWM_PERIOD = CLK_FREQ / PWM_FREQ;

#endif