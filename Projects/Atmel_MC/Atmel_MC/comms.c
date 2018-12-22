/*
 * comms.c
 *
 *  Author: Akhil Avula
 */ 

#include "comms.h"
#include "can.h"
/*
txd - pb10
rxd = pb11
*/
void comms(void *myCanDataPtr) {
	canData *canDataPtr = (canData*) myCanDataPtr;
	uint32_t id_value;
	uint8_t *data;
	bool txFlag;
	initTC3();
	if (txFlag) {
		can_tx(id_value, *data, canDataPtr);
		// enable interrupt
	} else {
		can_rx(id_value, *data, canDataPtr);
		// disable interrupt
	}
		
}

void initTC3() {
	
}

static void can_tx(uint32_t id_value, uint8_t *data, canData canDataPtr)
{
	uint32_t i;
	for (i = 0; i < 8; i++)
	{
		canDataPtr.txdata[i] = *data;
		data++;
	}
}

static void can_rx(uint32_t id_value, uint8_t *data, canData canDataPtr)
{
	uint32_t i;
	for (i = 0; i < 8; i++)
	{
		canDataPtr.rxdata[i] = *data;
		data++;
	}
}