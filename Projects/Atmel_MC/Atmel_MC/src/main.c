/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include <top.h>

pwmData myPWMData;
encoderData myEncoderData;
canData myCANData;
potData myPotData;

TCB canTCB, emergencyStopTCB, encoderTCB, limit_switchTCB, motorTCB;
TCB *head, *tail;
TCB *TCBArray[] = {&canTCB, &emergencyStopTCB, &encoderTCB, &limit_switchTCB, &, NULL}

int main (void)
{
	system_init();
	/* Insert application code here, after the board has been initialized. */
	initialize();
	while(1) 
	{
		scheduler();
	}
	
}
// https://www.digikey.com/eewiki/display/microcontroller/CAN+Example+-+ATmega32M1+-+
// https://github.com/arduino/ArduinoModule-CMSIS-Atmel/blob/master/CMSIS-Atmel/CMSIS/Device/ATMEL/samc21/include/samc21g17a.h



void initialize(void) {
	
	// Initialize structs
	myPWMData.pwmVal[0] = 0;
	myPWMData.pwmVal[1] = 0;
	myPWMData.pwmVal[2] = 0;

	myEncoderData.encoderRaw[0] = 0;
	myEncoderData.encoderRaw[1] = 0;
	myEncoderData.encoderRaw[2] = 0;
	
	// myCANData; // tbd
	
	// myPotData; // tbd
	
	// Initialize TCB's
	canTCB.task = comms;
	canTCB.dataPtr = &myCANData;
	
	emergencyStopTCB.task = emergencyStop;
	
	encoderTCB.task = readEncoders;
	encoderTCB.dataPtr = &myEncoderData;
	
	limit_switchTCB.task = limit_switch;
	
	motorTCB.task = motorPID;
	motorTCB.dataPtr = &myPWMData;
	
}