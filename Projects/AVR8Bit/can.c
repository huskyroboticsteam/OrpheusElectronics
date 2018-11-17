#include "conf.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <usart.h>
#include "can.h"

volatile uint8_t msgs_av; //Number of messages unclaimed messages

uint16_t RX_mask, RX_tag;

volatile uint8_t rxed_mobs[2];

ISR(CANIT_vect){
	uint8_t canpage = CANPAGE;
	//PORTE ^= (1<<PE4);
	if((CANHPMOB & 0xF0) != 0xF0){ //Message io?
		int mob = (CANHPMOB >> 4);
		select_mob(mob);
	    if(CANSTMOB & (1 << TXOK)){ //TX
			/*Reset the MOb*/
			CANSTMOB &= 0;
			CANCDMOB = 0;
			enable_mob_interrupt(mob);
		} else { //RX
			msgs_av++; //Increase count of messages
			rxed_mobs[!!(mob & 8)] |= (1 << (mob & 7));
			CANSTMOB &= 0;
			disable_mob_interrupt(mob);
		}
	} else {
		CANGIT |= 0; //Error interrupt - Handle these?
	}
	CANPAGE = canpage;
}

/*Enables the CAN controller
Parameters:
uint32_t rate: the baud rate selection
uin8_t txmobs: how many MOBs to dedicate to transmission
*/
void init_CAN(uint32_t rate, uint8_t txmobs, uint8_t mode){
	CANGCON |= (1<<SWRES);
	CANBT1 = 0x26;//(rate & 0xFF0000) >> 16;
	CANBT2 = 0x04;//(rate & 0x00FF00) >> 8;
	CANBT3 = 0x13;//(rate & 0x0000FF);
	CANGIE = (1 << CANIT) | /*(1 << ENERR) | (1 <<ENERG) |*/ (1 << ENRX) | (1 << ENTX); //Enable CAN interrupts
	CANTCON = 255; //Set the can timer to run at 1/2048th of F_CPU
	rxed_mobs[0] = rxed_mobs[1] = 0;
	uint8_t i;
	/*Initialize MOBs*/
	for(i = 0;i < 15;i++){
		select_mob(i);
		CANSTMOB &= 0;
		CANIDM4 = 0;
		CANIDM3 = 0;
		CANIDM2 = 0;
		CANIDM1 = 0;
		CANIDT4 = 0;
		CANIDT3 = 0;
		CANIDT2 = 0;
		CANIDT1 = 0;
		if(i > txmobs){
			CANCDMOB = (1 << CONMOB1); //Mark RX mobs
			enable_mob_interrupt(i);
		} else {
			CANCDMOB = 0;
		}
	}
	msgs_av = 0;
	//Enable the CAN controller
	CANGCON = (1 << ENASTB);
	if(mode & CAN_LISTEN){
		CANGCON |= (1<<LISTEN);
	}
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
int mob_interrupt_enabled(uint8_t mob){
	if(mob < 8){
		return !!(CANIE2 & (1 << mob));
	} else {
		return !!(CANIE1 & (1 << (mob - 8)));
	}
}
uint8_t mob_enabled(uint8_t mob){
	if(mob < 8){
		return !!(CANEN2 & (1 << mob));
	} else {
		return !!(CANEN1 & (1 << (mob - 8)));
	}
}

/*Returns the number of CAN messages waiting*/
uint8_t CAN_msg_available(){
	return msgs_av;
}

/*Copies a message received on the CAN bus to buf*/
uint8_t CAN_get_msg(struct CAN_msg *buf){
	uint8_t i, mob;
	if(!CAN_msg_available()) return 0;
	for(i = 0;i < 16;i++){
		if(i == 15) return 0;
		select_mob(i);
		if(rxed_mobs[!!(i & 8)] & (1 << (i & 7))){
			break;
		}
	}
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
	CANIDT4 = 0;
	CANIDT3 = 0;
	CANIDT2 = (RX_mask & 0x03) << 5;
	CANIDT1 = (RX_mask & 0x7F8) >> 3;
	enable_mob_interrupt(mob);
	rxed_mobs[!!(mob & 8)] &= ~(1 << (mob & 7));
	CANCDMOB = (1<<CONMOB1); //Re-enable recieve
	return 1;
}

int8_t find_free_mob(){
	uint8_t i;
	uint8_t status;
	for(i = 0;i < 15;i++){
		select_mob(i);
		status = CANCDMOB;
		//tprintf("mob %d: CONMOB1:%d, CONMOB0:%d\n", i, !!(status & (1 << CONMOB1)), !!(status & (1 << CONMOB0)));
		if(!(status & ((1 << CONMOB1) | (1 << CONMOB0)))){
			return i;
		}
		//if(status & (1 << CONMOB0) && !mob_enabled(i)){
		//}
	}
	return -1;
}

/*Send a message over the can bus*/
uint8_t CAN_send_msg(struct CAN_msg *buf){
	uint8_t i;
	int8_t mob = find_free_mob();
	//tprintf("free mob=%d\n", mob);
	if(mob == -1){
		return 0;
	}
	select_mob(mob);
	CANSTMOB &= 0;
	CANCDMOB = buf->length & 0x0F;
	for(i = 0;i < buf->length;i++){
		CANMSG = buf->data[i];
	}
	CANIDT4 = 0;
	CANIDT3 = (buf->flags & CAN_RTR)? (1<<RTRTAG): 0;
	CANIDT2 = ((buf->id & 3) << 5);
	CANIDT1 = ((buf->id & 0x7F8) >> 3);
	CANCDMOB |= (1<<CONMOB0);
	enable_mob_interrupt(mob);
	return 1;
}

void CAN_set_RX_filter(uint16_t mask, uint16_t tag){
	RX_mask = mask;
	RX_tag = tag;
	int i;
	for(i = 0;i < 15;i++){
		/*Only modify receive mobs which are enabled and not occupied*/
		if(mob_enabled(i)){
			select_mob(i);
			if(CANCDMOB & (1<<CONMOB1)){
				CANIDT2 = ((tag & 3) << 5);
				CANIDT1 = ((tag & 0x7F8) >> 3);
				CANIDM2 = ((mask & 3) << 5);
				CANIDM1 = ((mask & 0x7F8) >> 3);
			}
		}
	}
}
const char *canstmob_names[] = {"ACK ERR", "FORM ERR", "CRC ERR", "STF ERR", "BIT ERR", "RXOK", "TXOK", "DLCW"}; 
void CAN_dump_state(){
	int i,j;
	for(i = 0;i < 15;i++){
		select_mob(i);
		uint32_t canstmob = CANSTMOB;
		uint32_t cancdmob = CANCDMOB; 
		tprintf("mob %d: (%c), I=%c, IDT=%d, DLC=%d, CANST=0x%X", i, mob_enabled(i)? 'E': 'D', mob_interrupt_enabled(i)? 'E': 'D', (uint16_t)((CANIDT2 >> 5) | ((uint16_t)CANIDT1 << 3)), (int)(cancdmob & 15), canstmob);
		if(canstmob != 0){
			tprintf("{");
			for(j = 0;j < 8;j++){
				if(canstmob & (1<<j)){
					tprintf("%s ", canstmob_names[j]);
				}
			}
			tprintf("}");
		}
		tprintf(", CANCD=0x%X {", (long)cancdmob);
		if(cancdmob & (1<<5)){
			tprintf("RPLV ");
		}
		if(cancdmob & (1<<4)){
			tprintf("2.0B ");
		}
		switch((cancdmob & 0xC0)>>6){
			case 0:
				tprintf("DIS");
				break;
			case 1:
				tprintf("ENTX");
				break;
			case 2:
				tprintf("ENRX");
				break;
			case 3:
				tprintf("FBRX");
				break;
		}
		tprintf("}\n");
	}
}