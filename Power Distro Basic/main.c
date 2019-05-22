/*
 * PowerDistBasic.c
 *
 * Created: 21-May-19 18:18:55
 * Author : Akkshaj Singh (AJ)
 * Basic Power Distro Port Setup
 */ 

#include <avr/io.h>
#include "can.h"

void init(){
	
	PORTC = 0b00000000;
	DDRC = 0b00000111;
	
}

void bat_chk(){
	struct CAN_msg msg;
	if(CAN_msg_available()){
		CAN_get_msg(&msg);
		
		if(msg.data[0] == 0x20){
			if((float)msg.data[1] < 15){
				PORTC = 0b00000111;
			}
			else{
				PORTC = 0b00000000;
			}
		}
	}
}

int main(void)
{
    init();
	
	uint16_t canAdd = 0x04;
	CAN_set_RX_filter(canAdd,canAdd);
	init_CAN(CAN_125_BAUD, 5, 0);
	
    while (1) 
    {
		
    }
}

