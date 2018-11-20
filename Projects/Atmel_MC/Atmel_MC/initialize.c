

void initialize(void) {
	
	// Initialize structs
	myPWMData.pwmVal[0] = 0;
	myPWMData.pwmVal[1] = 0;
	myPWMData.pwmVal[2] = 0;

	myEncoderData.encoderRaw[0] = 0;
	myEncoderData.encoderRaw[1] = 0;
	myEncoderData.encoderRaw[2] = 0;
	
	myCANData; // tbd
	
	myPotData; // tbd
	
	// Initialize TCB's
	commsTCB.task = comms;
	commsTCB.dataPtr = &myCANData;
	
	emergencyStopTCB.task = emergencyStop; 
	
	encoderTCB.task = readEncoders;
	encoderTCB.dataPtr = &myEncoderData;
	
	limit_switchTCB.task = limit_switch;
	
	pwmControlTCB.task = pwmControl
	pwmControlTCB.dataPtr = &myPWMData;
	
}



