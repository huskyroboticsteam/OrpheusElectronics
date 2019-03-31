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
#include <stdio.h>

#define TX_DATA_SIZE            (100u)
char8 txData[TX_DATA_SIZE];
int main(void)
{
    
    ADC_SAR_Seq_1_Start();
    ADC_SAR_Seq_1_StartConvert();

    UART_Start();

    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint16 output;
        /* Start Opamp component */
    Opamp_Start();

    /* Sets Opamp power mode to High power */
    Opamp_SetPower(Opamp_HIGH_POWER);
    for(;;)
    {
        output = ADC_SAR_Seq_1_GetResult16(0u);
        sprintf(txData, "ADC value: %d\r\n", (int16) ADC_SAR_Seq_1_CountsTo_mVolts(0u,output));
        UART_UartPutString(txData);
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
