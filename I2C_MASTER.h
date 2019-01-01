#ifndef I2C_MASTER
#define I2C_MASTER

void I2CInit (void);
void I2CWait ();
void I2CStart (uint8_t address);
void I2CStop (void);
void I2CWrite (unsigned char data);
uint8_t I2CRead(void);

#endif 