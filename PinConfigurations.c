

#define CAN_TRANSMITTER_PORT          DDD5
#define CAN_RECEIVER_PORT             DDD6
#define bitrate CAN_BPS_500K
 
#include <avr/io.h>
#include <CAN.h>

void initializePorts(){
	// To relay driver 
	// 0xFF = output
	// 0x00 = input
	PORTC = 0b11111011;
	DDC6 = 0x00;
	
	PORTF = 0b0000111;
	DDF5 = 0xFF;
	DDF6 = 0xFF;
	DDF7 = 0xFF;
	
	// I2C SCL and SDA
	// D5 and D6 for CAN
	//	D5 = transmitter
	//	D6 = receiver 
	PORTD = 0b00000010
	DDD0 = 0x00;
	DDD1 = 0x00;
	CAN_TRANSMITTER_PORT = 0xFF;
	CAN_RECEIVER_PORT = 0x00;		
}
