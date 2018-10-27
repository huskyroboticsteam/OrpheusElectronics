#include <avr/io.h>
#include <avr/interrupt.h>
#include "encoder.h"

volatile uint32_t encoder_ticks;

/*Returns the total number of encoder ticks since the last reset*/
uint32_t get_encoder_ticks(){
	return encoder_ticks;
}

/*Initalizes the encoder with A on PE6 and B on PE7*/
void init_encoder(){
	EICRB &= 0x0F; //Disable pin change interrupts
	DDRE &= 0x3F; //Set PE6, PE7 as inputs
	PORTE |= 0xC0; //Enable pullups on PE6, PE7
	encoder_ticks = 0; //Reset count
	EICRB |= 0x50; //Enable pin change interrupt on PE6, PE7
}

/*Resets the encoder count*/
void reset_encoder(){
	EICRB &= 0x0F; //Disable pin change interrupts
	encoder_ticks = 0; //Reset count
	EICRB |= 0x50; //Enable pin change interrupt on PE6, PE7
}

ISR(INT6_vect){ //PE6, A
	uint8_t state = PINE;
	if(state & (1<<PE6)){ //A rising
		if(state & (1<<PE7)){ //B high
			encoder_ticks++;
		} else { //B low
			encoder_ticks--;
		}
	} else { //A falling
		if(state & (1<<PE7)){ //B high
			encoder_ticks--;
		} else { //B low
			encoder_ticks++;
		}
	}
}

ISR(INT7_vect){ //PE7, B
	uint8_t state = PINE;
	if(state & (1<<PE7)){ //B rising
		if(state & (1<<PE6)){ //A high
			encoder_ticks--;
		} else { //A low
			encoder_ticks++;
		}
	} else { //B falling
		if(state & (1<<PE6)){ //A high
			encoder_ticks++;
		} else { //A low
			encoder_ticks--;
		}
	}
}