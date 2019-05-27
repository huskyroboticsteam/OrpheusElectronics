#ifndef COMM_H
#define COMM_H

#include "conbits.h"

// SPI configuration:
//      SPI Mode:           Master F_OSC/4
//      SPI Data Sample:    Sample middle
//      SPI Clock Edge:     Idle to active
//      SPI Clock Poll:     Idle low
void spi_begin(void);

void spi_write(char dat);

char spi_read(void);

void can_begin(void);

void can_write(char dat);

char can_read(void);

#endif