/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "cyapicallbacks.h"

int gear_ratio;
int CAN_TIMEOUT;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();

    for(;;)
    {
        // inturupts limit switch, stops motor
        // intrupts second priority to read CAN
        // sets PWM
        // hardware encoder counter
        // read pot info
        // Sends to BB info over CAN
        // if no CAN data after ~100ms stop motors
    }
}
void emergency_Stop(void) {
    // stops all motors;
    // waits for restart CAN signal.
}

void initialize(void) {
    // initialize all blocks
}

void CAN_Read(int *read) {
    // writes to the read array the data that was sent
}

void CAN_Send(int count, int8 switch1, int8 switch2 ) {
    // sends enconder count and switch state through can
}

uint32 pot_Read(void) {
    // returns a position of the pot
}

int8 switch_State(int num) {
    //returns the state of switch "num" as an int
}

int8 encoder_Read(void) {
    // returns the amount of counts it turned   
}

void set_PWM(int pow) {
    // takes the pow between a positive and negitive number
    // and outputs pwm
}

void set_Position(int encoder) {
    //sets motor to encoder position
}

void set_Speed(int current_spd, int speed) {
    // gathers current speed and modifies pwm to get desired speed
}
    

/* [] END OF FILE */
