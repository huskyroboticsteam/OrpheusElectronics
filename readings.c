
#include <util/delay.h>
#include <util/twi.h>
#include <avr/include/stdio.h>
#include "Readings.h"

double moduleReadings () {
	I2CStart(1001110); // address of slave device
	
	I2CWrite(0x02h); // Bus Voltage register
	double voltage = (double) I2CRead(); // I HAVE TO FIX THIS.
	printf("Voltage :"+ voltage);
	if(voltage > 24 || voltage < 16){
		soundBuzzer(0x07h); 
	}
	I2CStop();
	
	I2CStart(1001110);
	
	I2CWrite(0x04h); // Current register
	double current = (double) I2CRead();
	printf("Current :"+ current);
	I2CStop();
	
	I2CStart(1001110);
	
	I2CWrite(0x03h); // Power register 
	double power = (double) I2CRead();
	printf("Power :"+ power);
	I2CStop();
}

void soundBuzzer (uint8_t address) { // UNFINISHED
	I2CStart(address);
	I2CStop();
}
