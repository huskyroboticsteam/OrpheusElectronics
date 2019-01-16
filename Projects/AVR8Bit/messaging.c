#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "can.h"
#include "motor.h"
#include "encoder.h"
#include "adc.h"
#include "usart.h"
#include "messaging.h"

/*Handle a recieved CAN message*/
void handle_CAN_message(struct CAN_msg *m){
	uint8_t sender = (m->id & 0x3E0) >> 5;
	uint16_t param1, param2;
	param1 = (m->data[1] << 8) | m->data[2];
	param2 = (m->data[3] << 8) | m->data[4];
	switch(m->data[0]){
		case 0x00: //Set Mode
			if(m->data[1]){
				set_motor_mode(get_motor_mode() & ~MOTOR_MODE_PID);
			} else {
				set_motor_mode(get_motor_mode() | MOTOR_MODE_PID);
			}
			break;
		case 0x02: //Set PWM/Direction
			if(!(get_motor_mode() & MOTOR_MODE_PID)){
				int16_t mp = ((unsigned)m->data[1]) * 4;
				if(m->data[2]){
					mp =- mp;
				}
				set_motor_power(mp);
			}
			break;
		case 0x04: //Set angle
			param1 = m->data[1] | m->data[2]<<8;
			param2 = m->data[3] | m->data[4]<<8;
			set_target_position(param1);
			set_target_velocity(param2);
			break;
		case 0x06: //Index
			index_motor();
			break;
		case 0x08: //Reset
			break;
		case 0x0A: //Set P
			set_Kp(m->data[1] | m->data[2]<<8, m->data[3] | m->data[4]<<8);
			break;
		case 0x0C: //Set I
			set_Ki(m->data[1] | m->data[2]<<8, m->data[3] | m->data[4]<<8);
			break;
		case 0x0E: //Set D
			set_Kd(m->data[1] | m->data[2]<<8, m->data[3] | m->data[4]<<8);
			break;
		case 0x10: //Model request
			send_model_number(sender);
			break;
		case 0xFF: /*error*/
			tprintf("Error %d\n", m->data[1]);
			break;
	}
}

/*Sends a CAN message to the specified target
  Parameters:
  uint8_t target: the target address
  uint8_t length: the length of the data to send (0 - 8 bytes)
  void *buffer: the data to send
  uint8_t priority: true to send a high priority message
*/
int send_CAN_message(uint8_t target, uint8_t length, void *buffer, uint8_t priority){
	struct CAN_msg m;
	uint8_t my_adr = 0x10 | get_dip_switch();
	m.id = ((!priority)<<10) | (my_adr & 0x1F)<<5 | (target & 0x1F);
	m.flags = 0;
	m.length = length;
	memcpy(m.data, buffer, length);
	return CAN_send_msg(&m);
}

/*Sends the model number of the board over CAN to the specified target.
  Parameters:
  uint8_t target: the address of the target node
*/
void send_model_number(uint8_t target){
	uint16_t req = (0x12<<8) | (MODEL_NUMBER & 0xFF);
	send_CAN_message(target, 2, &req, 0);
}

/*Sends an 8 bit int over CAN to the specified target
  Parameters:
  uint8_t target: the address of the target node
  uint8_t pn: the packet ID
  uint8_t b: the 8 bit int to send
  uint8_t priority: the priority of the message. True for high priority
*/
void send_int8_packet(uint8_t target, uint8_t pn, uint8_t b, uint8_t priority){
	uint16_t req = (pn << 8) | b;
	send_CAN_message(target, 2, &req, priority); 
}

/*Sends an 16 bit int over CAN to the specified target
  Parameters:
  uint8_t target: the address of the target node
  uint8_t pn: the packet ID
  uint8_t b: the 16 bit int to send
  uint8_t priority: the priority of the message. True for high priority
*/
void send_int16_packet(uint8_t target, uint8_t pn, uint16_t n, uint8_t priority){
	uint32_t req = (pn << 12) | (n << 8);
	send_CAN_message(target, 3, &req, priority);
} 

/*Sends an 32 bit int over CAN to the specified target
  Parameters:
  uint8_t target: the address of the target node
  uint8_t pn: the packet ID
  uint8_t b: the 32 bit int to send
  uint8_t priority: the priority of the message. True for high priority
*/
void send_int32_packet(uint8_t target, uint8_t pn, uint32_t n, uint8_t priority){
	uint8_t buf[4];
	buf[0] = pn;
	buf[1] = (n & 0xFF000000) >> 24;
	buf[2] = (n & 0x00FF0000) >> 16;
	buf[3] = (n & 0x0000FF00) >> 8;
	buf[4] = (n & 0x000000FF);
	send_CAN_message(target, 5, buf, priority);
}

/*Send an error packet with the specified code over the CAN bus to to the BBB*/
void send_CAN_error(uint8_t error, uint8_t param){
	send_int16_packet(BEAGLEBONE_ADDRESS, 0xFF, error << 8 | param, 1);
}

/*Sends the encoder count over the CAN bus to the BBB*/
void send_encoder_count(){
	uint32_t count = get_encoder_ticks();
	if(count < 65535){
		send_int16_packet(BEAGLEBONE_ADDRESS, 0x14, count & 0xFFFF, 0);
	} else {
		send_int32_packet(BEAGLEBONE_ADDRESS, 0x14, count, 0);
	}
}

/*Sends the voltage and current over the CAN bus to the BBB*/
void send_telemetry(){
	uint16_t voltage = get_voltage();
	uint16_t current = get_motor_current();
	send_int32_packet(BEAGLEBONE_ADDRESS, 0x18, ((uint32_t)voltage << 16) | current, 0);
}