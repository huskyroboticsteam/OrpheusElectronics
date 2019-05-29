#ifndef COMM_H
#define COMM_H

#include "conbits.h"

#define CAN_RESET_INS 0b11000000
#define CAN_READ_INS 0b00000011
#define CAN_READ_RX_BUFF_INS(n, m) 0b10010000|(n<<2)|(m<<1)
#define CAN_WRITE_INS 0b00000010
#define CAN_READ_STATUS_INS 0b10100000
#define CAN_RX_STAUTS_INS 0b10110000
#define CAN_BIT_MODIFY_INS 0b00000101

// spi_begin: initialize with the following SPI configuration
//      SPI Mode:           Master F_OSC/4
//      SPI Data Sample:    Sample middle
//      SPI Clock Edge:     Idle to active
//      SPI Clock Poll:     Idle low
void spi_begin(void);

// spi_write: writes 8 bit data to SSPBUF
void spi_write(char dat);

// spi_read: return 8 bit data
char spi_read(void);

// Currently unimplemented.
void can_reset(void);

// Currently unimplemented.
void can_write(char dat);

// Currently unimplemented.
char can_read(void);

#endif
