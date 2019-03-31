/******************************************************************************
* File Name: main.c
*
* Version: 2.0
*
* Description: This example project demonstrates the basic operation of the I2C master (SCB 
* mode) component using low level functions. The I2C master sends the command packets
* to the I2C slave to control the RGB LED color. The packet with a status is read back.
*
* Related Document: CE222306.pdf
*
* Hardware Dependency: CY8CKIT-042 PSoC 4 Pioneer Kit 
*
******************************************************************************
* Copyright (2018), Cypress Semiconductor Corporation.
******************************************************************************
* This software, including source code, documentation and related materials
* ("Software") is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and 
* foreign), United States copyright laws and international treaty provisions. 
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the 
* Cypress source code and derivative works for the sole purpose of creating 
* custom software in support of licensee product, such licensee product to be
* used only in conjunction with Cypress's integrated circuit as specified in the
* applicable agreement. Any reproduction, modification, translation, compilation,
* or representation of this Software except as specified above is prohibited 
* without the express written permission of Cypress.
* 
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED 
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* Cypress reserves the right to make changes to the Software without notice. 
* Cypress does not assume any liability arising out of the application or use
* of Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use as critical components in any products 
* where a malfunction or failure may reasonably be expected to result in 
* significant injury or death ("ACTIVE Risk Product"). By including Cypress's 
* product in a ACTIVE Risk Product, the manufacturer of such system or application
* assumes all risk of such use and in doing so indemnifies Cypress against all
* liability. Use of this Software may be limited by and subject to the applicable
* Cypress software license agreement.
*****************************************************************************/
#include "project.h"

/************************************
*             Constants
************************************/

/* I2C Status */
#define TRANSFER_CMPLT      (0x00u)
#define TRANSFER_ERROR      (0xFFu)
#define READ_CMPLT          (TRANSFER_CMPLT)

/* Command Valid Status */
#define STS_CMD_DONE        (0x00u)
#define STS_CMD_FAIL        (0xFFu)

/* Timeout */
#define I2C_TIMEOUT         (100u)

/* I2C Slave Address */
#define I2C_SLAVE_ADDR      (0x09u)

/* I2C Buffer Sizes */
#define WR_BUFFER_SIZE      (5u)
#define RD_BUFFER_SIZE      (3u)

/* Buffer offsets */
#define WR_BUFFER_SOP_POS   (0u)
#define WR_BUFFER_RED_POS   (1u)
#define WR_BUFFER_GREEN_POS (2u)
#define WR_BUFFER_BLUE_POS  (3u)
#define WR_BUFFER_EOP_POS   (4u)
#define RD_BUFFER_SOP_POS   (0u)
#define RD_BUFFER_STS_POS   (1u)
#define RD_BUFFER_EOP_POS   (2u)

/* Buffer values */
#define BUFFER_SOP          (0x01u)
#define BUFFER_EOP          (0x17u)

/* Color values */
#define COLOR_RED       (0u)
#define COLOR_GREEN     (1u)
#define COLOR_BLUE      (2u)
#define COLOR_CYAN      (3u)
#define COLOR_PURPLE    (4u)
#define COLOR_YELLOW    (5u)
#define COLOR_WHITE     (6u)

/***********************************
* Create a write buffer
* Frame:
* [SL_ADDR:SOP:RED:GREEN:BLUE:EOP]
***********************************/
uint8 buffer[WR_BUFFER_SIZE];

/***********************************
* Create a buffer to store read data
* Frame:
* [SOP:STS:EOP]
***********************************/
uint8 rdBuffer[RD_BUFFER_SIZE];

/*****************************************************************************
* Function Name: CreateCommandPacketBuffer()
******************************************************************************
* Params: cmd
* The command to be written to the slave device
*
* Sets up the buffer of data to write to the 
* slave device.
*
*****************************************************************************/
void CreateCommandPacketBuffer(uint8 cmd)
{
    /* Set the Start and End of packet values */
    buffer[WR_BUFFER_SOP_POS]  = BUFFER_SOP;
    buffer[WR_BUFFER_EOP_POS]  = BUFFER_EOP;
    
    /* Write color values to buffer positions */
    switch(cmd)
    {
        case COLOR_RED:
            buffer[WR_BUFFER_RED_POS]   = 0xFF;
            buffer[WR_BUFFER_GREEN_POS] = 0x01;
            buffer[WR_BUFFER_BLUE_POS]  = 0x00;
            break;
        case COLOR_GREEN:
            buffer[WR_BUFFER_RED_POS]   = 0x00;
            buffer[WR_BUFFER_GREEN_POS] = 0xFF;
            buffer[WR_BUFFER_BLUE_POS]  = 0x00;
            break;
        case COLOR_BLUE:
            buffer[WR_BUFFER_RED_POS]   = 0x00;
            buffer[WR_BUFFER_GREEN_POS] = 0x00;
            buffer[WR_BUFFER_BLUE_POS]  = 0xFF;
            break;
        case COLOR_CYAN:
            buffer[WR_BUFFER_RED_POS]   = 0x00;
            buffer[WR_BUFFER_GREEN_POS] = 0x77;
            buffer[WR_BUFFER_BLUE_POS]  = 0x77;
            break;
        case COLOR_PURPLE:
            buffer[WR_BUFFER_RED_POS]   = 0x7F;
            buffer[WR_BUFFER_GREEN_POS] = 0x00;
            buffer[WR_BUFFER_BLUE_POS]  = 0x7F;
            break;
        case COLOR_YELLOW:
            buffer[WR_BUFFER_RED_POS]   = 0x7F;
            buffer[WR_BUFFER_GREEN_POS] = 0x7F;
            buffer[WR_BUFFER_BLUE_POS]  = 0x00;
            break;
        case COLOR_WHITE:
            buffer[WR_BUFFER_RED_POS]   = 0x7F;
            buffer[WR_BUFFER_GREEN_POS] = 0x7F;
            buffer[WR_BUFFER_BLUE_POS]  = 0x7F;
            break;
        
        default:
            break;
    }
}    

/********************************************************************************
* Function Name: mI2CWriteCommandPacket
******************************************************************************
* Params: command
* The command to be written to the slave device
*
* Sets up the buffer of data to write to the 
* slave device. Uses low-level API I2CMasterSendStart, I2CMasterWriteByte
* and I2CMasterSendStop
*
********************************************************************************/
uint8 WriteCommandPacket(uint8 command)
{
    uint8 errorStatus = 0;
    uint8 status = TRANSFER_ERROR;
    
    /* Create packet to send to slave */
    CreateCommandPacketBuffer(command);
    
    /* Send start condition */
    if(0u == mI2C_I2CMasterSendStart(I2C_SLAVE_ADDR, mI2C_I2C_WRITE_XFER_MODE, I2C_TIMEOUT))
    {  
        /* Write bytes from the write buffer to the Slave */
        uint8 cnt = 0;
        do
        {
            /* Write byte and recieve ACK/NACK */
            errorStatus = mI2C_I2CMasterWriteByte(buffer[cnt], I2C_TIMEOUT);
            ++cnt;
        }    
        while((errorStatus == mI2C_I2C_MSTR_NO_ERROR) && (cnt < WR_BUFFER_SIZE));
    }
    
    /* Transfer succeeds send stop and return Success */
    if((errorStatus == mI2C_I2C_MSTR_NO_ERROR)      ||
       (errorStatus == mI2C_I2C_MASTER_CMD_M_NACK))
    {
        if(mI2C_I2CMasterSendStop(I2C_TIMEOUT) == mI2C_I2C_MSTR_NO_ERROR)
        {
            status = TRANSFER_CMPLT;
        }
    }
    
    return(status);
}    

/*****************************************************************************
* Function Name: ReadStatusPacket
******************************************************************************
* Reads the status of the last write operation to the slave.
* Uses low level functions SCB_I2CMasterSendStart(), SCB_I2CMasterReadByte(),
* SCB_I2CMasterSendStop()
*
* Return:
*  Status of the transfer. There are two statuses
*  - TRANSFER_CMPLT: transfer completed successfully.
*  - TRANSFER_ERROR: an error occurred durring transfer.
*
*****************************************************************************/
static uint8 ReadStatusPacket(void)
{   
    uint8 errorStatus;
    uint8 status = TRANSFER_ERROR;
    
    /* Send start condition and store read bytes in rdBuffer[] until end of buffer is reached */
    errorStatus = mI2C_I2CMasterSendStart(I2C_SLAVE_ADDR, mI2C_I2C_READ_XFER_MODE, I2C_TIMEOUT);
    if(errorStatus == mI2C_I2C_MSTR_NO_ERROR)
    {
        uint8 cnt = 0;
        uint8 cmd = mI2C_I2C_ACK_DATA;
        
        do
        {
            if (cnt == (RD_BUFFER_SIZE - 1U))
            {
                /* Send NACK on last byte */
                cmd = mI2C_I2C_NAK_DATA;
            }
            /* Read data from slave and store in rdBuffer[] */
            errorStatus = mI2C_I2CMasterReadByte(cmd, rdBuffer + cnt, I2C_TIMEOUT);
            ++cnt;
        }
        while ((errorStatus == mI2C_I2C_MSTR_NO_ERROR) && (cnt < RD_BUFFER_SIZE));
    }
    
    /* If read succeeds, send stop condition and return success */
    if ((errorStatus == mI2C_I2C_MSTR_NO_ERROR)     ||
        (errorStatus == mI2C_I2C_MASTER_CMD_M_NACK))
    {
        if (mI2C_I2CMasterSendStop(I2C_TIMEOUT) == mI2C_I2C_MSTR_NO_ERROR)
        {
            /* Check that data read from the slave is correct */
            if ((BUFFER_SOP == rdBuffer[RD_BUFFER_SOP_POS]) &&
                (BUFFER_EOP == rdBuffer[RD_BUFFER_EOP_POS]) &&
                (STS_CMD_DONE == rdBuffer[RD_BUFFER_STS_POS]))
            {
                status = TRANSFER_CMPLT;
            }
        }    
    }
    return(status);
}    
/*****************************************************************************
*Function Name: main()
******************************************************************************
*
* Main function performs the following actions:
*   1. Initializes I2C Component as master.
*   2. Writes command packets to the slave.
*   3. Reads back the status of the write from the slave.
*   4. Iterates through each command and loops back when the maximum number 
*      of commands is complete.
*
*****************************************************************************/
int main(void)
{
    uint8 command = COLOR_RED;
    
    CyGlobalIntEnable; 
    
    /* Initialize Components */
    mI2C_Start();
    
    for(;;)
    {
        /* If previous transfer succeeded, write the next command */
        if (TRANSFER_CMPLT == WriteCommandPacket(command))
        {
            /* Read back the status of the previous write */
            if (READ_CMPLT == ReadStatusPacket())
            {
                /* Set the next LED color */
                command++;
                if(command > COLOR_WHITE)
                {
                    command = COLOR_RED;
                }    
            }
            /* Delay for 0.5 Seconds between LED color changes */
            CyDelay(500);
        }    
    }
}

/* [] END OF FILE */
