/* 
 * File:   Outputs.h
 * Author: User
 *
 * Created on October 27, 2018, 11:23 AM
 */

#ifndef OUTPUTS_H
#define	OUTPUTS_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* OUTPUTS_H */

void soundBuzzer(){
    // Sounds alert. Usually called if voltage falls below acceptable level
}

double powerHigh(){
    // If voltage levels are adequate, 
    // regulate 24V Out to arm and science
    // Prints voltage readout;
}

double powerMid(){
    // if voltage levels are adequate
    // regulate 5V Out
    // Prints voltage readout;
}

double powerLow(){
    // if voltage levels are adequate
    // regulate 3.3V Out
    // Prints voltage readout
}

void killPower(){
      // immediately shuts off power if high enough voltage surge occurs
 }

void lightLED(){
    statusLED();
    // Flashes LED. Usually to indicate something is wrong
}