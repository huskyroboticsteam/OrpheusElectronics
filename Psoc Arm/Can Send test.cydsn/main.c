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
#include "CAN.h"
#include <stdio.h>

typedef struct _DATA_BYTES_MSG
{
uint8 byte[8];
} DATA_BYTES_MSG;


typedef struct _CANTXMsg
{
uint32 id;
uint8 rtr;
uint8 ide;
uint8 dlc;
uint8 irq;
DATA_BYTES_MSG *msg;
} CANTXMsg;


CANTXMsg Msg_Ptr; /* declare Msg_Ptr as structure variable of type CANTXMsg*/
DATA_BYTES_MSG Data; /*declare Data as structure variable of type DATA_BYTES_MSG*/
#define DATALENGTH 0x08 /* size of data to be transmitted */
int main()
{
    uint8 bIndex;
    uint8 MESSAGE[]={0x00,0x11,0x00,0x11,0x00,0x11,0x00,0x11};//define 8 bytes of data
    Msg_Ptr.id = 0x001; /*write the value of ID to the structure*/
    Msg_Ptr.rtr = 0; /*write the value of RTR to the structure*/
    Msg_Ptr.ide = 0; /*write the value of IDE to the structure*/
    Msg_Ptr.dlc = DATALENGTH; /*write the value of DLC to the structure*/
    Msg_Ptr.irq = 1; /*write the value of IRQ to the structure*/
    Msg_Ptr.msg = &Data; /* write address of structure that represents data*/
    CYGlobalIntEnable; /*enable global interrupts*/
    for(bIndex=0;bIndex<DATALENGTH;bIndex++)
    {
        Data.byte[iIndex] = MESSAGE[bIndex]; /* move data to the structure*/
    }
    CAN_Init(); /* initialize CAN node */
    CAN_Start(); /* start CAN node */
    while (1)
    {
        CAN_SendMsg(&Msg_Ptr); /* transmit the CAN message */
    }
}
