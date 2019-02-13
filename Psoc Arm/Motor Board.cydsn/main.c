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

uint32 message_id = 0;
#define MESSAGE_IDE             (0u)    /* Standard message */
#define MESSAGE_IRQ             (0u)    /* No transmit IRQ */
#define MESSAGE_RTR             (0u)    /* No RTR */

uint16 CAN_RX_MAILBOX_1_SHIFT  = 0b1;
uint16 CAN_RX_MAILBOX_0_SHIFT  = 0b10000000;

uint16 CAN_RX_MAILBOX_1 = 7u;
uint16 CAN_RX_MAILBOX_0 = 0u;


#define TX_DATA_SIZE            (50u)
#define PWM_PERIOD = 1000;

CY_ISR_PROTO(ISR_CAN);
//global var
uint8 uart_debug = 1;
int GEAR_RATIO;
int CAN_TIMEOUT;
int pwm_compare;
int i = 0;
int lastp = 0;
int kp,ki,kd;
volatile uint8 isrFlag = 0u;

int mailbox = 0x000;
uint8 emergency = 0;
char8 txData[TX_DATA_SIZE];
/* Global variables used to store configuration and data for BASIC CAN mailbox */
CAN_DATA_BYTES_MSG data;
CAN_TX_MSG message;

volatile uint8 receiveMailboxNumber = 0xFFu;




CY_ISR(Pin_Limit_1_Handler){// void Pin_SW_Handler(void)
    set_PWM(pwm_compare);
    Pin_Limit_1_ClearInterrupt();
}

int main(void)
{

    initialize_can_addr();
        /* BASIC CAN mailbox configuration */
    message.dlc = CAN_TX_DLC_MAX_VALUE;
    set_CAN_ID(0b1);
    message.ide = MESSAGE_IDE;
    message.irq = MESSAGE_IRQ;
    message.msg = &data;
    message.rtr = MESSAGE_RTR;
    CyIntSetVector(CAN_ISR_NUMBER, ISR_CAN);
    CyGlobalIntEnable; /* Enable global interrupts. */
    initialize();
    int test = 0b1;
    for(;;)
    {
        if(!emergency) {
        //UART_UartPutString(txData); 
           //Spare1_Write((Status_Reg_Switches_Read() & 0b10) >> 0b1);
           //Spare2_Write(Status_Reg_Switches_Read() & 0b01);
            CAN_Send_Model();
            CyDelay(1000);
            /*CyDelay(1000);
            CAN_Send_Encoder();
            CyDelay(1000);
            CAN_Send_Telemetry();
            CyDelay(1000);
            */
           // set_PWM(500);
           //set_PWM(pwm_compare); 
           /* CyDelay(100);
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
            */
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
//Recieve:
//1 00010 10000 0x450 BBB to base rotation
//1 00010 10001 0x451 
//1 00010 10010 0x452
//1 00010 10011 0x453
//1 00010 10100 0x454
//1 00010 10101 0x455
//1 00010 10110 0x456
//Send:
//1 10000 00010 0x602 base rotation to BBB 
//1 10001 00010 0x622 shoulder to BBB
//1 10010 00010 0x642 elbow ""
//1 10011 00010 0x662 forearm rotation ""
//1 10100 00010 0x682 diff wrist 1 ""
//1 10101 00010 0x6A2 diff wrist 2 ""
//1 10110 00010 0x6C2 hand ""
void initialize_can_addr(void) {
    uint8 setting = Can_addr_Read();
    uint8 shift = 0;
    switch(Can_addr_Read()) {
        case 0b1111:
            message_id = 0b10000;
            shift = 0;
        case 0b0001:
            message_id = 0b10001;
            shift = 1;
        case 0b0010:
            message_id = 0b10010;
            shift = 2;
        case 0b0011:
            message_id = 0b10011;
            shift = 3;
        case 0b0100:
            message_id = 0b10100;
            shift = 4;
        case 0b0101:
            message_id = 0b10101;
            shift = 5;
        case 0b0110:
            message_id = 0b10110;
            shift = 6;
    }
    
    CAN_RX_MAILBOX_0_SHIFT = CAN_RX_MAILBOX_0_SHIFT << shift;
    CAN_RX_MAILBOX_1_SHIFT = CAN_RX_MAILBOX_1_SHIFT << shift;
    
    if(uart_debug) {
        sprintf(txData, "CAN dip setting:  %x Message ID: %lx\r\n",setting, message_id);
        UART_UartPutString(txData); 
    }
}

void set_CAN_ID(uint32 priority) {
    message.id = (priority << 10) | (message_id << 5) | 0b00010;
}

void initialize(void) {
    int can_start = CAN_Start();
  //  int can_global = CAN_GlobalIntEnable();
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();
    QuadDec_Start();// QuadDec_GetCounter()
    PWM_Motor_Start();
    if(uart_debug) {
        UART_Start();
        sprintf(txData, "CAN_Start():  %u\r\n",can_start);
        UART_UartPutString(txData); 
      //  sprintf(txData, "CAN_GlobalIntEnable():  %u\r\n",can_global);
     //   UART_UartPutString(txData); 
    }
}
void CAN_Send_Encoder(void){
    //message.id = 0x1;
    data.byte[0u] = 0x14u;
    data.byte[1u] = LO8(QuadDec_GetCounter());
    data.byte[2u] = HI8(QuadDec_GetCounter());
    data.byte[3u] = 0;
    data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug) {
        sprintf(txData, "CAN_Send_Encoder: byte[0u] %x byte[1u] %x\r\n",data.byte[0u],data.byte[1u]);
        UART_UartPutString(txData); 
    }
}

void CAN_Send_Telemetry(void) {
    //message.id = 0x2;
    data.byte[0u] = 0x18u;
    data.byte[1u] = 1;
    data.byte[2u] = 2;
    data.byte[3u] = 3;
    data.byte[4u] = 4;
    CAN_SendMsg(&message);
    if(uart_debug) {
        sprintf(txData, "Telemerty: byte[0u] %x byte[1u] %x\r\n",data.byte[0u],data.byte[1u]);
        UART_UartPutString(txData); 
    }
}

void CAN_Send_Model(void) {
    //message.id = 0x3;
    data.byte[0u] = 0x12u;
    data.byte[1u] = Can_addr_Read();
   // data.byte[2u] = 0;
    //data.byte[3u] = 0;
   // data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug) {
        sprintf(txData, "Model: byte[0u] %x byte[1u] %x\r\n",data.byte[0u],data.byte[1u]);
        UART_UartPutString(txData); 
    }
}
/*
void CAN_Read(int *read) {
    // writes to the read array the data that was sent
}

void CAN_Send(int Mailbox, uint8 type, uint8 b1, uint8 b2, uint8 b3, uint8 b4) {
    int send_msg = CAN_SendMsg();
    if(uart_debug) {
        sprintf(txData, "Can send adc msg:  %u\r\n", send_msg );
        UART_UartPutString(txData);
    }
}
*/
CY_ISR(ISR_CAN)
{
    /* Clear Receive Message flag */
    CAN_INT_SR_REG = CAN_RX_MESSAGE_MASK;

    /* Switch status message received */
    if ((CAN_BUF_SR_REG & CAN_RX_MAILBOX_0_SHIFT) != 0u)
    {
        receiveMailboxNumber = CAN_RX_MAILBOX_0_SHIFT >> 1;

        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_ToBaseRotation_1);
    }

    if ((CAN_BUF_SR_REG & CAN_RX_MAILBOX_1_SHIFT) != 0u)
    {
        receiveMailboxNumber = CAN_RX_MAILBOX_ToElbow_1;
        
        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_ToShoulder_1);
    }
    
}

/*
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
