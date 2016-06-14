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
 *   Vector related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"
#include "thread_pkt.h"


#if DRV_TIMER_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_VECTOR_Timer2
 * DESCRIPTION:
 *   Timer2 ISR.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_VECTOR_Timer2(void) __interrupt(INTERRUPT_TIMER2)
{
    /* clear timeout flag */
    DRV_TIMER_ClearTimeoutFlag();

    /* update tick counter */
	DRV_TIMER_UpdateTick();
}

#endif

#if DRV_USB_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_VECTOR_UserUSB
 * DESCRIPTION:
 *   UserUSB ISR.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_VECTOR_UserUSB(void) __interrupt(INTERRUPT_UserUSB)
{
  #if PKT_SUPPORT
	thread_Pkt_Notify(DRV_USB_GetInterruptSource());
  #endif
}

#endif

