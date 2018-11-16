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
//uint8 limit_1_pressed = 0;
//uint8 limit_2_pressed = 0;
uint8 emergency = 0;

CY_ISR(Pin_Limit_1_Handler){// void Pin_SW_Handler(void)
    set_PWM(0);
  //  limit_1_pressed = 1;
    Pin_Limit_1_ClearInterrupt();
}

CY_ISR(Pin_Limit_2_Handler){// void Pin_SW_Handler(void)
    set_PWM(0);
  //  limit_2_pressed = 1;
    Pin_Limit_2_ClearInterrupt();
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();
    isr_Limit_1_StartEx(Pin_Limit_1_Handler);
    isr_Limit_2_StartEx(Pin_Limit_2_Handler);
    int i = 0;
    int up = 1;
    
    for(;;)
    {
        if(!emergency) {
        Pin_count_10_Write((Status_Reg_Switches_Read() & 0b10) >> 0b1);
        Pin_count_20_Write(Status_Reg_Switches_Read() & 0b01);
        //Pin_debug_Write(QuadDec_GetCounter() % 2);
        //Pin_count_10_Write(QuadDec_GetCounter() % 4);
        //Pin_count_neg_10_Write(QuadDec_GetCounter() % 3);
        //Pin_count_neg_20_Write(QuadDec_GetCounter() %2);
        /*if(QuadDec_GetCounter() < 0) {
            Pin_count_20_Write(1);
        } else {
            Pin_count_20_Write(0);
        }*/
       // check_Pin();
        set_PWM(i); 
        CyDelay(100);
        if(up){
            i += 100;
        } else {
            i -= 100;   
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
/*
void check_Pin(void) {
    if(Status_Reg_Switches_ReadMask() & 0b01) {
        limit_1_pressed = 0;
    }
    if(Status_Reg_Switches_ReadMask() & 0b10) {
        limit_2_pressed = 0;   
    }
}
*/
void emergency_halt(void) {
    PWM_Motor_Stop();
    emergency = 1;
    // stops all motors;
    // waits for restart CAN signal.
}

void initialize(void) {
    QuadDec_Start();
    PWM_Motor_Start();
}
/*
void CAN_Read(int *read) {
    // writes to the read array the data that was sent
}

void CAN_Send(int count, int8 switch1, int8 switch2 ) {
    // sends enconder count and switch state through can
}

uint32 pot_Read(void) {
    // returns a position of the pot
}
 
*/
    // takes between -1000 and 1000
void set_PWM(int compare) {
    if (compare < -1000 || compare > 1000) { return; }
    if (compare < 0 && !(Status_Reg_Switches_Read() & 0b01)) {
        Pin_Direction_Write(0);
        PWM_Motor_WriteCompare(-compare);
    } else if (compare > 0 && !(Status_Reg_Switches_Read() & 0b10)){
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
