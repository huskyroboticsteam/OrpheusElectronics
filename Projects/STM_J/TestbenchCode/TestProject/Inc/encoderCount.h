#ifndef __ENCODER_CNT__
#define __ENCODER_CNT__

// Otherwise it doesn't have a typedef for int32_t
#include "stm32f1xx_hal.h"

#define CMP_ENC_DEBUG 0

typedef enum { ENC_CW, ENC_CCW } ENC_DIR_t;

extern int32_t ENC_COUNT;

void ENC_CNT_INIT(void);
void ENC_DEBUG_PIN_INIT(void);
void ENC_CNT_FOUND_EDGE_A(void);
void ENC_CNT_FOUND_EDGE_B(void);

#endif /* __ENCODER_CNT__ */
