/*******************************************************************************
* File Name: V1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_V1_H) /* Pins V1_H */
#define CY_PINS_V1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "V1_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} V1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   V1_Read(void);
void    V1_Write(uint8 value);
uint8   V1_ReadDataReg(void);
#if defined(V1__PC) || (CY_PSOC4_4200L) 
    void    V1_SetDriveMode(uint8 mode);
#endif
void    V1_SetInterruptMode(uint16 position, uint16 mode);
uint8   V1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void V1_Sleep(void); 
void V1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(V1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define V1_DRIVE_MODE_BITS        (3)
    #define V1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - V1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the V1_SetDriveMode() function.
         *  @{
         */
        #define V1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define V1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define V1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define V1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define V1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define V1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define V1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define V1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define V1_MASK               V1__MASK
#define V1_SHIFT              V1__SHIFT
#define V1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in V1_SetInterruptMode() function.
     *  @{
     */
        #define V1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define V1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define V1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define V1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(V1__SIO)
    #define V1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(V1__PC) && (CY_PSOC4_4200L)
    #define V1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define V1_USBIO_DISABLE              ((uint32)(~V1_USBIO_ENABLE))
    #define V1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define V1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define V1_USBIO_ENTER_SLEEP          ((uint32)((1u << V1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << V1_USBIO_SUSPEND_DEL_SHIFT)))
    #define V1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << V1_USBIO_SUSPEND_SHIFT)))
    #define V1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << V1_USBIO_SUSPEND_DEL_SHIFT)))
    #define V1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(V1__PC)
    /* Port Configuration */
    #define V1_PC                 (* (reg32 *) V1__PC)
#endif
/* Pin State */
#define V1_PS                     (* (reg32 *) V1__PS)
/* Data Register */
#define V1_DR                     (* (reg32 *) V1__DR)
/* Input Buffer Disable Override */
#define V1_INP_DIS                (* (reg32 *) V1__PC2)

/* Interrupt configuration Registers */
#define V1_INTCFG                 (* (reg32 *) V1__INTCFG)
#define V1_INTSTAT                (* (reg32 *) V1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define V1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(V1__SIO)
    #define V1_SIO_REG            (* (reg32 *) V1__SIO)
#endif /* (V1__SIO_CFG) */

/* USBIO registers */
#if !defined(V1__PC) && (CY_PSOC4_4200L)
    #define V1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define V1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define V1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define V1_DRIVE_MODE_SHIFT       (0x00u)
#define V1_DRIVE_MODE_MASK        (0x07u << V1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins V1_H */


/* [] END OF FILE */
