/*
 * comms.c
 *
 *  Author: Akhil Avula
 */ 
// http://ww1.microchip.com/downloads/en/AppNotes/Atmel-42464-SAMC21-CAN-BUS-Firmware_ApplicationNote_AT6493.pdf

#include "top.h"

#define CAN_MODULE CAN0#define CAN_TX_MUX_SETTING MUX_PA24G_CAN0_TX
#define CAN_TX_PIN PIN_PA24G_CAN0_TX
#define CAN_RX_MUX_SETTING MUX_PA25G_CAN0_RX
#define CAN_RX_PIN PIN_PA25G_CAN0_RX
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
	struct system_pinmux_config pin_config;
	system_pinmux_get_config_defaults(&pin_config);
	pin_config.mux_position = CAN_TX_MUX_SETTING;
	system_pinmux_pin_set_config(CAN_TX_PIN, &pin_config);
	pin_config.mux_position = CAN_RX_MUX_SETTING;
	system_pinmux_pin_set_config(CAN_RX_PIN, &pin_config);
	
	struct can_config config_can;
	can_get_config_defaults(&config_can);
	can_init(&can_instance, CAN_MODULE, &config_can);
	can_switch_operation_mode(&can_instance, CAN_OPERATION_MODE_NORMAL_OPERATION);
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_CAN0);
}

static void can_tx(uint32_t id_value, uint8_t *data, canData canDataPtr)
{
	uint8_t i;
	// can_get_tx_buffer_element_defaults(&canDataPtr);

	for (i = 0; i < 16; i++)
	{
		canDataPtr.txdata[i] = *data;
		data++;
	}
	// can_set_tx_buffer_element(&can_instance, &tx_element, CAN_TX_BUFFER_INDEX);
	// can_tx_transfer_request(&can_instance, 1 << CAN_TX_BUFFER_INDEX);
}

static void can_rx(uint32_t id_value, uint8_t *data, canData canDataPtr)
{
	uint8_t i;
	for (i = 0; i < 16; i++)
	{
		canDataPtr.rxdata[i] = *data;
		data++;
	}
}