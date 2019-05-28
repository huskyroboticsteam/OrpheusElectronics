#include <stdint.h>
#include "bms.h"

#define R_2     180     // Replace with actual resistance (in kOhms)
#define R_6     33      // Replace with actual resistance (in kOhms) 
#define R_SENSE 0.001   // Replace with actual resistance (in Ohms)

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

void bms_get_data(bms_data *data)
{
    uint16_t adc_v, adc_c;

    adc_get_data(adc_v, 0xA);           // Store voltage ADC data

    adc_get_data(adc_c, 0x3);           // Store current ADC data
    
    *data = bms_convert_data(adc_v, adc_c);
}

void adc_get_data(uint16_t *data, uint8_t adc_channel)
{
    ADCON0bits.CHS = adc_channel;       // Select channel
    ADCON0bits.ADON = 1;                // Enable ADC
    ADCON0bits.GO_DONE = 1;             // Start ADC
    while(ADCON0bits.GO_DONE == 1)      // Wait for ADC to complete
        ;
    *data = ADRESL + (ADRESH * 256);    // raw 10 bit ADC data
}

bms_data bms_convert_data(uint16_t adc_v, uint16_t adc_c)
{ 
    bms_data result;

    // Voltage conversion:
    //      10 bit ADC resolution: 5.0 V / 1023
    //      Expected readings:
    //          V_33k = (V_in*33k)/(33k+180k),
    //          where V_in is between 0 and 32 V.
    //
    //      Convert from ADC int to float:
    //          V = (x * 5 / 1023)*((33k+180k)/33k);

    result.voltage = (R_2+R_6)*(adc_v*5)/(1023*R_6);

    // Current conversion:
    //      10 bit ADC resolution: 5.0 V / 1023
    //      Expected readings:
    //          I_0.001 = V_0.001 / 0.001
    //
    //          Current Sense amplifier gain: 20 V/V
    //          V_measured = 20 * V_0.001
    //
    //      Convert from ADC int to float:
    //          V_measured = x * 5 / 1023
    //          V_0.001 = V_measured / 20
    //          so I = (x * 5)/(1023*20*0.001)
    
    result.current = (adc_c * 5)/(1023*20*R_SENSE);

    return result;
}
