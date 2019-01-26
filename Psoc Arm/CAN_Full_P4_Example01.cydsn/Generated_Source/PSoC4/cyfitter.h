/*******************************************************************************
* File Name: cyfitter.h
* 
* PSoC Creator  4.2
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice_trm.h"

/* RX */
#define RX__0__DR CYREG_GPIO_PRT0_DR
#define RX__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define RX__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define RX__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define RX__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define RX__0__HSIOM_MASK 0x0000000Fu
#define RX__0__HSIOM_SHIFT 0u
#define RX__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define RX__0__INTR CYREG_GPIO_PRT0_INTR
#define RX__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define RX__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define RX__0__MASK 0x01u
#define RX__0__PA__CFG0 CYREG_UDB_PA4_CFG0
#define RX__0__PA__CFG1 CYREG_UDB_PA4_CFG1
#define RX__0__PA__CFG10 CYREG_UDB_PA4_CFG10
#define RX__0__PA__CFG11 CYREG_UDB_PA4_CFG11
#define RX__0__PA__CFG12 CYREG_UDB_PA4_CFG12
#define RX__0__PA__CFG13 CYREG_UDB_PA4_CFG13
#define RX__0__PA__CFG14 CYREG_UDB_PA4_CFG14
#define RX__0__PA__CFG2 CYREG_UDB_PA4_CFG2
#define RX__0__PA__CFG3 CYREG_UDB_PA4_CFG3
#define RX__0__PA__CFG4 CYREG_UDB_PA4_CFG4
#define RX__0__PA__CFG5 CYREG_UDB_PA4_CFG5
#define RX__0__PA__CFG6 CYREG_UDB_PA4_CFG6
#define RX__0__PA__CFG7 CYREG_UDB_PA4_CFG7
#define RX__0__PA__CFG8 CYREG_UDB_PA4_CFG8
#define RX__0__PA__CFG9 CYREG_UDB_PA4_CFG9
#define RX__0__PC CYREG_GPIO_PRT0_PC
#define RX__0__PC2 CYREG_GPIO_PRT0_PC2
#define RX__0__PORT 0u
#define RX__0__PS CYREG_GPIO_PRT0_PS
#define RX__0__SHIFT 0u
#define RX__DR CYREG_GPIO_PRT0_DR
#define RX__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define RX__DR_INV CYREG_GPIO_PRT0_DR_INV
#define RX__DR_SET CYREG_GPIO_PRT0_DR_SET
#define RX__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define RX__INTR CYREG_GPIO_PRT0_INTR
#define RX__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define RX__INTSTAT CYREG_GPIO_PRT0_INTR
#define RX__MASK 0x01u
#define RX__PA__CFG0 CYREG_UDB_PA4_CFG0
#define RX__PA__CFG1 CYREG_UDB_PA4_CFG1
#define RX__PA__CFG10 CYREG_UDB_PA4_CFG10
#define RX__PA__CFG11 CYREG_UDB_PA4_CFG11
#define RX__PA__CFG12 CYREG_UDB_PA4_CFG12
#define RX__PA__CFG13 CYREG_UDB_PA4_CFG13
#define RX__PA__CFG14 CYREG_UDB_PA4_CFG14
#define RX__PA__CFG2 CYREG_UDB_PA4_CFG2
#define RX__PA__CFG3 CYREG_UDB_PA4_CFG3
#define RX__PA__CFG4 CYREG_UDB_PA4_CFG4
#define RX__PA__CFG5 CYREG_UDB_PA4_CFG5
#define RX__PA__CFG6 CYREG_UDB_PA4_CFG6
#define RX__PA__CFG7 CYREG_UDB_PA4_CFG7
#define RX__PA__CFG8 CYREG_UDB_PA4_CFG8
#define RX__PA__CFG9 CYREG_UDB_PA4_CFG9
#define RX__PC CYREG_GPIO_PRT0_PC
#define RX__PC2 CYREG_GPIO_PRT0_PC2
#define RX__PORT 0u
#define RX__PS CYREG_GPIO_PRT0_PS
#define RX__SHIFT 0u

/* TX */
#define TX__0__DR CYREG_GPIO_PRT0_DR
#define TX__0__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define TX__0__DR_INV CYREG_GPIO_PRT0_DR_INV
#define TX__0__DR_SET CYREG_GPIO_PRT0_DR_SET
#define TX__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define TX__0__HSIOM_MASK 0x000000F0u
#define TX__0__HSIOM_SHIFT 4u
#define TX__0__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define TX__0__INTR CYREG_GPIO_PRT0_INTR
#define TX__0__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define TX__0__INTSTAT CYREG_GPIO_PRT0_INTR
#define TX__0__MASK 0x02u
#define TX__0__OUT_SEL CYREG_UDB_PA4_CFG10
#define TX__0__OUT_SEL_SHIFT 2u
#define TX__0__OUT_SEL_VAL -1u
#define TX__0__PA__CFG0 CYREG_UDB_PA4_CFG0
#define TX__0__PA__CFG1 CYREG_UDB_PA4_CFG1
#define TX__0__PA__CFG10 CYREG_UDB_PA4_CFG10
#define TX__0__PA__CFG11 CYREG_UDB_PA4_CFG11
#define TX__0__PA__CFG12 CYREG_UDB_PA4_CFG12
#define TX__0__PA__CFG13 CYREG_UDB_PA4_CFG13
#define TX__0__PA__CFG14 CYREG_UDB_PA4_CFG14
#define TX__0__PA__CFG2 CYREG_UDB_PA4_CFG2
#define TX__0__PA__CFG3 CYREG_UDB_PA4_CFG3
#define TX__0__PA__CFG4 CYREG_UDB_PA4_CFG4
#define TX__0__PA__CFG5 CYREG_UDB_PA4_CFG5
#define TX__0__PA__CFG6 CYREG_UDB_PA4_CFG6
#define TX__0__PA__CFG7 CYREG_UDB_PA4_CFG7
#define TX__0__PA__CFG8 CYREG_UDB_PA4_CFG8
#define TX__0__PA__CFG9 CYREG_UDB_PA4_CFG9
#define TX__0__PC CYREG_GPIO_PRT0_PC
#define TX__0__PC2 CYREG_GPIO_PRT0_PC2
#define TX__0__PORT 0u
#define TX__0__PS CYREG_GPIO_PRT0_PS
#define TX__0__SHIFT 1u
#define TX__DR CYREG_GPIO_PRT0_DR
#define TX__DR_CLR CYREG_GPIO_PRT0_DR_CLR
#define TX__DR_INV CYREG_GPIO_PRT0_DR_INV
#define TX__DR_SET CYREG_GPIO_PRT0_DR_SET
#define TX__INTCFG CYREG_GPIO_PRT0_INTR_CFG
#define TX__INTR CYREG_GPIO_PRT0_INTR
#define TX__INTR_CFG CYREG_GPIO_PRT0_INTR_CFG
#define TX__INTSTAT CYREG_GPIO_PRT0_INTR
#define TX__MASK 0x02u
#define TX__PA__CFG0 CYREG_UDB_PA4_CFG0
#define TX__PA__CFG1 CYREG_UDB_PA4_CFG1
#define TX__PA__CFG10 CYREG_UDB_PA4_CFG10
#define TX__PA__CFG11 CYREG_UDB_PA4_CFG11
#define TX__PA__CFG12 CYREG_UDB_PA4_CFG12
#define TX__PA__CFG13 CYREG_UDB_PA4_CFG13
#define TX__PA__CFG14 CYREG_UDB_PA4_CFG14
#define TX__PA__CFG2 CYREG_UDB_PA4_CFG2
#define TX__PA__CFG3 CYREG_UDB_PA4_CFG3
#define TX__PA__CFG4 CYREG_UDB_PA4_CFG4
#define TX__PA__CFG5 CYREG_UDB_PA4_CFG5
#define TX__PA__CFG6 CYREG_UDB_PA4_CFG6
#define TX__PA__CFG7 CYREG_UDB_PA4_CFG7
#define TX__PA__CFG8 CYREG_UDB_PA4_CFG8
#define TX__PA__CFG9 CYREG_UDB_PA4_CFG9
#define TX__PC CYREG_GPIO_PRT0_PC
#define TX__PC2 CYREG_GPIO_PRT0_PC2
#define TX__PORT 0u
#define TX__PS CYREG_GPIO_PRT0_PS
#define TX__SHIFT 1u

/* CAN */
#define CAN_CanIP__BUFFER_STATUS CYREG_CAN1_BUFFER_STATUS
#define CAN_CanIP__CAN_RX0_ACR CYREG_CAN1_CAN_RX0_ACR
#define CAN_CanIP__CAN_RX0_ACR_DATA CYREG_CAN1_CAN_RX0_ACR_DATA
#define CAN_CanIP__CAN_RX0_AMR CYREG_CAN1_CAN_RX0_AMR
#define CAN_CanIP__CAN_RX0_AMR_DATA CYREG_CAN1_CAN_RX0_AMR_DATA
#define CAN_CanIP__CAN_RX0_CONTROL CYREG_CAN1_CAN_RX0_CONTROL
#define CAN_CanIP__CAN_RX0_DATA_HIGH CYREG_CAN1_CAN_RX0_DATA_HIGH
#define CAN_CanIP__CAN_RX0_DATA_LOW CYREG_CAN1_CAN_RX0_DATA_LOW
#define CAN_CanIP__CAN_RX0_ID CYREG_CAN1_CAN_RX0_ID
#define CAN_CanIP__CAN_RX1_ACR CYREG_CAN1_CAN_RX1_ACR
#define CAN_CanIP__CAN_RX1_ACR_DATA CYREG_CAN1_CAN_RX1_ACR_DATA
#define CAN_CanIP__CAN_RX1_AMR CYREG_CAN1_CAN_RX1_AMR
#define CAN_CanIP__CAN_RX1_AMR_DATA CYREG_CAN1_CAN_RX1_AMR_DATA
#define CAN_CanIP__CAN_RX1_CONTROL CYREG_CAN1_CAN_RX1_CONTROL
#define CAN_CanIP__CAN_RX1_DATA_HIGH CYREG_CAN1_CAN_RX1_DATA_HIGH
#define CAN_CanIP__CAN_RX1_DATA_LOW CYREG_CAN1_CAN_RX1_DATA_LOW
#define CAN_CanIP__CAN_RX1_ID CYREG_CAN1_CAN_RX1_ID
#define CAN_CanIP__CAN_RX10_ACR CYREG_CAN1_CAN_RX10_ACR
#define CAN_CanIP__CAN_RX10_ACR_DATA CYREG_CAN1_CAN_RX10_ACR_DATA
#define CAN_CanIP__CAN_RX10_AMR CYREG_CAN1_CAN_RX10_AMR
#define CAN_CanIP__CAN_RX10_AMR_DATA CYREG_CAN1_CAN_RX10_AMR_DATA
#define CAN_CanIP__CAN_RX10_CONTROL CYREG_CAN1_CAN_RX10_CONTROL
#define CAN_CanIP__CAN_RX10_DATA_HIGH CYREG_CAN1_CAN_RX10_DATA_HIGH
#define CAN_CanIP__CAN_RX10_DATA_LOW CYREG_CAN1_CAN_RX10_DATA_LOW
#define CAN_CanIP__CAN_RX10_ID CYREG_CAN1_CAN_RX10_ID
#define CAN_CanIP__CAN_RX11_ACR CYREG_CAN1_CAN_RX11_ACR
#define CAN_CanIP__CAN_RX11_ACR_DATA CYREG_CAN1_CAN_RX11_ACR_DATA
#define CAN_CanIP__CAN_RX11_AMR CYREG_CAN1_CAN_RX11_AMR
#define CAN_CanIP__CAN_RX11_AMR_DATA CYREG_CAN1_CAN_RX11_AMR_DATA
#define CAN_CanIP__CAN_RX11_CONTROL CYREG_CAN1_CAN_RX11_CONTROL
#define CAN_CanIP__CAN_RX11_DATA_HIGH CYREG_CAN1_CAN_RX11_DATA_HIGH
#define CAN_CanIP__CAN_RX11_DATA_LOW CYREG_CAN1_CAN_RX11_DATA_LOW
#define CAN_CanIP__CAN_RX11_ID CYREG_CAN1_CAN_RX11_ID
#define CAN_CanIP__CAN_RX12_ACR CYREG_CAN1_CAN_RX12_ACR
#define CAN_CanIP__CAN_RX12_ACR_DATA CYREG_CAN1_CAN_RX12_ACR_DATA
#define CAN_CanIP__CAN_RX12_AMR CYREG_CAN1_CAN_RX12_AMR
#define CAN_CanIP__CAN_RX12_AMR_DATA CYREG_CAN1_CAN_RX12_AMR_DATA
#define CAN_CanIP__CAN_RX12_CONTROL CYREG_CAN1_CAN_RX12_CONTROL
#define CAN_CanIP__CAN_RX12_DATA_HIGH CYREG_CAN1_CAN_RX12_DATA_HIGH
#define CAN_CanIP__CAN_RX12_DATA_LOW CYREG_CAN1_CAN_RX12_DATA_LOW
#define CAN_CanIP__CAN_RX12_ID CYREG_CAN1_CAN_RX12_ID
#define CAN_CanIP__CAN_RX13_ACR CYREG_CAN1_CAN_RX13_ACR
#define CAN_CanIP__CAN_RX13_ACR_DATA CYREG_CAN1_CAN_RX13_ACR_DATA
#define CAN_CanIP__CAN_RX13_AMR CYREG_CAN1_CAN_RX13_AMR
#define CAN_CanIP__CAN_RX13_AMR_DATA CYREG_CAN1_CAN_RX13_AMR_DATA
#define CAN_CanIP__CAN_RX13_CONTROL CYREG_CAN1_CAN_RX13_CONTROL
#define CAN_CanIP__CAN_RX13_DATA_HIGH CYREG_CAN1_CAN_RX13_DATA_HIGH
#define CAN_CanIP__CAN_RX13_DATA_LOW CYREG_CAN1_CAN_RX13_DATA_LOW
#define CAN_CanIP__CAN_RX13_ID CYREG_CAN1_CAN_RX13_ID
#define CAN_CanIP__CAN_RX14_ACR CYREG_CAN1_CAN_RX14_ACR
#define CAN_CanIP__CAN_RX14_ACR_DATA CYREG_CAN1_CAN_RX14_ACR_DATA
#define CAN_CanIP__CAN_RX14_AMR CYREG_CAN1_CAN_RX14_AMR
#define CAN_CanIP__CAN_RX14_AMR_DATA CYREG_CAN1_CAN_RX14_AMR_DATA
#define CAN_CanIP__CAN_RX14_CONTROL CYREG_CAN1_CAN_RX14_CONTROL
#define CAN_CanIP__CAN_RX14_DATA_HIGH CYREG_CAN1_CAN_RX14_DATA_HIGH
#define CAN_CanIP__CAN_RX14_DATA_LOW CYREG_CAN1_CAN_RX14_DATA_LOW
#define CAN_CanIP__CAN_RX14_ID CYREG_CAN1_CAN_RX14_ID
#define CAN_CanIP__CAN_RX15_ACR CYREG_CAN1_CAN_RX15_ACR
#define CAN_CanIP__CAN_RX15_ACR_DATA CYREG_CAN1_CAN_RX15_ACR_DATA
#define CAN_CanIP__CAN_RX15_AMR CYREG_CAN1_CAN_RX15_AMR
#define CAN_CanIP__CAN_RX15_AMR_DATA CYREG_CAN1_CAN_RX15_AMR_DATA
#define CAN_CanIP__CAN_RX15_CONTROL CYREG_CAN1_CAN_RX15_CONTROL
#define CAN_CanIP__CAN_RX15_DATA_HIGH CYREG_CAN1_CAN_RX15_DATA_HIGH
#define CAN_CanIP__CAN_RX15_DATA_LOW CYREG_CAN1_CAN_RX15_DATA_LOW
#define CAN_CanIP__CAN_RX15_ID CYREG_CAN1_CAN_RX15_ID
#define CAN_CanIP__CAN_RX2_ACR CYREG_CAN1_CAN_RX2_ACR
#define CAN_CanIP__CAN_RX2_ACR_DATA CYREG_CAN1_CAN_RX2_ACR_DATA
#define CAN_CanIP__CAN_RX2_AMR CYREG_CAN1_CAN_RX2_AMR
#define CAN_CanIP__CAN_RX2_AMR_DATA CYREG_CAN1_CAN_RX2_AMR_DATA
#define CAN_CanIP__CAN_RX2_CONTROL CYREG_CAN1_CAN_RX2_CONTROL
#define CAN_CanIP__CAN_RX2_DATA_HIGH CYREG_CAN1_CAN_RX2_DATA_HIGH
#define CAN_CanIP__CAN_RX2_DATA_LOW CYREG_CAN1_CAN_RX2_DATA_LOW
#define CAN_CanIP__CAN_RX2_ID CYREG_CAN1_CAN_RX2_ID
#define CAN_CanIP__CAN_RX3_ACR CYREG_CAN1_CAN_RX3_ACR
#define CAN_CanIP__CAN_RX3_ACR_DATA CYREG_CAN1_CAN_RX3_ACR_DATA
#define CAN_CanIP__CAN_RX3_AMR CYREG_CAN1_CAN_RX3_AMR
#define CAN_CanIP__CAN_RX3_AMR_DATA CYREG_CAN1_CAN_RX3_AMR_DATA
#define CAN_CanIP__CAN_RX3_CONTROL CYREG_CAN1_CAN_RX3_CONTROL
#define CAN_CanIP__CAN_RX3_DATA_HIGH CYREG_CAN1_CAN_RX3_DATA_HIGH
#define CAN_CanIP__CAN_RX3_DATA_LOW CYREG_CAN1_CAN_RX3_DATA_LOW
#define CAN_CanIP__CAN_RX3_ID CYREG_CAN1_CAN_RX3_ID
#define CAN_CanIP__CAN_RX4_ACR CYREG_CAN1_CAN_RX4_ACR
#define CAN_CanIP__CAN_RX4_ACR_DATA CYREG_CAN1_CAN_RX4_ACR_DATA
#define CAN_CanIP__CAN_RX4_AMR CYREG_CAN1_CAN_RX4_AMR
#define CAN_CanIP__CAN_RX4_AMR_DATA CYREG_CAN1_CAN_RX4_AMR_DATA
#define CAN_CanIP__CAN_RX4_CONTROL CYREG_CAN1_CAN_RX4_CONTROL
#define CAN_CanIP__CAN_RX4_DATA_HIGH CYREG_CAN1_CAN_RX4_DATA_HIGH
#define CAN_CanIP__CAN_RX4_DATA_LOW CYREG_CAN1_CAN_RX4_DATA_LOW
#define CAN_CanIP__CAN_RX4_ID CYREG_CAN1_CAN_RX4_ID
#define CAN_CanIP__CAN_RX5_ACR CYREG_CAN1_CAN_RX5_ACR
#define CAN_CanIP__CAN_RX5_ACR_DATA CYREG_CAN1_CAN_RX5_ACR_DATA
#define CAN_CanIP__CAN_RX5_AMR CYREG_CAN1_CAN_RX5_AMR
#define CAN_CanIP__CAN_RX5_AMR_DATA CYREG_CAN1_CAN_RX5_AMR_DATA
#define CAN_CanIP__CAN_RX5_CONTROL CYREG_CAN1_CAN_RX5_CONTROL
#define CAN_CanIP__CAN_RX5_DATA_HIGH CYREG_CAN1_CAN_RX5_DATA_HIGH
#define CAN_CanIP__CAN_RX5_DATA_LOW CYREG_CAN1_CAN_RX5_DATA_LOW
#define CAN_CanIP__CAN_RX5_ID CYREG_CAN1_CAN_RX5_ID
#define CAN_CanIP__CAN_RX6_ACR CYREG_CAN1_CAN_RX6_ACR
#define CAN_CanIP__CAN_RX6_ACR_DATA CYREG_CAN1_CAN_RX6_ACR_DATA
#define CAN_CanIP__CAN_RX6_AMR CYREG_CAN1_CAN_RX6_AMR
#define CAN_CanIP__CAN_RX6_AMR_DATA CYREG_CAN1_CAN_RX6_AMR_DATA
#define CAN_CanIP__CAN_RX6_CONTROL CYREG_CAN1_CAN_RX6_CONTROL
#define CAN_CanIP__CAN_RX6_DATA_HIGH CYREG_CAN1_CAN_RX6_DATA_HIGH
#define CAN_CanIP__CAN_RX6_DATA_LOW CYREG_CAN1_CAN_RX6_DATA_LOW
#define CAN_CanIP__CAN_RX6_ID CYREG_CAN1_CAN_RX6_ID
#define CAN_CanIP__CAN_RX7_ACR CYREG_CAN1_CAN_RX7_ACR
#define CAN_CanIP__CAN_RX7_ACR_DATA CYREG_CAN1_CAN_RX7_ACR_DATA
#define CAN_CanIP__CAN_RX7_AMR CYREG_CAN1_CAN_RX7_AMR
#define CAN_CanIP__CAN_RX7_AMR_DATA CYREG_CAN1_CAN_RX7_AMR_DATA
#define CAN_CanIP__CAN_RX7_CONTROL CYREG_CAN1_CAN_RX7_CONTROL
#define CAN_CanIP__CAN_RX7_DATA_HIGH CYREG_CAN1_CAN_RX7_DATA_HIGH
#define CAN_CanIP__CAN_RX7_DATA_LOW CYREG_CAN1_CAN_RX7_DATA_LOW
#define CAN_CanIP__CAN_RX7_ID CYREG_CAN1_CAN_RX7_ID
#define CAN_CanIP__CAN_RX8_ACR CYREG_CAN1_CAN_RX8_ACR
#define CAN_CanIP__CAN_RX8_ACR_DATA CYREG_CAN1_CAN_RX8_ACR_DATA
#define CAN_CanIP__CAN_RX8_AMR CYREG_CAN1_CAN_RX8_AMR
#define CAN_CanIP__CAN_RX8_AMR_DATA CYREG_CAN1_CAN_RX8_AMR_DATA
#define CAN_CanIP__CAN_RX8_CONTROL CYREG_CAN1_CAN_RX8_CONTROL
#define CAN_CanIP__CAN_RX8_DATA_HIGH CYREG_CAN1_CAN_RX8_DATA_HIGH
#define CAN_CanIP__CAN_RX8_DATA_LOW CYREG_CAN1_CAN_RX8_DATA_LOW
#define CAN_CanIP__CAN_RX8_ID CYREG_CAN1_CAN_RX8_ID
#define CAN_CanIP__CAN_RX9_ACR CYREG_CAN1_CAN_RX9_ACR
#define CAN_CanIP__CAN_RX9_ACR_DATA CYREG_CAN1_CAN_RX9_ACR_DATA
#define CAN_CanIP__CAN_RX9_AMR CYREG_CAN1_CAN_RX9_AMR
#define CAN_CanIP__CAN_RX9_AMR_DATA CYREG_CAN1_CAN_RX9_AMR_DATA
#define CAN_CanIP__CAN_RX9_CONTROL CYREG_CAN1_CAN_RX9_CONTROL
#define CAN_CanIP__CAN_RX9_DATA_HIGH CYREG_CAN1_CAN_RX9_DATA_HIGH
#define CAN_CanIP__CAN_RX9_DATA_LOW CYREG_CAN1_CAN_RX9_DATA_LOW
#define CAN_CanIP__CAN_RX9_ID CYREG_CAN1_CAN_RX9_ID
#define CAN_CanIP__CAN_TX0_CONTROL CYREG_CAN1_CAN_TX0_CONTROL
#define CAN_CanIP__CAN_TX0_DATA_HIGH CYREG_CAN1_CAN_TX0_DATA_HIGH
#define CAN_CanIP__CAN_TX0_DATA_LOW CYREG_CAN1_CAN_TX0_DATA_LOW
#define CAN_CanIP__CAN_TX0_ID CYREG_CAN1_CAN_TX0_ID
#define CAN_CanIP__CAN_TX1_CONTROL CYREG_CAN1_CAN_TX1_CONTROL
#define CAN_CanIP__CAN_TX1_DATA_HIGH CYREG_CAN1_CAN_TX1_DATA_HIGH
#define CAN_CanIP__CAN_TX1_DATA_LOW CYREG_CAN1_CAN_TX1_DATA_LOW
#define CAN_CanIP__CAN_TX1_ID CYREG_CAN1_CAN_TX1_ID
#define CAN_CanIP__CAN_TX2_CONTROL CYREG_CAN1_CAN_TX2_CONTROL
#define CAN_CanIP__CAN_TX2_DATA_HIGH CYREG_CAN1_CAN_TX2_DATA_HIGH
#define CAN_CanIP__CAN_TX2_DATA_LOW CYREG_CAN1_CAN_TX2_DATA_LOW
#define CAN_CanIP__CAN_TX2_ID CYREG_CAN1_CAN_TX2_ID
#define CAN_CanIP__CAN_TX3_CONTROL CYREG_CAN1_CAN_TX3_CONTROL
#define CAN_CanIP__CAN_TX3_DATA_HIGH CYREG_CAN1_CAN_TX3_DATA_HIGH
#define CAN_CanIP__CAN_TX3_DATA_LOW CYREG_CAN1_CAN_TX3_DATA_LOW
#define CAN_CanIP__CAN_TX3_ID CYREG_CAN1_CAN_TX3_ID
#define CAN_CanIP__CAN_TX4_CONTROL CYREG_CAN1_CAN_TX4_CONTROL
#define CAN_CanIP__CAN_TX4_DATA_HIGH CYREG_CAN1_CAN_TX4_DATA_HIGH
#define CAN_CanIP__CAN_TX4_DATA_LOW CYREG_CAN1_CAN_TX4_DATA_LOW
#define CAN_CanIP__CAN_TX4_ID CYREG_CAN1_CAN_TX4_ID
#define CAN_CanIP__CAN_TX5_CONTROL CYREG_CAN1_CAN_TX5_CONTROL
#define CAN_CanIP__CAN_TX5_DATA_HIGH CYREG_CAN1_CAN_TX5_DATA_HIGH
#define CAN_CanIP__CAN_TX5_DATA_LOW CYREG_CAN1_CAN_TX5_DATA_LOW
#define CAN_CanIP__CAN_TX5_ID CYREG_CAN1_CAN_TX5_ID
#define CAN_CanIP__CAN_TX6_CONTROL CYREG_CAN1_CAN_TX6_CONTROL
#define CAN_CanIP__CAN_TX6_DATA_HIGH CYREG_CAN1_CAN_TX6_DATA_HIGH
#define CAN_CanIP__CAN_TX6_DATA_LOW CYREG_CAN1_CAN_TX6_DATA_LOW
#define CAN_CanIP__CAN_TX6_ID CYREG_CAN1_CAN_TX6_ID
#define CAN_CanIP__CAN_TX7_CONTROL CYREG_CAN1_CAN_TX7_CONTROL
#define CAN_CanIP__CAN_TX7_DATA_HIGH CYREG_CAN1_CAN_TX7_DATA_HIGH
#define CAN_CanIP__CAN_TX7_DATA_LOW CYREG_CAN1_CAN_TX7_DATA_LOW
#define CAN_CanIP__CAN_TX7_ID CYREG_CAN1_CAN_TX7_ID
#define CAN_CanIP__CNTL CYREG_CAN1_CNTL
#define CAN_CanIP__COMMAND CYREG_CAN1_COMMAND
#define CAN_CanIP__CONFIG CYREG_CAN1_CONFIG
#define CAN_CanIP__ECR CYREG_CAN1_ECR
#define CAN_CanIP__ERROR_STATUS CYREG_CAN1_ERROR_STATUS
#define CAN_CanIP__INT_EBL CYREG_CAN1_INT_EBL
#define CAN_CanIP__INT_STATUS CYREG_CAN1_INT_STATUS
#define CAN_CanIP__INTR_CAN CYREG_CAN1_INTR_CAN
#define CAN_CanIP__INTR_CAN_MASK CYREG_CAN1_INTR_CAN_MASK
#define CAN_CanIP__INTR_CAN_MASKED CYREG_CAN1_INTR_CAN_MASKED
#define CAN_CanIP__INTR_CAN_SET CYREG_CAN1_INTR_CAN_SET
#define CAN_CanIP__TTCAN_CAPTURE CYREG_CAN1_TTCAN_CAPTURE
#define CAN_CanIP__TTCAN_COMPARE CYREG_CAN1_TTCAN_COMPARE
#define CAN_CanIP__TTCAN_COUNTER CYREG_CAN1_TTCAN_COUNTER
#define CAN_CanIP__TTCAN_TIMING CYREG_CAN1_TTCAN_TIMING
#define CAN_HFCLK__DIV_ID 0x00000040u
#define CAN_HFCLK__DIV_REGISTER CYREG_PERI_DIV_16_CTL0
#define CAN_HFCLK__PA_DIV_ID 0x000000FFu
#define CAN_isr__INTC_CLR_EN_REG CYREG_CM0_ICER
#define CAN_isr__INTC_CLR_PD_REG CYREG_CM0_ICPR
#define CAN_isr__INTC_MASK 0x20000000u
#define CAN_isr__INTC_NUMBER 29u
#define CAN_isr__INTC_PRIOR_MASK 0xC000u
#define CAN_isr__INTC_PRIOR_NUM 3u
#define CAN_isr__INTC_PRIOR_REG CYREG_CM0_IPR7
#define CAN_isr__INTC_SET_EN_REG CYREG_CM0_ISER
#define CAN_isr__INTC_SET_PD_REG CYREG_CM0_ISPR

/* UART */
#define UART_rx__0__DR CYREG_GPIO_PRT3_DR
#define UART_rx__0__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define UART_rx__0__DR_INV CYREG_GPIO_PRT3_DR_INV
#define UART_rx__0__DR_SET CYREG_GPIO_PRT3_DR_SET
#define UART_rx__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define UART_rx__0__HSIOM_GPIO 0u
#define UART_rx__0__HSIOM_I2C 14u
#define UART_rx__0__HSIOM_I2C_SCL 14u
#define UART_rx__0__HSIOM_MASK 0x0000000Fu
#define UART_rx__0__HSIOM_SHIFT 0u
#define UART_rx__0__HSIOM_SPI 15u
#define UART_rx__0__HSIOM_SPI_MOSI 15u
#define UART_rx__0__HSIOM_UART 9u
#define UART_rx__0__HSIOM_UART_RX 9u
#define UART_rx__0__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_rx__0__INTR CYREG_GPIO_PRT3_INTR
#define UART_rx__0__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_rx__0__INTSTAT CYREG_GPIO_PRT3_INTR
#define UART_rx__0__MASK 0x01u
#define UART_rx__0__PA__CFG0 CYREG_UDB_PA7_CFG0
#define UART_rx__0__PA__CFG1 CYREG_UDB_PA7_CFG1
#define UART_rx__0__PA__CFG10 CYREG_UDB_PA7_CFG10
#define UART_rx__0__PA__CFG11 CYREG_UDB_PA7_CFG11
#define UART_rx__0__PA__CFG12 CYREG_UDB_PA7_CFG12
#define UART_rx__0__PA__CFG13 CYREG_UDB_PA7_CFG13
#define UART_rx__0__PA__CFG14 CYREG_UDB_PA7_CFG14
#define UART_rx__0__PA__CFG2 CYREG_UDB_PA7_CFG2
#define UART_rx__0__PA__CFG3 CYREG_UDB_PA7_CFG3
#define UART_rx__0__PA__CFG4 CYREG_UDB_PA7_CFG4
#define UART_rx__0__PA__CFG5 CYREG_UDB_PA7_CFG5
#define UART_rx__0__PA__CFG6 CYREG_UDB_PA7_CFG6
#define UART_rx__0__PA__CFG7 CYREG_UDB_PA7_CFG7
#define UART_rx__0__PA__CFG8 CYREG_UDB_PA7_CFG8
#define UART_rx__0__PA__CFG9 CYREG_UDB_PA7_CFG9
#define UART_rx__0__PC CYREG_GPIO_PRT3_PC
#define UART_rx__0__PC2 CYREG_GPIO_PRT3_PC2
#define UART_rx__0__PORT 3u
#define UART_rx__0__PS CYREG_GPIO_PRT3_PS
#define UART_rx__0__SHIFT 0u
#define UART_rx__DR CYREG_GPIO_PRT3_DR
#define UART_rx__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define UART_rx__DR_INV CYREG_GPIO_PRT3_DR_INV
#define UART_rx__DR_SET CYREG_GPIO_PRT3_DR_SET
#define UART_rx__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_rx__INTR CYREG_GPIO_PRT3_INTR
#define UART_rx__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_rx__INTSTAT CYREG_GPIO_PRT3_INTR
#define UART_rx__MASK 0x01u
#define UART_rx__PA__CFG0 CYREG_UDB_PA7_CFG0
#define UART_rx__PA__CFG1 CYREG_UDB_PA7_CFG1
#define UART_rx__PA__CFG10 CYREG_UDB_PA7_CFG10
#define UART_rx__PA__CFG11 CYREG_UDB_PA7_CFG11
#define UART_rx__PA__CFG12 CYREG_UDB_PA7_CFG12
#define UART_rx__PA__CFG13 CYREG_UDB_PA7_CFG13
#define UART_rx__PA__CFG14 CYREG_UDB_PA7_CFG14
#define UART_rx__PA__CFG2 CYREG_UDB_PA7_CFG2
#define UART_rx__PA__CFG3 CYREG_UDB_PA7_CFG3
#define UART_rx__PA__CFG4 CYREG_UDB_PA7_CFG4
#define UART_rx__PA__CFG5 CYREG_UDB_PA7_CFG5
#define UART_rx__PA__CFG6 CYREG_UDB_PA7_CFG6
#define UART_rx__PA__CFG7 CYREG_UDB_PA7_CFG7
#define UART_rx__PA__CFG8 CYREG_UDB_PA7_CFG8
#define UART_rx__PA__CFG9 CYREG_UDB_PA7_CFG9
#define UART_rx__PC CYREG_GPIO_PRT3_PC
#define UART_rx__PC2 CYREG_GPIO_PRT3_PC2
#define UART_rx__PORT 3u
#define UART_rx__PS CYREG_GPIO_PRT3_PS
#define UART_rx__SHIFT 0u
#define UART_SCB__CTRL CYREG_SCB1_CTRL
#define UART_SCB__EZ_DATA0 CYREG_SCB1_EZ_DATA0
#define UART_SCB__EZ_DATA1 CYREG_SCB1_EZ_DATA1
#define UART_SCB__EZ_DATA10 CYREG_SCB1_EZ_DATA10
#define UART_SCB__EZ_DATA11 CYREG_SCB1_EZ_DATA11
#define UART_SCB__EZ_DATA12 CYREG_SCB1_EZ_DATA12
#define UART_SCB__EZ_DATA13 CYREG_SCB1_EZ_DATA13
#define UART_SCB__EZ_DATA14 CYREG_SCB1_EZ_DATA14
#define UART_SCB__EZ_DATA15 CYREG_SCB1_EZ_DATA15
#define UART_SCB__EZ_DATA16 CYREG_SCB1_EZ_DATA16
#define UART_SCB__EZ_DATA17 CYREG_SCB1_EZ_DATA17
#define UART_SCB__EZ_DATA18 CYREG_SCB1_EZ_DATA18
#define UART_SCB__EZ_DATA19 CYREG_SCB1_EZ_DATA19
#define UART_SCB__EZ_DATA2 CYREG_SCB1_EZ_DATA2
#define UART_SCB__EZ_DATA20 CYREG_SCB1_EZ_DATA20
#define UART_SCB__EZ_DATA21 CYREG_SCB1_EZ_DATA21
#define UART_SCB__EZ_DATA22 CYREG_SCB1_EZ_DATA22
#define UART_SCB__EZ_DATA23 CYREG_SCB1_EZ_DATA23
#define UART_SCB__EZ_DATA24 CYREG_SCB1_EZ_DATA24
#define UART_SCB__EZ_DATA25 CYREG_SCB1_EZ_DATA25
#define UART_SCB__EZ_DATA26 CYREG_SCB1_EZ_DATA26
#define UART_SCB__EZ_DATA27 CYREG_SCB1_EZ_DATA27
#define UART_SCB__EZ_DATA28 CYREG_SCB1_EZ_DATA28
#define UART_SCB__EZ_DATA29 CYREG_SCB1_EZ_DATA29
#define UART_SCB__EZ_DATA3 CYREG_SCB1_EZ_DATA3
#define UART_SCB__EZ_DATA30 CYREG_SCB1_EZ_DATA30
#define UART_SCB__EZ_DATA31 CYREG_SCB1_EZ_DATA31
#define UART_SCB__EZ_DATA4 CYREG_SCB1_EZ_DATA4
#define UART_SCB__EZ_DATA5 CYREG_SCB1_EZ_DATA5
#define UART_SCB__EZ_DATA6 CYREG_SCB1_EZ_DATA6
#define UART_SCB__EZ_DATA7 CYREG_SCB1_EZ_DATA7
#define UART_SCB__EZ_DATA8 CYREG_SCB1_EZ_DATA8
#define UART_SCB__EZ_DATA9 CYREG_SCB1_EZ_DATA9
#define UART_SCB__I2C_CFG CYREG_SCB1_I2C_CFG
#define UART_SCB__I2C_CTRL CYREG_SCB1_I2C_CTRL
#define UART_SCB__I2C_M_CMD CYREG_SCB1_I2C_M_CMD
#define UART_SCB__I2C_S_CMD CYREG_SCB1_I2C_S_CMD
#define UART_SCB__I2C_STATUS CYREG_SCB1_I2C_STATUS
#define UART_SCB__INTR_CAUSE CYREG_SCB1_INTR_CAUSE
#define UART_SCB__INTR_I2C_EC CYREG_SCB1_INTR_I2C_EC
#define UART_SCB__INTR_I2C_EC_MASK CYREG_SCB1_INTR_I2C_EC_MASK
#define UART_SCB__INTR_I2C_EC_MASKED CYREG_SCB1_INTR_I2C_EC_MASKED
#define UART_SCB__INTR_M CYREG_SCB1_INTR_M
#define UART_SCB__INTR_M_MASK CYREG_SCB1_INTR_M_MASK
#define UART_SCB__INTR_M_MASKED CYREG_SCB1_INTR_M_MASKED
#define UART_SCB__INTR_M_SET CYREG_SCB1_INTR_M_SET
#define UART_SCB__INTR_RX CYREG_SCB1_INTR_RX
#define UART_SCB__INTR_RX_MASK CYREG_SCB1_INTR_RX_MASK
#define UART_SCB__INTR_RX_MASKED CYREG_SCB1_INTR_RX_MASKED
#define UART_SCB__INTR_RX_SET CYREG_SCB1_INTR_RX_SET
#define UART_SCB__INTR_S CYREG_SCB1_INTR_S
#define UART_SCB__INTR_S_MASK CYREG_SCB1_INTR_S_MASK
#define UART_SCB__INTR_S_MASKED CYREG_SCB1_INTR_S_MASKED
#define UART_SCB__INTR_S_SET CYREG_SCB1_INTR_S_SET
#define UART_SCB__INTR_SPI_EC CYREG_SCB1_INTR_SPI_EC
#define UART_SCB__INTR_SPI_EC_MASK CYREG_SCB1_INTR_SPI_EC_MASK
#define UART_SCB__INTR_SPI_EC_MASKED CYREG_SCB1_INTR_SPI_EC_MASKED
#define UART_SCB__INTR_TX CYREG_SCB1_INTR_TX
#define UART_SCB__INTR_TX_MASK CYREG_SCB1_INTR_TX_MASK
#define UART_SCB__INTR_TX_MASKED CYREG_SCB1_INTR_TX_MASKED
#define UART_SCB__INTR_TX_SET CYREG_SCB1_INTR_TX_SET
#define UART_SCB__RX_CTRL CYREG_SCB1_RX_CTRL
#define UART_SCB__RX_FIFO_CTRL CYREG_SCB1_RX_FIFO_CTRL
#define UART_SCB__RX_FIFO_RD CYREG_SCB1_RX_FIFO_RD
#define UART_SCB__RX_FIFO_RD_SILENT CYREG_SCB1_RX_FIFO_RD_SILENT
#define UART_SCB__RX_FIFO_STATUS CYREG_SCB1_RX_FIFO_STATUS
#define UART_SCB__RX_MATCH CYREG_SCB1_RX_MATCH
#define UART_SCB__SPI_CTRL CYREG_SCB1_SPI_CTRL
#define UART_SCB__SPI_STATUS CYREG_SCB1_SPI_STATUS
#define UART_SCB__SS0_POSISTION 0u
#define UART_SCB__SS1_POSISTION 1u
#define UART_SCB__SS2_POSISTION 2u
#define UART_SCB__SS3_POSISTION 3u
#define UART_SCB__STATUS CYREG_SCB1_STATUS
#define UART_SCB__TX_CTRL CYREG_SCB1_TX_CTRL
#define UART_SCB__TX_FIFO_CTRL CYREG_SCB1_TX_FIFO_CTRL
#define UART_SCB__TX_FIFO_STATUS CYREG_SCB1_TX_FIFO_STATUS
#define UART_SCB__TX_FIFO_WR CYREG_SCB1_TX_FIFO_WR
#define UART_SCB__UART_CTRL CYREG_SCB1_UART_CTRL
#define UART_SCB__UART_FLOW_CTRL CYREG_SCB1_UART_FLOW_CTRL
#define UART_SCB__UART_RX_CTRL CYREG_SCB1_UART_RX_CTRL
#define UART_SCB__UART_RX_STATUS CYREG_SCB1_UART_RX_STATUS
#define UART_SCB__UART_TX_CTRL CYREG_SCB1_UART_TX_CTRL
#define UART_SCBCLK__CTRL_REGISTER CYREG_PERI_PCLK_CTL3
#define UART_SCBCLK__DIV_ID 0x00000041u
#define UART_SCBCLK__DIV_REGISTER CYREG_PERI_DIV_16_CTL1
#define UART_SCBCLK__PA_DIV_ID 0x000000FFu
#define UART_tx__0__DR CYREG_GPIO_PRT3_DR
#define UART_tx__0__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define UART_tx__0__DR_INV CYREG_GPIO_PRT3_DR_INV
#define UART_tx__0__DR_SET CYREG_GPIO_PRT3_DR_SET
#define UART_tx__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define UART_tx__0__HSIOM_GPIO 0u
#define UART_tx__0__HSIOM_I2C 14u
#define UART_tx__0__HSIOM_I2C_SDA 14u
#define UART_tx__0__HSIOM_MASK 0x000000F0u
#define UART_tx__0__HSIOM_SHIFT 4u
#define UART_tx__0__HSIOM_SPI 15u
#define UART_tx__0__HSIOM_SPI_MISO 15u
#define UART_tx__0__HSIOM_UART 9u
#define UART_tx__0__HSIOM_UART_TX 9u
#define UART_tx__0__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_tx__0__INTR CYREG_GPIO_PRT3_INTR
#define UART_tx__0__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_tx__0__INTSTAT CYREG_GPIO_PRT3_INTR
#define UART_tx__0__MASK 0x02u
#define UART_tx__0__OUT_SEL CYREG_UDB_PA7_CFG10
#define UART_tx__0__OUT_SEL_SHIFT 2u
#define UART_tx__0__OUT_SEL_VAL -1u
#define UART_tx__0__PA__CFG0 CYREG_UDB_PA7_CFG0
#define UART_tx__0__PA__CFG1 CYREG_UDB_PA7_CFG1
#define UART_tx__0__PA__CFG10 CYREG_UDB_PA7_CFG10
#define UART_tx__0__PA__CFG11 CYREG_UDB_PA7_CFG11
#define UART_tx__0__PA__CFG12 CYREG_UDB_PA7_CFG12
#define UART_tx__0__PA__CFG13 CYREG_UDB_PA7_CFG13
#define UART_tx__0__PA__CFG14 CYREG_UDB_PA7_CFG14
#define UART_tx__0__PA__CFG2 CYREG_UDB_PA7_CFG2
#define UART_tx__0__PA__CFG3 CYREG_UDB_PA7_CFG3
#define UART_tx__0__PA__CFG4 CYREG_UDB_PA7_CFG4
#define UART_tx__0__PA__CFG5 CYREG_UDB_PA7_CFG5
#define UART_tx__0__PA__CFG6 CYREG_UDB_PA7_CFG6
#define UART_tx__0__PA__CFG7 CYREG_UDB_PA7_CFG7
#define UART_tx__0__PA__CFG8 CYREG_UDB_PA7_CFG8
#define UART_tx__0__PA__CFG9 CYREG_UDB_PA7_CFG9
#define UART_tx__0__PC CYREG_GPIO_PRT3_PC
#define UART_tx__0__PC2 CYREG_GPIO_PRT3_PC2
#define UART_tx__0__PORT 3u
#define UART_tx__0__PS CYREG_GPIO_PRT3_PS
#define UART_tx__0__SHIFT 1u
#define UART_tx__DR CYREG_GPIO_PRT3_DR
#define UART_tx__DR_CLR CYREG_GPIO_PRT3_DR_CLR
#define UART_tx__DR_INV CYREG_GPIO_PRT3_DR_INV
#define UART_tx__DR_SET CYREG_GPIO_PRT3_DR_SET
#define UART_tx__INTCFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_tx__INTR CYREG_GPIO_PRT3_INTR
#define UART_tx__INTR_CFG CYREG_GPIO_PRT3_INTR_CFG
#define UART_tx__INTSTAT CYREG_GPIO_PRT3_INTR
#define UART_tx__MASK 0x02u
#define UART_tx__PA__CFG0 CYREG_UDB_PA7_CFG0
#define UART_tx__PA__CFG1 CYREG_UDB_PA7_CFG1
#define UART_tx__PA__CFG10 CYREG_UDB_PA7_CFG10
#define UART_tx__PA__CFG11 CYREG_UDB_PA7_CFG11
#define UART_tx__PA__CFG12 CYREG_UDB_PA7_CFG12
#define UART_tx__PA__CFG13 CYREG_UDB_PA7_CFG13
#define UART_tx__PA__CFG14 CYREG_UDB_PA7_CFG14
#define UART_tx__PA__CFG2 CYREG_UDB_PA7_CFG2
#define UART_tx__PA__CFG3 CYREG_UDB_PA7_CFG3
#define UART_tx__PA__CFG4 CYREG_UDB_PA7_CFG4
#define UART_tx__PA__CFG5 CYREG_UDB_PA7_CFG5
#define UART_tx__PA__CFG6 CYREG_UDB_PA7_CFG6
#define UART_tx__PA__CFG7 CYREG_UDB_PA7_CFG7
#define UART_tx__PA__CFG8 CYREG_UDB_PA7_CFG8
#define UART_tx__PA__CFG9 CYREG_UDB_PA7_CFG9
#define UART_tx__PC CYREG_GPIO_PRT3_PC
#define UART_tx__PC2 CYREG_GPIO_PRT3_PC2
#define UART_tx__PORT 3u
#define UART_tx__PS CYREG_GPIO_PRT3_PS
#define UART_tx__SHIFT 1u

/* Miscellaneous */
#define CY_PROJECT_NAME "CAN_Full_P4_Example01"
#define CY_VERSION "PSoC Creator  4.2"
#define CYDEV_BANDGAP_VOLTAGE 1.024
#define CYDEV_BCLK__HFCLK__HZ 24000000U
#define CYDEV_BCLK__HFCLK__KHZ 24000U
#define CYDEV_BCLK__HFCLK__MHZ 24U
#define CYDEV_BCLK__SYSCLK__HZ 24000000U
#define CYDEV_BCLK__SYSCLK__KHZ 24000U
#define CYDEV_BCLK__SYSCLK__MHZ 24U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PSOC4A 18u
#define CYDEV_CHIP_DIE_PSOC5LP 2u
#define CYDEV_CHIP_DIE_PSOC5TM 3u
#define CYDEV_CHIP_DIE_TMA4 4u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_FM0P 5u
#define CYDEV_CHIP_FAMILY_FM3 6u
#define CYDEV_CHIP_FAMILY_FM4 7u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_PSOC6 4u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x101311A0u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 18u
#define CYDEV_CHIP_MEMBER_4D 13u
#define CYDEV_CHIP_MEMBER_4E 6u
#define CYDEV_CHIP_MEMBER_4F 19u
#define CYDEV_CHIP_MEMBER_4G 4u
#define CYDEV_CHIP_MEMBER_4H 17u
#define CYDEV_CHIP_MEMBER_4I 23u
#define CYDEV_CHIP_MEMBER_4J 14u
#define CYDEV_CHIP_MEMBER_4K 15u
#define CYDEV_CHIP_MEMBER_4L 22u
#define CYDEV_CHIP_MEMBER_4M 21u
#define CYDEV_CHIP_MEMBER_4N 10u
#define CYDEV_CHIP_MEMBER_4O 7u
#define CYDEV_CHIP_MEMBER_4P 20u
#define CYDEV_CHIP_MEMBER_4Q 12u
#define CYDEV_CHIP_MEMBER_4R 8u
#define CYDEV_CHIP_MEMBER_4S 11u
#define CYDEV_CHIP_MEMBER_4T 9u
#define CYDEV_CHIP_MEMBER_4U 5u
#define CYDEV_CHIP_MEMBER_4V 16u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_MEMBER_5B 2u
#define CYDEV_CHIP_MEMBER_6A 24u
#define CYDEV_CHIP_MEMBER_FM3 28u
#define CYDEV_CHIP_MEMBER_FM4 29u
#define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 25u
#define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 26u
#define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 27u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4L
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_PSOC5TM_ES0 0u
#define CYDEV_CHIP_REV_PSOC5TM_ES1 1u
#define CYDEV_CHIP_REV_PSOC5TM_PRODUCTION 1u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4O_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4P_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4R_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4S_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4T_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4V_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_6A_ES 17u
#define CYDEV_CHIP_REVISION_6A_NO_UDB 33u
#define CYDEV_CHIP_REVISION_6A_PRODUCTION 33u
#define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4L_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DFT_SELECT_CLK0 8u
#define CYDEV_DFT_SELECT_CLK1 9u
#define CYDEV_DMA_CHANNELS_AVAILABLE 32
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_IMO_TRIMMED_BY_USB 0u
#define CYDEV_IMO_TRIMMED_BY_WCO 1u
#define CYDEV_INTR_NUMBER_DMA 14u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0800
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VBUS 5.0
#define CYDEV_VBUS_MV 5000
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYDEV_VDDIO 3.3
#define CYDEV_VDDIO_MV 3300
#define CYDEV_WDT_GENERATE_ISR 1u
#define CYIPBLOCK_m0s8can_VERSION 1
#define CYIPBLOCK_m0s8cpussv2_VERSION 1
#define CYIPBLOCK_m0s8csd_VERSION 1
#define CYIPBLOCK_m0s8ioss_VERSION 1
#define CYIPBLOCK_m0s8lcd_VERSION 2
#define CYIPBLOCK_m0s8lpcomp_VERSION 2
#define CYIPBLOCK_m0s8peri_VERSION 1
#define CYIPBLOCK_m0s8scb_VERSION 2
#define CYIPBLOCK_m0s8srssv2_VERSION 2
#define CYIPBLOCK_m0s8tcpwm_VERSION 2
#define CYIPBLOCK_m0s8udb_VERSION 1
#define CYIPBLOCK_m0s8usbdss_VERSION 2
#define CYIPBLOCK_m0s8wco_VERSION 1
#define CYIPBLOCK_s8pass4al_VERSION 1
#define DMA_CHANNELS_USED__MASK 0u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
