#include <stdint.h>
#include "bms.h"

#define VOLT_FACTOR 1.0 // !! CHANGE
#define CURR_FACTOR 1.0 // !! CHANGE
#define T_AD 32.0/_XTAL_FREQ
#define ADC_RES (5.0/1023.0) // 5 V / 1024 (10 bit)

// Initialize pins used for ADC current and voltage measurement
void bms_begin(void)
{
    // Configure pins
    TRISAbits.TRISA3 = 1;       // Set RA3 and RB1 port direction as input:
    TRISBbits.TRISB1 = 1;       //    disable output driver

    // Configure pins as ADC input
    ANSELbits.ANS3 = 1;         // Set RA3 as analog input
    ANSELHbits.ANS10 = 1;       // Set RB1 as analog input

    // Other configuration
    ADCON0 = 0;
    ADCON0bits.ADCS1 = 1;       // ADCS - 10: A/D Conversion Clock 
    ADCON0bits.ADCS0 = 0;       //      F_OSC/32
    ADCON1 = 0;
    ADCON1bits.ADFM = 1;        // AD Conversion Result Format: right justified
    ADCON1bits.VCFG1 = 0;       // V_SS reference
    ADCON1bits.VCFG0 = 0;       // V_DD reference
}

// bms_get_data: returns bms_data
// TODO: implement checks
bms_data bms_get_data(void)
{
    // Voltage
    ADCON0bits.CHS3 = 1;    // Select RB1/AN10 as ADC input channel
    ADCON0bits.CHS2 = 0;    
    ADCON0bits.CHS1 = 1;    
    ADCON0bits.CHS0 = 0;    
    ADCON0bits.ADON = 1;    // Enable ADC
    ADCON0bits.GO_DONE = 1;
    while(GO_DONE == 1) {
        ;                   // Wait until GO_DONE bit is set to 1
    }
    uint8_t volt = ADRESL + (ADRESH * 256);
    ADCON0bits.GO_DONE = 0;
    // ADCON0bits.ADON = 0;

    // Current
    ADCON0bits.CHS3 = 0;    // Select RA3/AN3 as ADC input channel
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 1;
    ADCON0bits.CHS0 = 1;
    //ADCON0bits.ADON = 1;    // Enable ADC
    ADCON0bits.GO_DONE = 1;
    while(GO_DONE == 1) {
        ;
    }
    uint8_t curr = ADRESL + (ADRESH * 256);
    ADCON0bits.GO_DONE = 0;
    ADCON0bits.ADON = 0;
    return bms_convert_data(volt, curr);
}

// bms_data: convert the data into SI units so that it can be
// understood.
bms_data bms_convert_data(uint8_t volt, uint8_t curr)
{
    bms_data result;
    result.voltage = volt * VOLT_FACTOR;
    result.current = curr * CURR_FACTOR;
    return result;
}