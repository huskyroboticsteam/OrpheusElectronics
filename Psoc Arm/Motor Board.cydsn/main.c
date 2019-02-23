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
uint32 CAN_RX_MAILBOX_0_SHIFT  = 0b10000000;

uint16 CAN_RX_MAILBOX_1 = 0u;
uint16 CAN_RX_MAILBOX_0 = 7u;


#define TX_DATA_SIZE            (100u)
#define PWM_PERIOD = 1000;

CY_ISR_PROTO(ISR_CAN);
//global var
volatile uint8 uart_debug = 1;
int GEAR_RATIO;
int CAN_TIMEOUT;
int pwm_compare;
int i = 0;
int lastp = 0;
int kp,ki,kd;
uint8 mode = 2;
uint8 send_data = 1;
volatile uint8 isrFlag = 0u;

struct Can_data Can_rx_pwm, Can_rx_angle;

int mailbox = 0x000;
uint8 emergency = 0;
char8 txData[TX_DATA_SIZE];
/* Global variables used to store configuration and data for BASIC CAN mailbox */
CAN_DATA_BYTES_MSG data;
CAN_TX_MSG message;

volatile uint8 receiveMailbox = 0;


CY_ISR(Period_Reset_Handler) {
    int timer = Timer_1_ReadStatusRegister();
    if(uart_debug) {
        sprintf(txData,"Period interupt triggerd %x\r\n", timer);
        UART_UartPutString(txData);
    }
    send_data = 1;
}

CY_ISR(Pin_Limit_Handler){
    if(uart_debug) {
        sprintf(txData,"Limit interupt triggerd\r\n");
        UART_UartPutString(txData);
    }
    set_PWM(pwm_compare);
}

int main(void)
{

        /* BASIC CAN mailbox configuration */
    message.dlc = 4u;
    message.ide = MESSAGE_IDE;
    message.irq = MESSAGE_IRQ;
    message.msg = &data;
    message.rtr = MESSAGE_RTR;
    
    Pin_Test_Write(0);

    
    initialize();
    CAN_GlobalIntEnable();
    CyIntSetVector(CAN_ISR_NUMBER, ISR_CAN);
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
    initialize_can_addr();
    set_CAN_ID(0b1);
    int up = 0;
    pwm_compare = 0;
    int test = 0;
    set_PWM(0);
    for(;;)
    {
        if(!emergency) {
        //UART_UartPutString(txData); 
           //Spare1_Write((Status_Reg_Switches_Read() & 0b10) >> 0b1);
           //Spare2_Write(Status_Reg_Switches_Read() & 0b01);
            //CAN_Send_Model();
            //CyDelay(1000);
            
            
            if (receiveMailbox == 1)
            {               

                if(!Can_rx_pwm.done) {
                    if(mode == 0) {
                        if(uart_debug) {
                            sprintf(txData, "B1: %d, B2: %d done %x\r\n",Can_rx_pwm.b1, Can_rx_pwm.b2, Can_rx_pwm.done);
                            UART_UartPutString(txData);
                        }
                        Can_rx_pwm.done = 1;
                        if(Can_rx_pwm.b2 & 0b01) {
                            set_PWM((int)Can_rx_pwm.b1);
                        }
                        else {
                            set_PWM(-(int)Can_rx_pwm.b1);
                        }
                    } else {
                        if(uart_debug) {
                            sprintf(txData, "Mode is not set to 0\r\n");
                            UART_UartPutString(txData);
                        }
                    }
                }
                if(mode != 1 || mode != 0) {
                    Can_rx_angle.done = 1;
                    Can_rx_pwm.done = 1;
                }
            }
            receiveMailbox = !Can_rx_pwm.done | !Can_rx_angle.done;
            if(send_data) {
                if(uart_debug) {
                    sprintf(txData,"\nSending Data... \r\n");
                    UART_UartPutString(txData);
                }
                CAN_Send_Encoder(); 
                send_data = 0;
            }
            
            
           // CAN_Send_Model();
            /*
            CyDelay(100);
            if(up){
                pwm_compare += 10;
            } else {
                pwm_compare -= 10;   
            }
            if(pwm_compare > 255) {
                up = 0;   
            } else if (pwm_compare < -255) {
                up = 1;
            }
            set_PWM(pwm_compare);
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
void emergency_halt(void) {
    PWM_Motor_Stop();
    emergency = 1;
    // stops all motors;
    // waits for restart CAN signal.
}

inline void set_data(uint16 addr){
        if(CAN_RX_DATA_BYTE1(addr) == 0x00) {
            mode = CAN_RX_DATA_BYTE2(addr);
        }
        if(CAN_RX_DATA_BYTE1(addr) == 0x02) {
            Can_rx_pwm.b1 = CAN_RX_DATA_BYTE2(addr);
            Can_rx_pwm.b2 = CAN_RX_DATA_BYTE3(addr);
            Can_rx_pwm.b3 = CAN_RX_DATA_BYTE4(addr);
            Can_rx_pwm.b4 = CAN_RX_DATA_BYTE5(addr);
            Can_rx_pwm.done = 0;
        }
        if(CAN_RX_DATA_BYTE1(addr) == 0x04) {
            Can_rx_angle.b1 = CAN_RX_DATA_BYTE2(addr);
            Can_rx_angle.b2 = CAN_RX_DATA_BYTE3(addr);
            Can_rx_angle.b3 = CAN_RX_DATA_BYTE4(addr);
            Can_rx_angle.b4 = CAN_RX_DATA_BYTE5(addr);
            Can_rx_angle.done = 0;
        }
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
        case 0b000:
            message_id = 0b10000;
            shift = 0;
            break;
        case 0b001:
            message_id = 0b10001;
            shift = 1;
            break;
        case 0b010:
            message_id = 0b10010;
            shift = 2;
            break;
        case 0b011:
            message_id = 0b10011;
            shift = 3;
            break;
        case 0b100:
            message_id = 0b10100;
            shift = 4;
            break;
        case 0b101:
            message_id = 0b10101;
            shift = 5;
            break;
        case 0b110:
            message_id = 0b10110;
            shift = 6;
            break;
    }
    
    CAN_RX_MAILBOX_0_SHIFT = CAN_RX_MAILBOX_0_SHIFT << shift;
    CAN_RX_MAILBOX_1_SHIFT = CAN_RX_MAILBOX_1_SHIFT << shift;
    CAN_RX_MAILBOX_0 += shift;
    CAN_RX_MAILBOX_1 += shift;
    
    if(uart_debug) {
        sprintf(txData, "CAN dip setting:  %x Message ID: %lx\r\n",setting, message_id);
        UART_UartPutString(txData); 
        sprintf(txData, "Can shift: %x   P0Mailbox: %x P1Mailbox %x\r\n",shift, CAN_RX_MAILBOX_0, CAN_RX_MAILBOX_1);
        UART_UartPutString(txData); 
    }
}

void set_CAN_ID(uint32 priority) {
    message.id = (priority << 10) | (message_id << 5) | 0b00010;
}

void initialize(void) {
    int can_start = CAN_Start();
    Status_Reg_Switches_InterruptEnable();
    //Timer_1_Start();
   // ADC_SAR_Seq_1_Start();
    //ADC_SAR_Seq_1_StartConvert();
    QuadDec_Start();
    PWM_Motor_Start();
    if(uart_debug) {
        UART_Start();
        sprintf(txData, "CAN_Start():  %u\r\n",can_start);
        UART_UartPutString(txData); 
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
        sprintf(txData, "CAN_Send_Encoder: byte[0u] %x byte[1u] %x byte[2u] %x\n QuadDec Count %d\r\n",
            data.byte[0u],data.byte[1u],data.byte[2u],
            QuadDec_GetCounter());
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
        sprintf(txData, "Telemerty: byte[0u] %x byte[1u] %x\r\n",(uint8)data.byte[0u],(uint8)data.byte[1u]);
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

CY_ISR(ISR_CAN)
{
    /* Clear Receive Message flag */
    CAN_INT_SR_REG = CAN_RX_MESSAGE_MASK;
    if(uart_debug) {
        UART_UartPutString("\n Can rx triggered\n");   
    }
    /* Switch status message received */
    if ((CAN_BUF_SR_REG & CAN_RX_MAILBOX_0_SHIFT) != 0u)
    {   
        if(uart_debug){
            UART_UartPutString("P0 recieved\n");    
        }
        set_data(CAN_RX_MAILBOX_0);

        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_0);
    }

    if ((CAN_BUF_SR_REG & CAN_RX_MAILBOX_1_SHIFT) != 0u)
    {
        if(uart_debug){
            UART_UartPutString("P1 recieved\n\n");    
        }
        set_data(CAN_RX_MAILBOX_1);
        
        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_1);
    }
    
}

    // takes between -255 and 255
void set_PWM(int compare) {
    if (compare < -255 || compare > 255) { return; }
    uint8 status = Status_Reg_Switches_Read();
    if (compare < 0 && !(status & 0b01)) {
        Pin_Direction_Write(0);
        PWM_Motor_WriteCompare(-compare);
    } else if (compare > 0 && !(status & 0b10)){
        Pin_Direction_Write(1);
        PWM_Motor_WriteCompare(compare);
    } else {
        PWM_Motor_WriteCompare(0);   
    }
}


void set_Position(int degrees) {
    int PWM = position_PID(degrees_to_tick(degrees));
    if(PWM > 255){
        set_PWM(255);   
    } else if(PWM < -255) {
        set_PWM(-255);
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
