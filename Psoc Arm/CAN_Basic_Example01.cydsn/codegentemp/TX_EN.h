/*******************************************************************************
* File Name: TX_EN.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_TX_EN_H) /* Pins TX_EN_H */
#define CY_PINS_TX_EN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "TX_EN_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    TX_EN_Write(uint8 value) ;
void    TX_EN_SetDriveMode(uint8 mode) ;
uint8   TX_EN_ReadDataReg(void) ;
uint8   TX_EN_Read(void) ;
void    TX_EN_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   TX_EN_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the TX_EN_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define TX_EN_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define TX_EN_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define TX_EN_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define TX_EN_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define TX_EN_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define TX_EN_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define TX_EN_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define TX_EN_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define TX_EN_MASK               TX_EN__MASK
#define TX_EN_SHIFT              TX_EN__SHIFT
#define TX_EN_WIDTH              1u

/* Interrupt constants */
#if defined(TX_EN__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in TX_EN_SetInterruptMode() function.
     *  @{
     */
        #define TX_EN_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define TX_EN_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define TX_EN_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define TX_EN_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define TX_EN_INTR_MASK      (0x01u)
#endif /* (TX_EN__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TX_EN_PS                     (* (reg8 *) TX_EN__PS)
/* Data Register */
#define TX_EN_DR                     (* (reg8 *) TX_EN__DR)
/* Port Number */
#define TX_EN_PRT_NUM                (* (reg8 *) TX_EN__PRT) 
/* Connect to Analog Globals */                                                  
#define TX_EN_AG                     (* (reg8 *) TX_EN__AG)                       
/* Analog MUX bux enable */
#define TX_EN_AMUX                   (* (reg8 *) TX_EN__AMUX) 
/* Bidirectional Enable */                                                        
#define TX_EN_BIE                    (* (reg8 *) TX_EN__BIE)
/* Bit-mask for Aliased Register Access */
#define TX_EN_BIT_MASK               (* (reg8 *) TX_EN__BIT_MASK)
/* Bypass Enable */
#define TX_EN_BYP                    (* (reg8 *) TX_EN__BYP)
/* Port wide control signals */                                                   
#define TX_EN_CTL                    (* (reg8 *) TX_EN__CTL)
/* Drive Modes */
#define TX_EN_DM0                    (* (reg8 *) TX_EN__DM0) 
#define TX_EN_DM1                    (* (reg8 *) TX_EN__DM1)
#define TX_EN_DM2                    (* (reg8 *) TX_EN__DM2) 
/* Input Buffer Disable Override */
#define TX_EN_INP_DIS                (* (reg8 *) TX_EN__INP_DIS)
/* LCD Common or Segment Drive */
#define TX_EN_LCD_COM_SEG            (* (reg8 *) TX_EN__LCD_COM_SEG)
/* Enable Segment LCD */
#define TX_EN_LCD_EN                 (* (reg8 *) TX_EN__LCD_EN)
/* Slew Rate Control */
#define TX_EN_SLW                    (* (reg8 *) TX_EN__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define TX_EN_PRTDSI__CAPS_SEL       (* (reg8 *) TX_EN__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define TX_EN_PRTDSI__DBL_SYNC_IN    (* (reg8 *) TX_EN__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define TX_EN_PRTDSI__OE_SEL0        (* (reg8 *) TX_EN__PRTDSI__OE_SEL0) 
#define TX_EN_PRTDSI__OE_SEL1        (* (reg8 *) TX_EN__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define TX_EN_PRTDSI__OUT_SEL0       (* (reg8 *) TX_EN__PRTDSI__OUT_SEL0) 
#define TX_EN_PRTDSI__OUT_SEL1       (* (reg8 *) TX_EN__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define TX_EN_PRTDSI__SYNC_OUT       (* (reg8 *) TX_EN__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(TX_EN__SIO_CFG)
    #define TX_EN_SIO_HYST_EN        (* (reg8 *) TX_EN__SIO_HYST_EN)
    #define TX_EN_SIO_REG_HIFREQ     (* (reg8 *) TX_EN__SIO_REG_HIFREQ)
    #define TX_EN_SIO_CFG            (* (reg8 *) TX_EN__SIO_CFG)
    #define TX_EN_SIO_DIFF           (* (reg8 *) TX_EN__SIO_DIFF)
#endif /* (TX_EN__SIO_CFG) */

/* Interrupt Registers */
#if defined(TX_EN__INTSTAT)
    #define TX_EN_INTSTAT             (* (reg8 *) TX_EN__INTSTAT)
    #define TX_EN_SNAP                (* (reg8 *) TX_EN__SNAP)
    
	#define TX_EN_0_INTTYPE_REG 		(* (reg8 *) TX_EN__0__INTTYPE)
#endif /* (TX_EN__INTSTAT) */

#endif /* End Pins TX_EN_H */


/* [] END OF FILE */
