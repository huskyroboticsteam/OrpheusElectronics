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
#include <project.h>
#include "cyapicallbacks.h"
#include <stdio.h>

int gear_ratio;
int CAN_TIMEOUT;
int pwm_compare;
int i = 0;
int lastp = 0;
int kp,ki,kd;
#define TX_DATA_SIZE           (25u)
#define PWM_PERIOD = 1000;
char8 txData[TX_DATA_SIZE];
//uint8 limit_1_pressed = 0;
//uint8 limit_2_pressed = 0;
uint8 emergency = 0;

CY_ISR(Pin_Limit_1_Handler){// void Pin_SW_Handler(void)
    set_PWM(pwm_compare);
    Pin_Limit_1_ClearInterrupt();
}
int main(void)
{
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();
    isr_Limit_1_StartEx(Pin_Limit_1_Handler);
    int up = 1;
    int16 adc ;
    for(;;)
    {
        if(!emergency) {
            if(Status_Reg_Manual_Read()) {
                adc = ADC_SAR_Seq_1_GetResult16(0);
                if(Status_Reg_Manual_Read() & 0b10) {
                      
                } else if(Status_Reg_Manual_Read() & 0b01) {
                    
                }
            }
            Pin_count_10_Write((Status_Reg_Switches_Read() & 0b10) >> 0b1);
            Pin_count_20_Write(Status_Reg_Switches_Read() & 0b01);
            CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_Test, 1u);
            CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_Test, 2u);
            CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_Test, 3u); 
            CAN_TX_DATA_BYTE4(CAN_TX_MAILBOX_Test, 4u);
            CAN_TX_DATA_BYTE5(CAN_TX_MAILBOX_Test, 5u);
            CAN_TX_DATA_BYTE6(CAN_TX_MAILBOX_Test, 6u);
            CAN_TX_DATA_BYTE7(CAN_TX_MAILBOX_Test, 7u);
            CAN_TX_DATA_BYTE8(CAN_TX_MAILBOX_Test, 8u);
            CAN_SendMsgTest();
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
            set_PWM(pwm_compare); 
            CyDelay(100);
            if(up){
                pwm_compare += 100;
            } else {
                pwm_compare -= 100;   
            }
            if(pwm_compare > 1000) {
                up = 0;   
            } else if (pwm_compare < -1000) {
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
    UART_Start();
    UART_UartPutString(txData);
    sprintf(txData, "Can Start:  %u\r\n",CAN_Start());
    CAN_GlobalIntEnable();
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
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


void set_Position(int degrees) {
    int PWM = position_PID(degrees_to_tick(degrees));
    if(PWM > 1000){
        set_PWM(1000);   
    } else if(PWM < -1000) {
        set_PWM(-1000);
    } else {
        set_PWM(PWM);   
    }
}

int degrees_to_tick(int degrees){
    int ratio = 1;
    return(degrees * ratio);
}

int position_PID(int target){
    int current =  QuadDec_GetCounter();
    int p = target - current;
    i = i + p;
    int d = p - lastp;
    lastp = current;
    return (p*10 + i*10 + d*10);
}

/*
void set_Speed(int current_spd, int speed) {
    // gathers current speed and modifies pwm to get desired speed
}
    */

/* [] END OF FILE */
