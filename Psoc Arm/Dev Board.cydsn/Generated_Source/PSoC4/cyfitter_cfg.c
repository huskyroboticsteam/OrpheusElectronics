
/*******************************************************************************
* File Name: cyfitter_cfg.c
* 
* PSoC Creator  4.2
*
* Description:
* This file contains device initialization code.
* Except for the user defined sections in CyClockStartupError(), this file should not be modified.
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include <string.h>
#include "cytypes.h"
#include "cydevice_trm.h"
#include "cyfitter.h"
#include "CyLib.h"
#include "CyLFClk.h"
#include "cyfitter_cfg.h"
#include "cyapicallbacks.h"


#if defined(__GNUC__) || defined(__ARMCC_VERSION)
    #define CYPACKED 
    #define CYPACKED_ATTR __attribute__ ((packed))
    #define CYALIGNED __attribute__ ((aligned))
    #define CY_CFG_UNUSED __attribute__ ((unused))
    #ifndef CY_CFG_SECTION
        #define CY_CFG_SECTION __attribute__ ((section(".psocinit")))
    #endif
    
    #if defined(__ARMCC_VERSION)
        #define CY_CFG_MEMORY_BARRIER() __memory_changed()
    #else
        #define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
    #endif
    
#elif defined(__ICCARM__)
    #include <intrinsics.h>

    #define CYPACKED __packed
    #define CYPACKED_ATTR 
    #define CYALIGNED _Pragma("data_alignment=4")
    #define CY_CFG_UNUSED _Pragma("diag_suppress=Pe177")
    #define CY_CFG_SECTION _Pragma("location=\".psocinit\"")
    
    #define CY_CFG_MEMORY_BARRIER() __DMB()
    
#else
    #error Unsupported toolchain
#endif

#ifndef CYCODE
    #define CYCODE
#endif
#ifndef CYDATA
    #define CYDATA
#endif
#ifndef CYFAR
    #define CYFAR
#endif
#ifndef CYXDATA
    #define CYXDATA
#endif


CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n);
CY_CFG_UNUSED
static void CYMEMZERO(void *s, size_t n)
{
	(void)memset(s, 0, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPY(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n);
CY_CFG_UNUSED
static void CYCONFIGCPYCODE(void *dest, const void *src, size_t n)
{
	(void)memcpy(dest, src, n);
}




/* Clock startup error codes                                                   */
#define CYCLOCKSTART_NO_ERROR    0u
#define CYCLOCKSTART_XTAL_ERROR  1u
#define CYCLOCKSTART_32KHZ_ERROR 2u
#define CYCLOCKSTART_PLL_ERROR   3u
#define CYCLOCKSTART_FLL_ERROR   4u
#define CYCLOCKSTART_WCO_ERROR   5u


#ifdef CY_NEED_CYCLOCKSTARTUPERROR
/*******************************************************************************
* Function Name: CyClockStartupError
********************************************************************************
* Summary:
*  If an error is encountered during clock configuration (crystal startup error,
*  PLL lock error, etc.), the system will end up here.  Unless reimplemented by
*  the customer, this function will stop in an infinite loop.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode);
CY_CFG_UNUSED
static void CyClockStartupError(uint8 errorCode)
{
    /* To remove the compiler warning if errorCode not used.                */
    errorCode = errorCode;

    /* If we have a clock startup error (bad MHz crystal, PLL lock, etc.),  */
    /* we will end up here to allow the customer to implement something to  */
    /* deal with the clock condition.                                       */

#ifdef CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK
    CY_CFG_Clock_Startup_ErrorCallback();
#else
    /*  If not using CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK, place your clock startup code here. */
    /* `#START CyClockStartupError` */



    /* `#END` */

    while(1) {}
#endif /* CY_CFG_CLOCK_STARTUP_ERROR_CALLBACK */
}
#endif

#define CY_CFG_BASE_ADDR_COUNT 14u
CYPACKED typedef struct
{
	uint8 offset;
	uint8 value;
} CYPACKED_ATTR cy_cfg_addrvalue_t;



/*******************************************************************************
* Function Name: cfg_write_bytes32
********************************************************************************
* Summary:
*  This function is used for setting up the chip configuration areas that
*  contain relatively sparse data.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[]);
static void cfg_write_bytes32(const uint32 addr_table[], const cy_cfg_addrvalue_t data_table[])
{
	/* For 32-bit little-endian architectures */
	uint32 i, j = 0u;
	for (i = 0u; i < CY_CFG_BASE_ADDR_COUNT; i++)
	{
		uint32 baseAddr = addr_table[i];
		uint8 count = (uint8)baseAddr;
		baseAddr &= 0xFFFFFF00u;
		while (count != 0u)
		{
			CY_SET_REG8((void *)(baseAddr + data_table[j].offset), data_table[j].value);
			j++;
			count--;
		}
	}
}


/*******************************************************************************
* Function Name: ClockSetup
********************************************************************************
*
* Summary:
*   Performs the initialization of all of the clocks in the device based on the
*   settings in the Clock tab of the DWR.  This includes enabling the requested
*   clocks and setting the necessary dividers to produce the desired frequency. 
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
static void ClockSetup(void);
CY_CFG_SECTION
static void ClockSetup(void)
{

	/* Set Flash Cycles based on max possible frequency in case a glitch occurs during ClockSetup(). */
	CY_SET_REG32((void CYXDATA *)(CYREG_CPUSS_FLASH_CTL), (0x0012u));

	/* Start the WCO */
	CySysClkWcoStart();
	CyDelayCycles(12000000u); /* WCO may take up to 500ms to start */

	/* Setup and trim IMO based on desired frequency. */
	CySysClkWriteImoFreq(48u);
	CySysClkImoEnableWcoLock();
	/* CYDEV_WDT_CONFIG Starting address: CYDEV_WDT_CONFIG */
	CY_SET_REG32((void *)(CYREG_WDT_CONFIG), 0x40000000u);


	/* Setup phase aligned clocks */
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL0, 0x00000000u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF40u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_24_5_CTL, 0x0752FF00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FFC0u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL5, 0x00BB7F00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF45u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL1, 0x00000100u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF41u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL2, 0x00000800u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF42u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL4, 0x00002200u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF44u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_16_CTL3, 0x00001D00u);
	CY_SET_REG32((void *)CYREG_PERI_DIV_CMD, 0x8000FF43u);

	/* CYDEV_CLK_IMO_CONFIG Starting address: CYDEV_CLK_IMO_CONFIG */
	CY_SET_REG32((void *)(CYREG_CLK_IMO_CONFIG), 0x82000000u);

	/* CYDEV_CLK_SELECT Starting address: CYDEV_CLK_SELECT */
	CY_SET_REG32((void *)(CYREG_CLK_SELECT), 0x00060000u);

	/* CYDEV_PERI_PCLK_CTL22 Starting address: CYDEV_PERI_PCLK_CTL22 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL22), 0x000000C0u);

	/* CYDEV_PERI_PCLK_CTL20 Starting address: CYDEV_PERI_PCLK_CTL20 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL20), 0x00000045u);

	/* CYDEV_PERI_PCLK_CTL18 Starting address: CYDEV_PERI_PCLK_CTL18 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL18), 0x00000041u);

	/* CYDEV_PERI_PCLK_CTL10 Starting address: CYDEV_PERI_PCLK_CTL10 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL10), 0x00000042u);

	/* CYDEV_PERI_PCLK_CTL3 Starting address: CYDEV_PERI_PCLK_CTL3 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL3), 0x00000044u);

	/* CYDEV_PERI_PCLK_CTL2 Starting address: CYDEV_PERI_PCLK_CTL2 */
	CY_SET_REG32((void *)(CYREG_PERI_PCLK_CTL2), 0x00000043u);

	(void)CyIntSetVector(8u, &CySysWdtIsr);
	CyIntEnable(8u);
	CY_SET_REG32((void *)(CYREG_WDT_CONFIG), 0x40000000u);
}


/* Analog API Functions */


/*******************************************************************************
* Function Name: AnalogSetDefault
********************************************************************************
*
* Summary:
*  Sets up the analog portions of the chip to default values based on chip
*  configuration options from the project.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
static void AnalogSetDefault(void);
static void AnalogSetDefault(void)
{
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTBM0_DFT_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_CTBM1_DFT_CTRL, 0x00000003u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_SAR_CTRL, 0x80000000u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_SAR_MUX_SWITCH0, 0x00000021u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_SAR_MUX_SWITCH_HW_CTRL, 0x00000021u);
	CY_SET_XTND_REG32((void CYFAR *)CYREG_PASS_DSAB_DSAB_CTRL, 0x00000000u);
	SetAnalogRoutingPumps(1);
}


/*******************************************************************************
* Function Name: SetAnalogRoutingPumps
********************************************************************************
*
* Summary:
* Enables or disables the analog pumps feeding analog routing switches.
* Intended to be called at startup, based on the Vdda system configuration;
* may be called during operation when the user informs us that the Vdda voltage crossed the pump threshold.
*
* Parameters:
*  enabled - 1 to enable the pumps, 0 to disable the pumps
*
* Return:
*  void
*
*******************************************************************************/
void SetAnalogRoutingPumps(uint8 enabled)
{
	uint32 regValue = CY_GET_XTND_REG32((void *)(CYREG_SAR_PUMP_CTRL));
	if (enabled != 0u)
	{
		regValue |= 0x80000000u;
	}
	else
	{
		regValue &= ~0x80000000u;
	}
	CY_SET_XTND_REG32((void *)(CYREG_SAR_PUMP_CTRL), regValue);
}




/*******************************************************************************
* Function Name: cyfitter_cfg
********************************************************************************
* Summary:
*  This function is called by the start-up code for the selected device. It
*  performs all of the necessary device configuration based on the design
*  settings.  This includes settings from the Design Wide Resources (DWR) such
*  as Clocks and Pins as well as any component configuration that is necessary.
*
* Parameters:
*   void
*
* Return:
*   void
*
*******************************************************************************/
CY_CFG_SECTION
void cyfitter_cfg(void)
{
	/* Disable interrupts by default. Let user enable if/when they want. */
	CyGlobalIntDisable;

	/* Enable the clock in the interrupt controller for the routed interrupts */
	CY_SET_REG8((void *)CYREG_UDB_UDB_INT_CLK_CTL, 0x01u);
	{
		static const uint32 CYCODE cy_cfg_addr_table[] = {
			0x400F0003u, /* Base address: 0x400F0000 Count: 3 */
			0x400F303Fu, /* Base address: 0x400F3000 Count: 63 */
			0x400F312Eu, /* Base address: 0x400F3100 Count: 46 */
			0x400F325Cu, /* Base address: 0x400F3200 Count: 92 */
			0x400F333Eu, /* Base address: 0x400F3300 Count: 62 */
			0x400F343Fu, /* Base address: 0x400F3400 Count: 63 */
			0x400F3536u, /* Base address: 0x400F3500 Count: 54 */
			0x400F4005u, /* Base address: 0x400F4000 Count: 5 */
			0x400F4107u, /* Base address: 0x400F4100 Count: 7 */
			0x400F4205u, /* Base address: 0x400F4200 Count: 5 */
			0x400F4408u, /* Base address: 0x400F4400 Count: 8 */
			0x400F4507u, /* Base address: 0x400F4500 Count: 7 */
			0x400F4603u, /* Base address: 0x400F4600 Count: 3 */
			0x400F6003u, /* Base address: 0x400F6000 Count: 3 */
		};

		static const cy_cfg_addrvalue_t CYCODE cy_cfg_data_table[] = {
			{0x80u, 0x6Fu},
			{0x84u, 0x0Fu},
			{0x85u, 0x03u},
			{0x01u, 0x10u},
			{0x07u, 0x10u},
			{0x09u, 0x04u},
			{0x0Bu, 0x08u},
			{0x0Du, 0x02u},
			{0x0Fu, 0x1Du},
			{0x14u, 0x04u},
			{0x15u, 0x1Cu},
			{0x18u, 0x01u},
			{0x19u, 0x04u},
			{0x1Bu, 0x08u},
			{0x1Du, 0x1Cu},
			{0x22u, 0x03u},
			{0x23u, 0x03u},
			{0x25u, 0x03u},
			{0x2Au, 0x0Cu},
			{0x2Bu, 0x20u},
			{0x30u, 0x04u},
			{0x31u, 0x3Cu},
			{0x32u, 0x08u},
			{0x34u, 0x02u},
			{0x35u, 0x02u},
			{0x36u, 0x01u},
			{0x37u, 0x01u},
			{0x3Eu, 0x41u},
			{0x3Fu, 0x50u},
			{0x54u, 0x0Fu},
			{0x58u, 0x04u},
			{0x59u, 0x04u},
			{0x5Bu, 0x04u},
			{0x5Cu, 0x11u},
			{0x5Du, 0x10u},
			{0x5Fu, 0x05u},
			{0x81u, 0x05u},
			{0x83u, 0x0Au},
			{0x84u, 0x9Eu},
			{0x85u, 0x07u},
			{0x86u, 0x60u},
			{0x88u, 0x94u},
			{0x8Au, 0x60u},
			{0x92u, 0x0Fu},
			{0x95u, 0x0Cu},
			{0x97u, 0x03u},
			{0x98u, 0x73u},
			{0x99u, 0x0Au},
			{0x9Bu, 0x05u},
			{0x9Cu, 0x30u},
			{0x9Du, 0x0Fu},
			{0x9Eu, 0xC9u},
			{0xA4u, 0xCFu},
			{0xA5u, 0x03u},
			{0xA6u, 0x30u},
			{0xA7u, 0x0Cu},
			{0xACu, 0xFDu},
			{0xAEu, 0x02u},
			{0xB1u, 0x0Fu},
			{0xB2u, 0xFFu},
			{0xBEu, 0x04u},
			{0xD8u, 0x04u},
			{0xD9u, 0x04u},
			{0xDBu, 0x04u},
			{0xDCu, 0x10u},
			{0xDFu, 0x01u},
			{0x05u, 0x10u},
			{0x06u, 0x18u},
			{0x07u, 0x10u},
			{0x0Au, 0x18u},
			{0x0Eu, 0x04u},
			{0x0Fu, 0x41u},
			{0x10u, 0x88u},
			{0x13u, 0x20u},
			{0x15u, 0x08u},
			{0x17u, 0x44u},
			{0x19u, 0x81u},
			{0x1Au, 0x18u},
			{0x1Bu, 0x10u},
			{0x1Fu, 0x08u},
			{0x22u, 0x50u},
			{0x23u, 0x40u},
			{0x24u, 0x80u},
			{0x27u, 0x40u},
			{0x2Bu, 0x58u},
			{0x2Eu, 0x08u},
			{0x30u, 0x04u},
			{0x31u, 0x10u},
			{0x33u, 0x40u},
			{0x37u, 0x54u},
			{0x39u, 0x08u},
			{0x3Au, 0x10u},
			{0x3Bu, 0x41u},
			{0x3Eu, 0x04u},
			{0x3Fu, 0x01u},
			{0x59u, 0x89u},
			{0x5Bu, 0x20u},
			{0x5Cu, 0x06u},
			{0x5Du, 0x40u},
			{0x5Fu, 0x10u},
			{0x61u, 0x24u},
			{0x78u, 0x04u},
			{0x8Du, 0x40u},
			{0xC0u, 0x60u},
			{0xC2u, 0xD6u},
			{0xC4u, 0xAAu},
			{0xCAu, 0x47u},
			{0xCCu, 0x7Eu},
			{0xCEu, 0xCFu},
			{0xD6u, 0xFFu},
			{0xD8u, 0x06u},
			{0xDEu, 0x02u},
			{0x04u, 0x06u},
			{0x0Cu, 0x05u},
			{0x18u, 0x03u},
			{0x24u, 0x06u},
			{0x2Du, 0x01u},
			{0x31u, 0x01u},
			{0x34u, 0x07u},
			{0x38u, 0x20u},
			{0x40u, 0x36u},
			{0x41u, 0x05u},
			{0x49u, 0xFFu},
			{0x4Au, 0xFFu},
			{0x4Bu, 0xFFu},
			{0x4Du, 0xA0u},
			{0x4Fu, 0x01u},
			{0x50u, 0x18u},
			{0x58u, 0x04u},
			{0x59u, 0x04u},
			{0x5Au, 0x04u},
			{0x5Cu, 0x31u},
			{0x5Du, 0x01u},
			{0x5Fu, 0x01u},
			{0x60u, 0x40u},
			{0x62u, 0x80u},
			{0x64u, 0x40u},
			{0x65u, 0x40u},
			{0x66u, 0x80u},
			{0x68u, 0x40u},
			{0x6Au, 0x80u},
			{0x6Cu, 0x40u},
			{0x6Du, 0x20u},
			{0x6Eu, 0x80u},
			{0x81u, 0x01u},
			{0x85u, 0x1Cu},
			{0x8Bu, 0x07u},
			{0x8Du, 0x18u},
			{0x8Fu, 0x04u},
			{0x90u, 0x08u},
			{0x97u, 0x20u},
			{0x98u, 0x01u},
			{0x99u, 0x18u},
			{0x9Du, 0x08u},
			{0x9Fu, 0x10u},
			{0xA5u, 0x0Cu},
			{0xA8u, 0x03u},
			{0xA9u, 0x14u},
			{0xABu, 0x08u},
			{0xACu, 0x03u},
			{0xAEu, 0x0Cu},
			{0xAFu, 0x01u},
			{0xB0u, 0x04u},
			{0xB1u, 0x02u},
			{0xB2u, 0x08u},
			{0xB3u, 0x01u},
			{0xB4u, 0x01u},
			{0xB5u, 0x1Cu},
			{0xB6u, 0x02u},
			{0xB7u, 0x20u},
			{0xB8u, 0xA0u},
			{0xBEu, 0x14u},
			{0xBFu, 0x04u},
			{0xC0u, 0x32u},
			{0xC1u, 0x05u},
			{0xC5u, 0x0Eu},
			{0xC6u, 0xC4u},
			{0xC7u, 0x32u},
			{0xC8u, 0x3Du},
			{0xC9u, 0xFFu},
			{0xCAu, 0xFFu},
			{0xCBu, 0xFFu},
			{0xCDu, 0xAFu},
			{0xCEu, 0x07u},
			{0xCFu, 0x01u},
			{0xD0u, 0x18u},
			{0xD2u, 0x80u},
			{0xD8u, 0x04u},
			{0xD9u, 0x04u},
			{0xDAu, 0x04u},
			{0xDBu, 0x04u},
			{0xDCu, 0x11u},
			{0xDDu, 0x11u},
			{0xDFu, 0x01u},
			{0xE0u, 0x40u},
			{0xE2u, 0x80u},
			{0xE4u, 0x40u},
			{0xE5u, 0x40u},
			{0xE6u, 0x80u},
			{0xE8u, 0x40u},
			{0xEAu, 0x80u},
			{0xECu, 0x40u},
			{0xEDu, 0x20u},
			{0xEEu, 0x80u},
			{0x04u, 0x80u},
			{0x07u, 0x11u},
			{0x09u, 0x10u},
			{0x0Au, 0x44u},
			{0x0Eu, 0x04u},
			{0x10u, 0x0Au},
			{0x15u, 0x08u},
			{0x18u, 0x04u},
			{0x19u, 0x08u},
			{0x1Au, 0x40u},
			{0x1Bu, 0x50u},
			{0x1Eu, 0x04u},
			{0x1Fu, 0x20u},
			{0x20u, 0x01u},
			{0x21u, 0x19u},
			{0x24u, 0x40u},
			{0x2Au, 0x90u},
			{0x2Bu, 0x20u},
			{0x2Fu, 0x01u},
			{0x31u, 0x10u},
			{0x32u, 0x80u},
			{0x33u, 0x04u},
			{0x38u, 0x80u},
			{0x39u, 0x2Au},
			{0x40u, 0x04u},
			{0x41u, 0x08u},
			{0x45u, 0x08u},
			{0x49u, 0x04u},
			{0x4Bu, 0x40u},
			{0x4Fu, 0x60u},
			{0x50u, 0x8Au},
			{0x51u, 0x20u},
			{0x58u, 0x04u},
			{0x5Au, 0x04u},
			{0x72u, 0x80u},
			{0x90u, 0x80u},
			{0x92u, 0xA0u},
			{0x93u, 0x40u},
			{0x95u, 0x08u},
			{0x96u, 0x04u},
			{0x97u, 0x01u},
			{0x9Au, 0x10u},
			{0x9Bu, 0x08u},
			{0x9Cu, 0x04u},
			{0x9Du, 0x1Cu},
			{0x9Fu, 0x10u},
			{0xA3u, 0x04u},
			{0xA4u, 0x88u},
			{0xA5u, 0x20u},
			{0xA7u, 0x40u},
			{0xABu, 0x04u},
			{0xAFu, 0x08u},
			{0xB3u, 0x10u},
			{0xB4u, 0x06u},
			{0xC0u, 0xA0u},
			{0xC2u, 0x4Au},
			{0xC4u, 0x23u},
			{0xCAu, 0x1Eu},
			{0xCCu, 0x0Eu},
			{0xCEu, 0x0Fu},
			{0xD0u, 0x46u},
			{0xD2u, 0x38u},
			{0x00u, 0x01u},
			{0x01u, 0x10u},
			{0x03u, 0x20u},
			{0x05u, 0x0Cu},
			{0x07u, 0x02u},
			{0x09u, 0x0Cu},
			{0x0Bu, 0x01u},
			{0x0Du, 0x0Bu},
			{0x0Fu, 0x04u},
			{0x11u, 0x10u},
			{0x13u, 0x20u},
			{0x15u, 0x10u},
			{0x17u, 0x20u},
			{0x1Bu, 0x0Fu},
			{0x1Du, 0x28u},
			{0x1Fu, 0x11u},
			{0x29u, 0x07u},
			{0x33u, 0x0Fu},
			{0x34u, 0x01u},
			{0x37u, 0x30u},
			{0x3Bu, 0x80u},
			{0x54u, 0x0Fu},
			{0x58u, 0x04u},
			{0x59u, 0x04u},
			{0x5Bu, 0x04u},
			{0x5Cu, 0x13u},
			{0x5Du, 0x10u},
			{0x5Fu, 0x01u},
			{0x80u, 0x01u},
			{0x82u, 0x02u},
			{0x83u, 0x0Fu},
			{0x87u, 0x20u},
			{0x88u, 0x02u},
			{0x89u, 0x07u},
			{0x8Au, 0x01u},
			{0x93u, 0x10u},
			{0x94u, 0x01u},
			{0x95u, 0x0Cu},
			{0x96u, 0x0Au},
			{0x97u, 0x01u},
			{0x99u, 0x0Cu},
			{0x9Bu, 0x02u},
			{0x9Cu, 0x01u},
			{0x9Eu, 0x06u},
			{0xA1u, 0x0Bu},
			{0xA3u, 0x04u},
			{0xA5u, 0x08u},
			{0xA6u, 0x10u},
			{0xA7u, 0x01u},
			{0xB0u, 0x04u},
			{0xB1u, 0x20u},
			{0xB2u, 0x10u},
			{0xB3u, 0x0Fu},
			{0xB4u, 0x03u},
			{0xB5u, 0x10u},
			{0xB6u, 0x08u},
			{0xBAu, 0x20u},
			{0xD6u, 0x04u},
			{0xD8u, 0x04u},
			{0xD9u, 0x04u},
			{0xDBu, 0x04u},
			{0xDCu, 0x11u},
			{0xDFu, 0x01u},
			{0x03u, 0x80u},
			{0x05u, 0x11u},
			{0x0Eu, 0x22u},
			{0x17u, 0x08u},
			{0x19u, 0x20u},
			{0x1Du, 0x11u},
			{0x1Eu, 0x22u},
			{0x1Fu, 0x10u},
			{0x21u, 0x04u},
			{0x22u, 0x88u},
			{0x23u, 0x01u},
			{0x24u, 0x10u},
			{0x26u, 0x02u},
			{0x27u, 0x14u},
			{0x28u, 0x04u},
			{0x2Fu, 0x50u},
			{0x31u, 0x10u},
			{0x32u, 0x82u},
			{0x33u, 0x04u},
			{0x36u, 0x0Au},
			{0x37u, 0x10u},
			{0x38u, 0x91u},
			{0x39u, 0x08u},
			{0x3Bu, 0x80u},
			{0x3Du, 0x20u},
			{0x3Fu, 0x09u},
			{0x58u, 0x04u},
			{0x5Au, 0xA0u},
			{0x5Bu, 0x01u},
			{0x5Cu, 0x40u},
			{0x5Du, 0x20u},
			{0x67u, 0x40u},
			{0x87u, 0x40u},
			{0x8Bu, 0x80u},
			{0x90u, 0xC1u},
			{0x92u, 0xA0u},
			{0x95u, 0x08u},
			{0x97u, 0x01u},
			{0x98u, 0x04u},
			{0x9Bu, 0x09u},
			{0x9Du, 0x10u},
			{0x9Fu, 0x14u},
			{0xA1u, 0x10u},
			{0xA3u, 0x04u},
			{0xA6u, 0x80u},
			{0xABu, 0x01u},
			{0xC0u, 0x58u},
			{0xC2u, 0xA0u},
			{0xC4u, 0x20u},
			{0xCAu, 0xC4u},
			{0xCCu, 0xEFu},
			{0xCEu, 0xEFu},
			{0xD6u, 0x3Fu},
			{0xD8u, 0x80u},
			{0x0Bu, 0x02u},
			{0x0Fu, 0x10u},
			{0x6Bu, 0x02u},
			{0xC2u, 0x60u},
			{0xDAu, 0x40u},
			{0x0Fu, 0x08u},
			{0x9Fu, 0x02u},
			{0xABu, 0x01u},
			{0xAFu, 0x10u},
			{0xC2u, 0x80u},
			{0xE8u, 0x10u},
			{0xECu, 0x20u},
			{0x87u, 0x02u},
			{0x9Fu, 0x02u},
			{0xABu, 0x04u},
			{0xE6u, 0x40u},
			{0xECu, 0x20u},
			{0x01u, 0x80u},
			{0x04u, 0x08u},
			{0x07u, 0x08u},
			{0x0Bu, 0x02u},
			{0x8Fu, 0x01u},
			{0xC0u, 0x07u},
			{0xC2u, 0x02u},
			{0xE2u, 0x02u},
			{0x0Cu, 0x40u},
			{0xB3u, 0x08u},
			{0xB4u, 0x04u},
			{0xB5u, 0x80u},
			{0xC2u, 0x01u},
			{0xEAu, 0x08u},
			{0xEEu, 0x03u},
			{0x88u, 0x40u},
			{0x98u, 0x40u},
			{0xE2u, 0x01u},
			{0x01u, 0x0Au},
			{0x10u, 0x0Au},
			{0x12u, 0x0Au},
		};



		CYPACKED typedef struct {
			void CYFAR *address;
			uint16 size;
		} CYPACKED_ATTR cfg_memset_t;

		static const cfg_memset_t CYCODE cfg_memset_list[] = {
			/* address, size */
			{(void CYFAR *)(CYDEV_UDB_P0_U0_BASE), 2048u},
			{(void CYFAR *)(CYDEV_UDB_DSI0_BASE), 2048u},
		};

		uint8 CYDATA i;

		/* Zero out critical memory blocks before beginning configuration */
		for (i = 0u; i < (sizeof(cfg_memset_list)/sizeof(cfg_memset_list[0])); i++)
		{
			const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
			CYMEMZERO(ms->address, (size_t)(uint32)(ms->size));
		}

		cfg_write_bytes32(cy_cfg_addr_table, cy_cfg_data_table);

		/* HSIOM Starting address: CYDEV_HSIOM_BASE */
		CY_SET_REG32((void *)(CYDEV_HSIOM_BASE), 0x0000000Au);
		CY_SET_REG32((void *)(CYREG_HSIOM_PORT_SEL1), 0x08000000u);
		CY_SET_REG32((void *)(CYREG_HSIOM_PORT_SEL3), 0x0000EE99u);
		CY_SET_REG32((void *)(CYREG_HSIOM_PORT_SEL4), 0x0A000000u);
		CY_SET_REG32((void *)(CYREG_HSIOM_PORT_SEL6), 0x00EE0000u);

		/* UDB_PA_0 Starting address: CYDEV_UDB_PA0_BASE */
		CY_SET_REG32((void *)(CYDEV_UDB_PA0_BASE), 0x00990000u);

		/* UDB_PA_1 Starting address: CYDEV_UDB_PA1_BASE */
		CY_SET_REG32((void *)(CYDEV_UDB_PA1_BASE), 0x00990000u);

		/* UDB_PA_2 Starting address: CYDEV_UDB_PA2_BASE */
		CY_SET_REG32((void *)(CYDEV_UDB_PA2_BASE), 0x00990000u);

		/* UDB_PA_4 Starting address: CYDEV_UDB_PA4_BASE */
		CY_SET_REG32((void *)(CYDEV_UDB_PA4_BASE), 0x00990000u);

		/* UDB_PA_5 Starting address: CYDEV_UDB_PA5_BASE */
		CY_SET_REG32((void *)(CYDEV_UDB_PA5_BASE), 0x00990000u);

		/* UDB_PA_7 Starting address: CYDEV_UDB_PA7_BASE */
		CY_SET_REG32((void *)(CYDEV_UDB_PA7_BASE), 0x00990000u);

		/* UDB_P0_U0_CFG24 Starting address: CYDEV_UDB_P0_U0_CFG24 */
		CY_SET_REG32((void *)(CYREG_UDB_P0_U0_CFG24), 0x84000404u);

		/* INT_SELECT Starting address: CYDEV_CPUSS_INT_SEL */
		CY_SET_REG32((void *)(CYREG_CPUSS_INT_SEL), 0x00000001u);

		/* INT_CONFIG Starting address: CYDEV_UDB_INT_CFG */
		CY_SET_REG32((void *)(CYREG_UDB_INT_CFG), 0x00000001u);

		/* Enable UDB array and digital routing */
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDB_WAIT_CFG, (uint8)((CY_GET_XTND_REG8((void *)CYREG_UDB_UDB_WAIT_CFG) & 0xC3u) | 0x14u));
		CY_SET_XTND_REG8((void *)CYREG_UDB_UDB_BANK_CTL, (uint8)(CY_GET_XTND_REG8((void *)CYREG_UDB_UDB_BANK_CTL) | 0x16u));
	}

	/* Perform second pass device configuration. These items must be configured in specific order after the regular configuration is done. */
	/* IOPINS0_0 Starting address: CYDEV_GPIO_PRT0_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT0_BASE), 0x0000004Eu);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT0_PC), 0x00080491u);

	/* IOPINS0_1 Starting address: CYDEV_GPIO_PRT1_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT1_BASE), 0x000000C0u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT1_PC), 0x00586D80u);

	/* IOPINS0_2 Starting address: CYDEV_GPIO_PRT2_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT2_BASE), 0x00000021u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT2_PC2), 0x00000021u);

	/* IOPINS0_3 Starting address: CYDEV_GPIO_PRT3_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT3_BASE), 0x00000002u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT3_PC), 0x00000DB1u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT3_PC2), 0x00000002u);

	/* IOPINS0_4 Starting address: CYDEV_GPIO_PRT4_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT4_BASE), 0x000000C0u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT4_PC), 0x00580000u);

	/* IOPINS0_5 Starting address: CYDEV_GPIO_PRT5_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT5_BASE), 0x00000008u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT5_PC), 0x00048400u);

	/* IOPINS0_6 Starting address: CYDEV_GPIO_PRT6_BASE */
	CY_SET_REG32((void *)(CYDEV_GPIO_PRT6_BASE), 0x00000030u);
	CY_SET_REG32((void *)(CYREG_GPIO_PRT6_PC), 0x00024000u);


	/* Setup clocks based on selections from Clock DWR */
	ClockSetup();

	/* Perform basic analog initialization to defaults */
	AnalogSetDefault();

}
