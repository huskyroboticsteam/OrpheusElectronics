#include <avr/io.h>
#include "can.h"
#include "motor.h"
#include "messaging.h"

void handle_CAN_message(struct CAN_msg *m){
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
			break;
		case 0x06: //Set velocity
			break;
		case 0x08: //Reset
			break;
		case 0x0A: //Set P
			break;
		case 0x0C: //Set I
			break;
		case 0x0E: //Set D
			break;
		case 0x10: //Model request
			break;
	}
}