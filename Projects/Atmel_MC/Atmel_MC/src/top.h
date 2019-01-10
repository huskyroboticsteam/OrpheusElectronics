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

#define PWMPIN PIN_PA08
#define CANRXPIN PIN_PB11
#define CANTXPIN PIN_PB10

#endif