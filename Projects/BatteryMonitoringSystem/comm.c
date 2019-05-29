#include "comm.h"

// Initialize SPI Configuration
void spi_begin(void)
{
    TRISCbits.TRISC5 = 0;   // Set RC5 as output
    SSPSTAT = 0;
    SSPSTATbits.CKE = 1;    // SPI Clock Edge Select bit: Active to idle
    SSPSTATbits.SMP = 0;    // Input data sampled at middle of data output time
    SSPCON = 0;
    SSPCONbits.CKP = 0;     // Idle state for clock is a low level
    SSPCONbits.SSPEN = 1;   // Enables serial port and configures SCK< DO, SDI,
                            // and SS as the source of the serial port pins.
    SSPCONbits.SSPM = 0;    // SPI Master mode, clock = F_OSC/4
}

// spi_write: writes 8 bit data to register SSPBUF at file register 13h
void spi_write(char dat)
{
    SSPBUF = dat;
}

// spi_read: return 8 bit data
char spi_read(void)
{
    while(!BF)          // Wait for Buffer Fill register
        ;
    return SSPBUF;      // Get data from register
}
