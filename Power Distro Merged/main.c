/*
 * CanFix.c
 *
 * Created: 23-Apr-19 14:18:09
 * Author : Akkshaj Singh (AJ)
 */ 

#include <avr/io.h>
#include "can.h"
#include <util/delay.h>

void I2CInit (){
	TWBR = 0x01; // Set bit rate to 100 kHz
	TWCR = (1<<TWEN);
	TWSR = 0x00;
	
}

void I2CWait () {
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

void initializePorts(){

	// To relay driver

	// 0xFF = output
	// 0x00 = input

	PORTC = 0b11111011;
	//DDC6 = 0x00;
	DDRC = 0b00000000;

	PORTF = 0b0000111;
	/*DDF5 = 0xFF;
	DDF6 = 0xFF;
	DDF7 = 0xFF;
*/
	// TWI SCL and SDA
	// D5 and D6 for CAN
	//	D5 = transmitter
	//	D6 = receiver

	PORTD = 0b11000010;
/*	DDD0 = 0x00;
	DDD1 = 0x00;
	DDD5 = 0xFF;
	DDD6 = 0x00;
*/
}

void soundBuzzer (uint8_t address) { // UNFINISHED
	I2CStart(address);
	I2CStop();
}

uint8_t readMsgChk(){
	struct CAN_msg msg;
	if(CAN_msg_available()){
		CAN_get_msg(&msg);
		
		if(msg.data[0] == 0x26){
			//msg from beagle bone for relay shutoff over I2C
		}
		
		if(msg.data[0] == 0x20){
			//battery voltage
			return msg.data[1];
		}
	}
	
	
	
}

void sendCurrent(uint8_t threeV, uint8_t FiveV, uint8_t TwFourV){
	struct CAN_msg current;
	
	current.id = 0x02;
	current.flags = 1;
	current.length = 3;
	current.data[0] = 0x24;
	current.data[1] = threeV;
	current.data[2] = FiveV;
	current.data[3] = TwFourV;
	
	CAN_send_msg(&current);
}

void sendVoltage(uint8_t threeV, uint8_t FiveV, uint8_t TwFourV){
	struct CAN_msg voltage;
	
	voltage.id = 0x02;
	voltage.flags = 1;
	voltage.length = 3;
	voltage.data[0] = 0x22;
	voltage.data[1] = threeV;
	voltage.data[2] = FiveV;
	voltage.data[3] = TwFourV;
	
	CAN_send_msg(&voltage);
}

void sendTest(){
	struct CAN_msg test;
	
	test.id = 1;
	test.flags = 0;
	test.length = 2;
	test.data[0] = 'h';
	test.data[1] = 'i';
	
	CAN_send_msg(&test);
	
}

int main(void)
{
	initializePorts();
	uint16_t canAdd = 0x04;
	CAN_set_RX_filter(canAdd,canAdd);
	
	init_CAN(CAN_125_BAUD, 5, 0);
	
    while (1) 
    {
// 		sendTest();
// 		_delay_ms(1000);
		
		uint8_t batVoltage = readMsgChk();
		
		uint8_t readerAddress = 0x4E; //1001110
		
		I2CStart(readerAddress); // address of slave device
		
		I2CWrite(0x02); // Bus Voltage register
		uint8_t voltage = I2CRead(); // I HAVE TO FIX THIS.
		//printf("Voltage :"+ voltage);

		if(batVoltage > 24 || batVoltage < 16){
			soundBuzzer(0x07);
		}
		
		I2CStop();
		
		
		
		I2CStart(readerAddress);
		I2CWrite(0x04); // Current register
		uint8_t current = I2CRead();
		//printf("Current :"+ current);
		I2CStop();
		
		I2CStart(readerAddress);
		I2CWrite(0x03); // Power register
		uint8_t power = I2CRead();
		//printf("Power :"+ power);
		I2CStop();		sendCurrent(current, current, current);		sendVoltage(voltage, voltage, voltage);
    }
}

