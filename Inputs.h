/* 
 * File:   Inputs.h
 * Author: User
 *
 * Created on October 27, 2018, 11:34 AM
 */

#ifndef INPUTS_H
#define	INPUTS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* INPUTS_H */

struct readingInfo(){
    double voltage;
    double current;   
}

double readVoltage(){

 /*
     Extract voltage reading. If 
     voltage reading is below the 23V threshold, sound a buzzer 
     Function has to be called every 1000 ms 	
	If(Voltage < 23 V){
		soundBuzzer();
		
	}else{
		?.
	
	}
   
    if(Voltage > safe Amount){
      killPower();
  }
  
  
 */
 }

double sendVoltage(int voltage){
    readVoltage();
    // send voltage info to BBB  
}

  double readCurrent(){
/*
    Accepts information from battery management
		
	If(current < ?){
		SoundBuzzer();
	}else{
		?.
	}
	Sends current info to BBB;
	}
	
} */
  }
  
  double sendCurrent(int current){
      readCurrent()
      // send current info to BBB
  }
  
  double readPower(){
      
      // receive battery VIN
  }
  
  