/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016      CreaLights Inc.      All rights reserved.
 *
 *   This is unpublished proprietary source code of CreaLights Inc.
 *   The copyright notice above does not evidence any actual or intended
 *   publication of such source code.
 *
 * DESCRIPTION:
 *   Driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#define _DRV_TIMER_INTERNAL_
#include "cfg.h"
#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_Init
 * DESCRIPTION:
 *   Driver init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_Init(void)
{
	DRV_VECTOR_Init();

  #if DRV_FLASH_SUPPORT
	DRV_FLASH_Init();
  #endif

  #if DRV_RESET_SUPPORT
	DRV_RESET_Init();
  #endif

  #if DRV_TIMER_SUPPORT
	DRV_TIMER_Init();
  #endif

  #if DRV_USB_SUPPORT
	DRV_USB_Init();
  #endif

  #if DRV_VREF_SUPPORT
	DRV_VREF_Init();
  #endif

  #if DRV_ADC_SUPPORT
	DRV_ADC_Init();
  #endif

  #if DRV_I2CM_SUPPORT
	DRV_I2CM_Init();
  #endif

  #if DRV_C2M_SUPPORT
	DRV_C2M_Init();
  #endif
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_Init
 * DESCRIPTION:
 *   Driver pre-init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_PreInit(void)
{
    /* disable all interrupt */
    DRV_INT_DisableAllInterrupt();

  #if DRV_CLOCK_SUPPORT
    DRV_CLOCK_Init();
  #endif

  #if DRV_IO_SUPPORT
	DRV_IO_Init();
  #endif

  #if DRV_UART_SUPPORT
    DRV_UART_Init();
  #endif

  #if DRV_PCA_SUPPORT
    DRV_PCA_Init();
  #endif

  #if DRV_WATCHDOG_SUPPORT
	DRV_WATCHDOG_Enable();
  #endif
}

