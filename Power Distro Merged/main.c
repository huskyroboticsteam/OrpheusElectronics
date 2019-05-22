/*
 * PowerDistroTWIUpdated.c
 *
 * Created: 18-May-19 16:38:43
 * Author : Akkshaj Singh (AJ)
 */ 

//TODO add INA226 calib/setup & reading - https://github.com/jarzebski/Arduino-INA226/blob/master/INA226.cpp for sample
//I2C Library - https://github.com/g4lvanix/I2C-master-lib
//TODO port initialization (confirm with hardware)

#include <avr/io.h>
#include <util/delay.h>

#include "can.h"
#include "i2c_master.h"

void initializePorts(){
	
	//PC0,PC1,PC2 - converter inhibit pins
	PORTC = 0b00000000;
	DDRC =  0b11100000;
	
	//add for other ports
	
}

//checks for an incoming can msg
//if battery voltage msg from battery board, return.
uint8_t readMsgChk(){
	struct CAN_msg msg;
	if(CAN_msg_available()){
		CAN_get_msg(&msg);
		
		if(msg.data[0] == 0x20){
			//battery voltage
			return msg.data[1];
		}
	}
	
	return 0;
}

//sends a test CAN msg 
//for debugging only
void sendTest(){
	struct CAN_msg test;
	
	test.id = 1;
	test.flags = 0;
	test.length = 2;
	test.data[0] = 'h';
	test.data[1] = 'i';
	
	CAN_send_msg(&test);
	
}

void sendCurrent(uint8_t voltage){
	struct CAN_msg current;
	
	current.id = 0x02;
	current.flags = 1;
	current.length = 3;
	current.data[0] = 0x24;
	current.data[1] = voltage;
	
	CAN_send_msg(&current);
}

void sendVoltage(uint8_t current){
	struct CAN_msg voltage;
	
	voltage.id = 0x02;
	voltage.flags = 1;
	voltage.length = 3;
	voltage.data[0] = 0x22;
	voltage.data[1] = current;
	
	CAN_send_msg(&voltage);
}

//handle calibration & setup of INA 226 over I2C
void ina_setup(){
	i2c_init();
	i2c_start(0x40);
	
}

uint8_t ina_readV(){
	
}

uint8_t ina_readA(){
	
}

uint8_t ina_radP(){
	
}



int main(void)
{
    initializePorts();
	
    uint16_t canAdd = 0x04;
    CAN_set_RX_filter(canAdd,canAdd);
	init_CAN(CAN_125_BAUD, 5, 0);
	
	ina_setup();
	
    while (1) 
    {

		
    }
}

