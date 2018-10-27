#include "conf.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can.h"

volatile uint8_t msgs_av; //Number of messages unclaimed messages

ISR(CANIT_vect){}

/*Enables the CAN controller
Parameters:
uint32_t rate: the baud rate selection
uin8_t txmobs: how many MOBs to dedicate to transmission
*/
void init_CAN(uint32_t rate, uint8_t txmobs){
	CANBT1 = (rate & 0xFF0000) >> 16;
	CANBT2 = (rate & 0x00FF00) >> 8;
	CANBT3 = (rate & 0x0000FF);
	CANGIE = (1 << ENIT) | (1 << ENRX) | (1 << ENTX); //Enable CAN interrupts
	CANTCON = 255; //Set the can timer to run at 1/2048th of F_CPU
	uint8_t i;
	/*Initialize non-tx MOBs to receive*/
	for(i = txmobs;i < 15;i++){
		select_mob(i);
		CANSTMOB &= 0;
		CANCDMOB = (1 << CONMOB1);
	}
	msgs_av = 0;
	//CANGCON = (1 << ENASTB) //Enable the CAN controller
}

/*Selects the MOB to operate on*/
void select_mob(uint8_t mob){
	CANPAGE = (CANPAGE & 0x0F) | ((mob & 0x0F) << 4);
}

/*Returns the number of CAN messages waiting*/
uint8_t CAN_msg_available(){
	return msgs_av;
}

/*Copies a message received on the CAN bus to buf*/
void CAN_get_msg(struct CAN_msg *buf){
	uint8_t i;
	if(!CAN_msg_available) return;
	for(i = 0;i < 15;i++){
		select_mob(i);
		if(CANSTMOB & (1<<RXOK)){
			break;
		}
	}
	/*TODO: Copy MOB to buffer, reset MOB*/
}


/*Send a message over the can bus*/
uint8_t CAN_send_msg(struct CAN_msg *buf){}
