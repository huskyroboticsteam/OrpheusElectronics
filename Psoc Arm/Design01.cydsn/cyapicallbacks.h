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
    
void initialize(void);
int encoder(void);
void emergency_Stop(void);
void initialize(void);
void CAN_Read(int *read);
void CAN_Send(int count, int8 switch1, int8 switch2 );
uint32 pot_Read(void);
void set_PWM(int pow);
void set_Position(int encoder);
void set_Speed(int current_spd, int speed);


    /*Define your macro callbacks here */
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
