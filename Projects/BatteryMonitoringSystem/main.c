/************************************************************************
*                                                                       *
*   Filename:      main.c                                               *
*   Date:          5/27/19                                              *
*   File Version:  0.1                                                  *
*                                                                       *
*   Author:        Hansem Ro                                            *
*                                                                       *
*************************************************************************
*                                                                       *
*   Architecture:  Midrange PIC                                         *
*   Processor:     16F886                                               *
*   Compiler:      MPLAB XC8 v2.05 (Free mode)                          *
*                                                                       *
*************************************************************************
*                                                                       *
*   Description:                                                        *
*                                                                       *
*   Goal:                                                               *
*   Get current/voltage data and send them via CAN                      *
*   Smart relay switch: kill device when:                               *
*       +30 A detected                                                  *
*       +30-33 V detected                                               *
*       -15 V detected                                                  *
*                                                                       *
*   Implmentation:                                                      *
*   Interface with CAN controller and transceiver using SPI             *
*   Measure voltage across 33k resistor.                                *
*   Measure current from current sense amplifier.
*                                                                       *
*************************************************************************
*                                                                       *
*   Pin assignments:                                                    *
*       RA0 = (O) Standby - MCP25625                                    *
*       RA1 = (O) Chip Select - MCP25625                                *
*       RA3/AN3 = (ADC) Current Sense Amp output - INA240A1PWR (OUT)    *
*       RA5 = (O) RESET - MCP25625                                      *
*       RA7 = (O) MCP25625 CLKOUT (16MHz)                               *
*       RB0 = (O) Relay Control - SN74LVC1G32DCKR                       *
*       RB1/AN10 = (ADC) Voltage Sense                                  *
*       RB6 = (IO) Header                                               *
*       RB7 = (IO) Header                                               *
*       RC3 = (O) SPI Clock Output - MCP25625 (SCK)                     *
*       RC4 = (I) SDI - MCP25625 (SO)                                   *
*       RC5 = (O) SDO - MCP25625 (SI)                                   *
*       RC6 = (IO) Header - J4 pin 3                                    *
*       RC7 = (IO) Header - J4 pin 2                                    *
*       RE3 = MCLR                                                      *
*                                                                       *
************************************************************************/

#include <xc.h>
#include <pic16f886.h>
#include <stdint.h>
#include <stdbool.h>
#include "conbits.h"
#include "bms.h"
#include "comm.h"

#define POLLTIME 200 // Polls every 200 ms.

void interrupt isr(void);

bms_data batt_data, *p_data;
uint8_t polltick = 0;

void main(void)
{
    // Configure Ports/Pins
    PORTA = 0;                      // Clear bits
    TRISA = ~(1<<0|1<<1|1<<5|1<<7); // Set RA0, RA1, RA5, and RA7 as output

    // Relay switch is left at high to allow normal operation
    TRISB = ~(1<<0);                // Set RB0 as output
    PORTB = 0x1;                    // Clear bits except leave RB0 high

    PORTC = 0;                      // Clear bits
    TRISC = ~(1<<3|1<<5);           // Set RC3 and RC5 as output

    // Configure ADC
    bms_begin();

    // Configure Timer and Interrupts
    TMR0 = 0;
    OPTION_REGbits.T0CS = 0;        // Internal instruction cycle clock (F_OSC/4)
    OPTION_REGbits.PSA = 0;         // Prescaler assigned to Timer0 module.
    OPTION_REGbits.PS = 0x3;        // 1:16 prescale value

    INTCONbits.T0IE = 1;            // Enable Timer0 Overfow Interrupt
    INTCONbits.T0IF = 0;            // Clear Timer0 Overflow Interrupt
    ei();                           // Enable Global Interrupt
    INTCONbits.PEIE = 1;            // Enable Peripheral Interrupt

    // Configure SPI
    spi_begin();

    // Configure CAN
    // can_begin();
    
    for(;;)     // Main loop
    {
        if(polltick >= POLLTIME) {  // After approximately 200 ms,
            p_data = &batt_data;
            bms_get_data(p_data);// get BMS data
        }
    }
}

void interrupt isr(void)
{
    INTCONbits.GIE = 0;            // Clear global interrupt

    if(INTCONbits.T0IF) {           // If Timer0 register overflows
        polltick++;                 // Count the number of overflows ~ every 1024 us.
        INTCONbits.T0IF = 0;        // Clear overflow interrupt
    }

    INTCONbits.GIE = 1;            // Enable Global Interrupt
}
