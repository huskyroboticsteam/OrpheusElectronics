#include "conf.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "can.h"

volatile uint8_t msgs_av; //Number of messages unclaimed messages

ISR(CANIT_vect){
	//uint8_t canpage, mob;
	if((CANHPMOB & 0xF0) != 0xF0){ //Message received?
		/*canpage = CANPAGE;
		CANPAGE = CANHPMOB & 0xF0;
		mob = CANHPMOB >> 4; //get highest priority MOb
		*/
		msgs_av++; //Increase count of messages
	} else {
		CANGIT |= 0; //Error interrupt - Handle these?
	}
}

/*Enables the CAN controller
Parameters:
uint32_t rate: the baud rate selection
uin8_t txmobs: how many MOBs to dedicate to transmission
*/
void init_CAN(uint32_t rate, uint8_t txmobs, uint8_t mode){
	CANGCON |= (1<<SWRES);
	CANBT1 = (rate & 0xFF0000) >> 16;
	CANBT2 = (rate & 0x00FF00) >> 8;
	CANBT3 = (rate & 0x0000FF);
	CANGIE = (1 << ENERR) | (1 <<ENERG) | (1 << ENRX); //Enable CAN RX interrupts
	CANTCON = 255; //Set the can timer to run at 1/2048th of F_CPU
	uint8_t i;
	/*Initialize non-tx MOBs to receive*/
	for(i = txmobs;i < 15;i++){
		select_mob(i);
		CANSTMOB &= 0;
		CANCDMOB = (1 << CONMOB1);
	}
	msgs_av = 0;
	if(mode & CAN_LISTEN){
		CANGCON |= (1<<CAN_LISTEN);
	}
	CANGCON = (1 << ENASTB); //Enable the CAN controller
}

/*Selects the MOB to operate on*/
void select_mob(uint8_t mob){
	CANPAGE = ((mob & 0x0F) << 4);
}

void disable_mob_interrupt(uint8_t mob){
	if(mob < 8){
		CANIE2 &= ~(1 << mob);
	} else {
		CANIE1 &= ~(1 << (mob - 8));
	}
}

void enable_mob_interrupt(uint8_t mob){
	if(mob < 8){
		CANIE2 |= (1 << mob);
	} else {
		CANIE1 |= (1 << (mob - 8));
	}
}


/*Returns the number of CAN messages waiting*/
uint8_t CAN_msg_available(){
	return msgs_av;
}

/*Copies a message received on the CAN bus to buf*/
uint8_t CAN_get_msg(struct CAN_msg *buf){
	uint8_t i, mob;
	if(!CAN_msg_available()) return;
	for(i = 0;i < 15;i++){
		select_mob(i);
		if(CANSTMOB & (1<<RXOK)){
			CANSTMOB &= 0;
			break;
		}
	}
	if(i == 15) return 0;
	mob = i;
	buf->length = CANCDMOB & 0x0F;
	buf->id = (CANIDT2 >> 5) | ((uint16_t)CANIDT1 << 3);
	if(CANIDT4 & (1<<RTRTAG)){
		buf->flags |= CAN_RTR;
	} else {
		buf->flags &= CAN_RTR;
	}
	for(i = 0;i < buf->length;i++){
		buf->data[i] = CANMSG;
	}
	cli();
	msgs_av--;
	sei();
	enable_mob_interrupt(mob);
	CANCDMOB = (1<<CONMOB1); //Re-enable recieve
	return 1;
}

int8_t find_free_mob(){
	uint8_t i;
	for(i = 0;i < 15;i++){
		select_mob(i);
		if(!(CANCDMOB & ((1 << CONMOB1) | (1 << CONMOB0)))){
			return i;
		}
	}
	return -1;
}

/*Send a message over the can bus*/
uint8_t CAN_send_msg(struct CAN_msg *buf){
	int8_t mob = find_free_mob();
	uint8_t i;
	if(mob == -1){
		return 0;
	}
	select_mob(mob);
	CANSTMOB &= 0;
	CANCDMOB = buf->length & 0x0F;
	for(i = 0;i < buf->length;i++){
		CANMSG = buf->data[i];
	}
	CANIDT3 = (buf->flags & CAN_RTR)? (1<<RTRTAG): 0;
	CANIDT2 = ((buf->id & 3) << 5);
	CANIDT1 = ((buf->id & 0x7F8) >> 3);
	CANCDMOB |= (1<<CONMOB0);
	return 1;
}
