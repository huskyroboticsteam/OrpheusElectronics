#include "stm32f1xx_hal.h"
#include "encoderCount.h"
#include "main.h"
#include <stdio.h>

char LAST_A = 0;
char LAST_B = 0;

uint16_t ENC_DIR = 0;
uint16_t ENC_INIT = 0;
uint16_t ENC_DEBUG = 0;

int32_t ENC_COUNT = 0;

/*
 * Initializes the encoder counter.
 * Must be called before FOUND_EDGE.
 */
void ENC_CNT_INIT() {
    LAST_A = (char)HAL_GPIO_ReadPin(ENC_A_GPIO_Port, ENC_A_Pin);
    LAST_B = (char)HAL_GPIO_ReadPin(ENC_B_GPIO_Port, ENC_B_Pin);
    ENC_INIT = 1;
}

/*
 * Enables output to debug pin.
 * Constant CMP_ENC_DEBUG must be
 * set also for debug to work.
 */
void ENC_DEBUG_PIN_INIT() { ENC_DEBUG = 1; }

/*
 * Call when A Edge has been detected
 */
void ENC_CNT_FOUND_EDGE_A() {
    if (!ENC_INIT) { return; }
		// Encoder Logic
		// We know currently that A = !LAST_A
		// DIR = LB & ~A || ~LB & A
    if ((LAST_B && LAST_A) || (!LAST_B && !LAST_A)) { ENC_COUNT++; }
		else { ENC_COUNT--; }
    LAST_A = !LAST_A;
		#if CMP_ENC_DEBUG
    if (ENC_DEBUG) {
        if (HAL_GPIO_ReadPin(ENC_A_GPIO_Port, ENC_A_Pin)) {
            HAL_GPIO_WritePin(ENC_DEBUG_PIN_GPIO_Port, ENC_DEBUG_PIN_Pin, GPIO_PIN_SET);       
        } else {
            HAL_GPIO_WritePin(ENC_DEBUG_PIN_GPIO_Port, ENC_DEBUG_PIN_Pin, GPIO_PIN_RESET);
        }
    }
    #endif
}

/*
 * Call when B Edge has been detected
 */
void ENC_CNT_FOUND_EDGE_B() {
    if (!ENC_INIT) { return; }
		// Encoder logic
		// We know currently that B = !LAST_B
		// DIR = LA && B || ~LA && B
		if ((LAST_B && LAST_A) || (!LAST_A && !LAST_B)) { ENC_COUNT++; }
		else { ENC_COUNT--; }
    LAST_B = !LAST_B;
    #if CMP_ENC_DEBUG
    if (ENC_DEBUG) {
        if (HAL_GPIO_ReadPin(ENC_B_GPIO_Port, ENC_B_Pin)) {
            HAL_GPIO_WritePin(ENC_DEBUG_PIN_GPIO_Port, ENC_DEBUG_PIN_Pin, GPIO_PIN_SET);       
        } else {
            HAL_GPIO_WritePin(ENC_DEBUG_PIN_GPIO_Port, ENC_DEBUG_PIN_Pin, GPIO_PIN_RESET);
        }
    }
    #endif
}

/*
 * Sets the encoder direction. 
 * Must be called before ENC_CNT_INIT.
 */
void ENC_SET_DIR(ENC_DIR_t DIRECTION) {
    if (ENC_INIT) { return; }
    if (DIRECTION == ENC_CW) { ENC_DIR = 0; }
    if (DIRECTION == ENC_CCW) { ENC_DIR = 1; }
}
