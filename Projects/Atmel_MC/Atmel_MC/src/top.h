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
#include <asf.h>
#include <string.h>
#include <conf_can.h>

#include "structs.h"
#include "TCB.h"
#include "functions.h"
#include "comms.h"
#include "can.h"
#include "pins.h"

#define NUM_TASKS 6

// Default position PID values (will be fine tuned)
#define DEFAULT_Kp 140 
#define DEFAULT_Ki 20 
#define DEFAULT_Kd 100 

// for pwm
int SPEED_RES = 255; // input speed resolution
int CLK_FREQ = 12000000; // input clock frequency to PWM block
int PWM_FREQ = 333; //Hz, 100kHz max
int PWM_PERIOD = CLK_FREQ / PWM_FREQ;

#endif