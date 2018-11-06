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
#define PWM_PERIOD = 1000;
uint8 limit_1_pressed = 0;
uint8 limit_2_pressed = 0;
uint8 emergency = 0;

CY_ISR(Pin_Limit_1_Handler){// void Pin_SW_Handler(void)
    set_PWM(0);
    limit_1_pressed = 1;
    Pin_Limit_1_ClearInterrupt();
}
/*
CY_ISR(Pin_Limit_2_Handler){// void Pin_SW_Handler(void)
    set_PWM(0);
    limit_2_pressed = 1;
    Pin_Limit_2_ClearInterrupt();
}
*/
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   // initialize();
    isr_Limit_1_StartEx(Pin_Limit_1_Handler);
  //  isr_Limit_2_StartEx(Pin_Limit_2_Handler);
    PWM_Motor_Start();
    int i = 0;
    int up = 1;
    
    for(;;)
    {
        if(!emergency) {
        Pin_debug_Write(limit_1_pressed);
        check_Pin();
        set_PWM(i);
        CyDelay(100);
        if(up){
            i += 10;
        } else {
            i -= 10;   
        }
        if(i > 1000) {
            up = 0;   
        } else if (i < -1000) {
            up = 1;
        }
        // inturupts limit switch, stops motor
        // intrupts second priority to read CAN
        // sets PWM
        // hardware encoder counter
        // read pot info
        // Sends to BB info over CAN
        // if no CAN data after ~100ms stop motors
        }
    }
}

void check_Pin(void) {
    if(Pin_Limit_1_Read() == 1) {
        limit_1_pressed = 0;
    }
   /* if(Pin_Limit_2_Read() == 1) {
        limit_2_pressed = 0;   
    }*/
}

void emergency_halt(void) {
    PWM_Motor_Stop();
    emergency = 1;
    // stops all motors;
    // waits for restart CAN signal.
}
/*
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
*/

    // takes between -1000 and 1000
void set_PWM(int compare) {
    if (compare < -1000 || compare > 1000) { return; }
    if (compare < 0 && limit_1_pressed == 0) {
        Pin_Direction_Write(0);
        PWM_Motor_WriteCompare(-compare);
    } else if (compare > 0 && limit_2_pressed == 0){
        Pin_Direction_Write(1);
        PWM_Motor_WriteCompare(compare);
    } else {
        PWM_Motor_WriteCompare(0);   
    }
}
/*
void set_Position(int encoder) {
    //sets motor to encoder position
}

void set_Speed(int current_spd, int speed) {
    // gathers current speed and modifies pwm to get desired speed
}
    */

/* [] END OF FILE */
