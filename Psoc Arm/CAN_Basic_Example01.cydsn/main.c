/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  In this project, the CAN component is configured to transmit two messages
*  over the CAN bus:
*   Message 1 - Status of Switch 1. Sent whenever there is a change in the
*               status.
*   Message 2 - ADC data. Sent every 100ms.
*
*  The component is also configured to receive data which is used to set the
*  pulse width of the PWM used in the project.
*  Both transmitted and received data are displayed on a 2x16 LCD.
*
*  This is only one part of the CAN example project. Use this example along
*  with CAN_FullCAN_Example for complete demonstration.
*
* Hardware Dependency:
*  CY8CKIT-001
*  CY8CKIT-017
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software only as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>
#include <stdio.h>

/* Switch debounce delay in milliseconds */
#define SWITCH_DEBOUNCE_UNIT   (1u)

/* Number of debounce units to count delay, before consider that switch is pressed */
#define SWITCH_DEBOUNCE_PERIOD (10u)

#define DATA_SIZE              (6u)

/* Switch state defines */
#define SWITCH_PRESSED         (0u)
#define SWITCH_RELEASED        (1u)

/* Function prototypes */
static uint32 ReadSwSwitch(void);
CY_ISR_PROTO(ISR_CAN);

/* Global variable used to store switch state */
uint8 switchState = SWITCH_RELEASED;

/* Global variable used to store ISR flag */
volatile uint8 isrFlag = 0u;


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  main() performs the following functions:
*  1: Starts the ADC, LCD, PWM, CAN components.
*  2: Starts ADC conversion.
*  3: Gets the converted result, sends message over a CAN and displays it on LCD.
*  4: Polls the status of Switch 1 and sends message over a CAN if it changes.
*  5: Sets a PWM pulse width and displays it on the LCD.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    int16 output;
    uint16 resMilliVolts;
    char8 txData[DATA_SIZE];

    LCD_Start();

    /* Display value of ADC output on LCD */
    LCD_Position(0u, 0u);
    LCD_PrintString("ADC");

    /* Display state of switch on LCD */
    LCD_Position(1u, 0u);
    LCD_PrintString("SW");

    /* Display state of PWM pulse width on LCD */
    LCD_Position(0u, 10u);
    LCD_PrintString("PWM");

    ADC_Start();
    PWM_Start();        

    /* Start ADC conversion */
    ADC_StartConvert();

    CAN_Start();

    /* Set CAN interrupt handler to local routine */
    CyIntSetVector(CAN_ISR_NUMBER, ISR_CAN);

    CyGlobalIntEnable;

    for(;;)
    {
        if (ADC_IsEndConversion(ADC_RETURN_STATUS))
        {
            /* Gets ADC conversion result */
            output = ADC_GetResult16();

            /* Saturates ADC result to positive numbers */
            if (output < 0)
            {
                output = 0;
            }

            /* Converts ADC result to milli volts */
            resMilliVolts = (uint16) ADC_CountsTo_mVolts(output);
            
            /* Sends the value of ADC output via CAN */
            CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_ADCdata) = HI8(resMilliVolts);
            CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_ADCdata) = LO8(resMilliVolts);
            CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_ADCdata) = 0u;
            CAN_TX_DATA_BYTE4(CAN_TX_MAILBOX_ADCdata) = 0u;
            CAN_TX_DATA_BYTE5(CAN_TX_MAILBOX_ADCdata) = 0u;
            CAN_TX_DATA_BYTE6(CAN_TX_MAILBOX_ADCdata) = 0u;
            CAN_TX_DATA_BYTE7(CAN_TX_MAILBOX_ADCdata) = 0u;
            CAN_TX_DATA_BYTE8(CAN_TX_MAILBOX_ADCdata) = 0u;
            CAN_SendMsgADCdata();

            /* Display value of ADC output on LCD */
            sprintf(txData, "%u.%.3u", (resMilliVolts / 1000u), (resMilliVolts % 1000u));
            txData[DATA_SIZE - 1u] = (char8) '\0';
            
            LCD_Position(0u, 4u);
            LCD_PrintString(txData);
        }

        /* Change configuration at switch press or release event */
        if (switchState != ReadSwSwitch())    /* Switch state changed status */
        {
            switchState = ReadSwSwitch();    /* Store the current switch state */
            LCD_Position(1u, 3u);

            if (switchState == SWITCH_RELEASED)
            {
                CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_switchStatus) = SWITCH_PRESSED;
                LCD_PrintString("pressed ");
            }
            else
            {
                CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_switchStatus) = SWITCH_RELEASED;
                LCD_PrintString("released");
            }
            CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_switchStatus) = 0u;
            CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_switchStatus) = 0u;
            CAN_TX_DATA_BYTE4(CAN_TX_MAILBOX_switchStatus) = 0u;
            CAN_TX_DATA_BYTE5(CAN_TX_MAILBOX_switchStatus) = 0u;
            CAN_TX_DATA_BYTE6(CAN_TX_MAILBOX_switchStatus) = 0u;
            CAN_TX_DATA_BYTE7(CAN_TX_MAILBOX_switchStatus) = 0u;
            CAN_TX_DATA_BYTE8(CAN_TX_MAILBOX_switchStatus) = 0u;            

            /* Send CAN message with switch state */
            CAN_SendMsgswitchStatus();
        }
        
        if (isrFlag != 0u)
        {
            /* Set PWM pulse width */
            PWM_WriteCompare(CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_0));

            /* Display value of PWM pulse width on LCD */
            LCD_Position(0u, 14u);
            LCD_PrintInt8(CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_0));
            
            /* Clear the isrFlag */
            isrFlag = 0u;
        }

        CyDelay(100u);
    }
}


/*******************************************************************************
* Function Name: ISR_CAN
********************************************************************************
*
* Summary:
*  This ISR is executed at a Receive Message event and set the isrFlag.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(ISR_CAN)
{
    /* Clear Receive Message flag */
    CAN_INT_SR_REG.byte[1u] = CAN_RX_MESSAGE_MASK;

    /* Set the isrFlag */
    isrFlag = 1u;    

    /* Acknowledges receipt of new message */
    CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_0);
}


/*******************************************************************************
* Function Name: ReadSwSwitch
********************************************************************************
* Summary:
*  Reads and returns the current status of the switch.
*
* Parameters:
*  None
*
* Return:
*  Returns a non-zero value, if switch is pressed, and a zero value otherwise.
*
*******************************************************************************/
static uint32 ReadSwSwitch(void)
{
    uint32 heldDown;
    uint32 swStatus;

    swStatus = 0u;  /* Switch is not active */
    heldDown = 0u;  /* Reset debounce counter */

    /* Wait for debounce period before determining whether the switch is pressed */
    while (Switch1_Read() == SWITCH_PRESSED)
    {
        /* Count debounce period */
        CyDelay(SWITCH_DEBOUNCE_UNIT);
        ++heldDown;

        if (heldDown > SWITCH_DEBOUNCE_PERIOD)
        {
            swStatus = 1u; /* Switch is pressed */
            break;
        }
    }

    return (swStatus);
}

/* [] END OF FILE */
