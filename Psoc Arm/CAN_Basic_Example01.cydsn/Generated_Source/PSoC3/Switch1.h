/*******************************************************************************
* File Name: Switch1.h  
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

#if !defined(CY_PINS_Switch1_H) /* Pins Switch1_H */
#define CY_PINS_Switch1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Switch1_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Switch1_Write(uint8 value) ;
void    Switch1_SetDriveMode(uint8 mode) ;
uint8   Switch1_ReadDataReg(void) ;
uint8   Switch1_Read(void) ;
void    Switch1_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   Switch1_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Switch1_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define Switch1_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define Switch1_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define Switch1_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define Switch1_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define Switch1_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define Switch1_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define Switch1_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define Switch1_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Switch1_MASK               Switch1__MASK
#define Switch1_SHIFT              Switch1__SHIFT
#define Switch1_WIDTH              1u

/* Interrupt constants */
#if defined(Switch1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Switch1_SetInterruptMode() function.
     *  @{
     */
        #define Switch1_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define Switch1_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define Switch1_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define Switch1_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define Switch1_INTR_MASK      (0x01u)
#endif /* (Switch1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Switch1_PS                     (* (reg8 *) Switch1__PS)
/* Data Register */
#define Switch1_DR                     (* (reg8 *) Switch1__DR)
/* Port Number */
#define Switch1_PRT_NUM                (* (reg8 *) Switch1__PRT) 
/* Connect to Analog Globals */                                                  
#define Switch1_AG                     (* (reg8 *) Switch1__AG)                       
/* Analog MUX bux enable */
#define Switch1_AMUX                   (* (reg8 *) Switch1__AMUX) 
/* Bidirectional Enable */                                                        
#define Switch1_BIE                    (* (reg8 *) Switch1__BIE)
/* Bit-mask for Aliased Register Access */
#define Switch1_BIT_MASK               (* (reg8 *) Switch1__BIT_MASK)
/* Bypass Enable */
#define Switch1_BYP                    (* (reg8 *) Switch1__BYP)
/* Port wide control signals */                                                   
#define Switch1_CTL                    (* (reg8 *) Switch1__CTL)
/* Drive Modes */
#define Switch1_DM0                    (* (reg8 *) Switch1__DM0) 
#define Switch1_DM1                    (* (reg8 *) Switch1__DM1)
#define Switch1_DM2                    (* (reg8 *) Switch1__DM2) 
/* Input Buffer Disable Override */
#define Switch1_INP_DIS                (* (reg8 *) Switch1__INP_DIS)
/* LCD Common or Segment Drive */
#define Switch1_LCD_COM_SEG            (* (reg8 *) Switch1__LCD_COM_SEG)
/* Enable Segment LCD */
#define Switch1_LCD_EN                 (* (reg8 *) Switch1__LCD_EN)
/* Slew Rate Control */
#define Switch1_SLW                    (* (reg8 *) Switch1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Switch1_PRTDSI__CAPS_SEL       (* (reg8 *) Switch1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Switch1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Switch1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Switch1_PRTDSI__OE_SEL0        (* (reg8 *) Switch1__PRTDSI__OE_SEL0) 
#define Switch1_PRTDSI__OE_SEL1        (* (reg8 *) Switch1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Switch1_PRTDSI__OUT_SEL0       (* (reg8 *) Switch1__PRTDSI__OUT_SEL0) 
#define Switch1_PRTDSI__OUT_SEL1       (* (reg8 *) Switch1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Switch1_PRTDSI__SYNC_OUT       (* (reg8 *) Switch1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Switch1__SIO_CFG)
    #define Switch1_SIO_HYST_EN        (* (reg8 *) Switch1__SIO_HYST_EN)
    #define Switch1_SIO_REG_HIFREQ     (* (reg8 *) Switch1__SIO_REG_HIFREQ)
    #define Switch1_SIO_CFG            (* (reg8 *) Switch1__SIO_CFG)
    #define Switch1_SIO_DIFF           (* (reg8 *) Switch1__SIO_DIFF)
#endif /* (Switch1__SIO_CFG) */

/* Interrupt Registers */
#if defined(Switch1__INTSTAT)
    #define Switch1_INTSTAT             (* (reg8 *) Switch1__INTSTAT)
    #define Switch1_SNAP                (* (reg8 *) Switch1__SNAP)
    
	#define Switch1_0_INTTYPE_REG 		(* (reg8 *) Switch1__0__INTTYPE)
#endif /* (Switch1__INTSTAT) */

#endif /* End Pins Switch1_H */


/* [] END OF FILE */
