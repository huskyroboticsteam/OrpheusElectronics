#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <avr/include/stdio.h>
#include "I2C_MASTER.h"

void I2CInit (){
	TWBR = 0x01; // Set bit rate to 100 kHz
	TWCR = (1<<TWEN);
	TWSR = 0x00;
}

void I2CWait (){
	while(!(TWCR & (1<<TWINT)));
}

void I2CStart (uint8_t address){
	// Clear start flag
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	I2CWait();
	TWDR = address;
	TWCR = (1<<TWEN) | (1<<TWINT);
	I2CWait();
}

void I2CStop (){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2CWrite (unsigned char data){
	TWDR = data;
	TWCR = (1<<TWEN) | (1<<TWINT);
	I2CWait();
}

uint8_t I2CRead()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	I2CWait();
	return TWDR;
}

