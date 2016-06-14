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
 *   Platform system start entry.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *   _fixupInit
 * DESCRIPTION:
 *   System FixUp Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   This is a post init after system is ready.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
static void _fixupInit(void)
{
    /* Globally enable Interrupt */
    DRV_INT_GlobalEnableInterrupt();

  #if DRV_USB_SUPPORT
	/* enable USB interface */
	DRV_USB_Enable();
  #endif
}


/******************************************************************************
 * FUNCTION NAME:
 *   main
 * DESCRIPTION:
 *   System entry of C file.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void main(void)
{
	/* previous init */
	DRV_PreInit();

    /* init protothread */
    OS_Init();

    /* fixup init */
    _fixupInit();

    /* start protothread (never return) */
    OS_Start();
}

