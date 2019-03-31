/******************************************************************************
* File Name: main.c
*
* Version: 2.0
*
* Description: This example project demonstrates the basic operation of the I2C master (SCB 
* mode) component using high-level functions. The I2C master sends the command packets
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

#include <project.h>

/***************************************
*              Constants
****************************************/
    
#define I2C_SLAVE_ADDR      (0x9u)

/* Buffer and packet size */
#define BUFFER_SIZE         (5u)
#define PACKET_SIZE         (BUFFER_SIZE)
#define RD_BUFFER_SIZE      (3u)

/* Packet positions */
#define PACKET_SOP_POS      (0u)
#define PACKET_RED_POS      (1u)
#define PACKET_GREEN_POS    (2u)
#define PACKET_BLUE_POS     (3u)
#define PACKET_EOP_POS      (4u)
#define RD_PACKET_SOP_POS   (0u)
#define RD_PACKET_STS_POS   (1u)
#define RD_PACKET_EOP_POS   (2u)

/* Start and end of packet markers */
#define PACKET_SOP          (0x01u)
#define PACKET_EOP          (0x17u)

/* Command statuses */
#define STS_CMD_DONE        (0x00u)
#define STS_CMD_FAIL        (0xFFu)

/* Transfer statuses */
#define TRANSFER_CMPLT      (0x00u)
#define TRANSFER_ERROR      (0xFFu)

/* List of supported commands */
#define COLOR_RED       (0u)
#define COLOR_GREEN     (1u)
#define COLOR_BLUE      (2u)
#define COLOR_CYAN      (3u)
#define COLOR_PURPLE    (4u)
#define COLOR_YELLOW    (5u)
#define COLOR_WHITE     (6u)

/* Time between LED color changes (ms) */
#define CMD_TO_CMD_DELAY    (500u)

/* Create the buffers for writing and reading */
uint8_t buffer[BUFFER_SIZE];
uint8_t rd_Buffer[RD_BUFFER_SIZE];

/********************************************************************************
* Function Name: CreateCommandPacketBuffer
*********************************************************************************
* This function initializes the buffer with data related to color.
*  
* Parameters: cmd
*
* Depending on this value packet is created for different colors and sent to slave.
*   - COLOR_RED:    set red color of the LED.
*   - COLOR_GREEN:  set green color of the LED.
*   - COLOR_BLUE:   set blue color of the LED.
*   - COLOR_CYAN:   set cyan color of the LED.
*   - COLOR_PURPLE: set purple color of the LED.
*   - COLOR_YELLOW: set yellow color of the LED.
*   - COLOR_WHITE:  set white color of the LED.
*
*********************************************************************************/
static void CreateCommandPacketBuffer(uint8_t cmd)
{ 
    /* Initialize buffer with commands to be sent. */
    buffer[PACKET_SOP_POS] = PACKET_SOP;
    buffer[PACKET_EOP_POS] = PACKET_EOP;
    
    switch(cmd)
    {
        case COLOR_RED:
            buffer[PACKET_RED_POS] =   0xFF;
            buffer[PACKET_GREEN_POS] = 0x00;
            buffer[PACKET_BLUE_POS] =  0x00;
            break;
        
        case COLOR_GREEN:
            buffer[PACKET_RED_POS] =   0x00;
            buffer[PACKET_GREEN_POS] = 0xFF;
            buffer[PACKET_BLUE_POS] =  0x00;
            break;
        
        case COLOR_BLUE:
            buffer[PACKET_RED_POS] =   0x00;
            buffer[PACKET_GREEN_POS] = 0x00;
            buffer[PACKET_BLUE_POS] =  0xFF;
            break;
        
        case COLOR_CYAN:
            buffer[PACKET_RED_POS] =   0x00;
            buffer[PACKET_GREEN_POS] = 0x7F;
            buffer[PACKET_BLUE_POS] =  0x7F;
            break;
        
        case COLOR_PURPLE:
            buffer[PACKET_RED_POS] =   0x7F;
            buffer[PACKET_GREEN_POS] = 0x00;
            buffer[PACKET_BLUE_POS] =  0x7F;
            break;
        
        case COLOR_YELLOW:
            buffer[PACKET_RED_POS] =   0x7F;
            buffer[PACKET_GREEN_POS] = 0x7F;
            buffer[PACKET_BLUE_POS] =  0x00;
            break;
        
        case COLOR_WHITE:
            buffer[PACKET_RED_POS] =   0xFF;
            buffer[PACKET_GREEN_POS] = 0xFF;
            buffer[PACKET_BLUE_POS] =  0xFF;
            break;
        
        default:
            break;  
    } 
}
/********************************************************************************
* Function Name: WriteCommandPacket()
******************************************************************************
* Uses high level api to write to the 
* slave device.
*
* Parameters: cmd
* The command to be written to the slave device
*
* Return:
* Status of the transfer. There are two statuses
*  - TRANSFER_CMPLT: transfer completed successfully.
*  - TRANSFER_ERROR: an error occurred durring transfer.
*
********************************************************************************/
uint32 WriteCommandPacket(uint8 cmd)
{   
    uint32 status = TRANSFER_ERROR;

    buffer[0u] = 0x10;
    buffer[1u] = 0x20;
    buffer[2u] = 0x30;
    buffer[3u] = 0x40;
    buffer[4u] = 0x50;
    
   // CreateCommandPacketBuffer(cmd);

    (void) mI2C_I2CMasterClearStatus();
    
    /* Start I2C write and check status */
    if(mI2C_I2C_MSTR_NO_ERROR == mI2C_I2CMasterWriteBuf(I2C_SLAVE_ADDR,
                                                        buffer, BUFFER_SIZE,
                                                        mI2C_I2C_MODE_COMPLETE_XFER))
    {
        /* If I2C write started without errors, 
         * wait until I2C Master completes write transfer */
        while (0u == (mI2C_I2CMasterStatus() & mI2C_I2C_MSTAT_WR_CMPLT))
        {
        }
        
        /* Report transfer status */
        if (0u == (mI2C_I2CMasterStatus() & mI2C_I2C_MSTAT_ERR_XFER))
        {
            /* Check if all bytes were written */
            if (mI2C_I2CMasterGetWriteBufSize() == BUFFER_SIZE)
            {
                status = TRANSFER_CMPLT;
            }
        }
    }

    return (status);
}

/*******************************************************************************
* Function Name: ReadStatusPacket
********************************************************************************
* 
* Summary:
*  Master initiates the transfer to read status packet from the Slave.
*  The status of the transfer is returned. Uses high level API I2CMasterStatus()
*
* Parameters:
*  None
*
* Return:
*  Status of the transfer. There are two statuses
*  - TRANSFER_CMPLT: transfer completed successfully.
*  - TRANSFER_ERROR: an error occurred durring transfer.
*
*******************************************************************************/
uint32 ReadStatusPacket(void)
{
    uint32 status = TRANSFER_ERROR;
    
    (void) mI2C_I2CMasterClearStatus();
    
    if(mI2C_I2C_MSTR_NO_ERROR ==  mI2C_I2CMasterReadBuf(I2C_SLAVE_ADDR,
                                                        rd_Buffer, RD_BUFFER_SIZE,
                                                        mI2C_I2C_MODE_COMPLETE_XFER))
    {
        /* If I2C read started without errors, 
        / wait until master complete read transfer */
        while (0u == (mI2C_I2CMasterStatus() & mI2C_I2C_MSTAT_RD_CMPLT))
        { 
        }
        
        /* Display transfer status */
        if (0u == (mI2C_I2C_MSTAT_ERR_XFER & mI2C_I2CMasterStatus()))
        {
            /* Check packet structure is correct */
            if ((mI2C_I2CMasterGetReadBufSize() == RD_BUFFER_SIZE) &&
                (PACKET_SOP == rd_Buffer[RD_PACKET_SOP_POS]) &&
                (PACKET_EOP == rd_Buffer[RD_PACKET_EOP_POS]))
            {
                /* Check packet status */
                if (STS_CMD_DONE == rd_Buffer[RD_PACKET_STS_POS])
                {
                    status = TRANSFER_CMPLT;
                }
            }
        }
    }

    return (status);
}

/*******************************************************************************
* Function Name: main
********************************************************************************
* 
* Main function performs the following actions:
*   1. Initializes I2C Component.
*   2. Writes a command packet to the slave.
*   3. Reads back the status of the write from the slave.
*   4. Iterates through each command and loops back when the maximum number 
*      of commands is complete.
*
*******************************************************************************/
int main()
{
    uint8 command = COLOR_RED;
    
    CyGlobalIntEnable;
    
    /* Start the I2C Master */
    mI2C_Start();
    
    rd_Buffer[RD_PACKET_SOP_POS] = PACKET_SOP;
    rd_Buffer[RD_PACKET_EOP_POS] = PACKET_EOP;

    for(;;)
    {   
        
        /* Send packet with command to the slave */
        if (TRANSFER_CMPLT == WriteCommandPacket(command))
        {
            /* Read response packet from the slave */
            if (TRANSFER_CMPLT == ReadStatusPacket())
            {                
                /* Cycle through LED Colors */
                command++;
                if (command > COLOR_WHITE)
                {
                    command = COLOR_RED;
                }
            }
        }
 
        /* Delay before changing LED color */
        CyDelay(500u); 
    }
}

/* [] END OF FILE */
