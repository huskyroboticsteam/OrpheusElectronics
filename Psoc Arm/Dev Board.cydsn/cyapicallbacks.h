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
#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H

#include "project.h"
    

    
//void check_Pin(void);
void initialize_can_addr(void);
void set_CAN_ID(uint32 priority);
void CAN_Send_Encoder(void);
void CAN_Send_Telemetry(void);
void CAN_Send_Model(void);
void initialize(void);
int encoder(void);
void emergency_Stop(void);
void initialize(void);
void CAN_Read(int *read);
void CAN_Send(int Mailbox, uint8 type, uint8 b1, uint8 b2, uint8 b3, uint8 b4);
uint32 pot_Read(void);
void set_PWM(int period);
int degrees_to_tick();
int position_PID();
void set_Position(int encoder);
void set_Speed(int current_spd, int speed);


    /*Define your macro callbacks here */
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
