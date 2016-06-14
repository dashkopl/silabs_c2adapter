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
 *   Thread: Idle related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"
#include "apl.h"


static OS_TCB   vTCB_Idle;

/******************************************************************************
 * FUNCTION NAME:
 *   thread_IDLE_Entry
 * DESCRIPTION:
 *   Idle Thread Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   OS_HANDLE
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
OS_HANDLE thread_IDLE_Entry(void)
{
    PT_BEGIN(&vTCB_Idle);

    for (;;)
    {
    	/* system entry */
        CFG_Entry();
        DRV_Entry();
        APL_Entry();

        OS_SLEEP_MS(&vTCB_Idle, 50);
    }

    PT_END(&vTCB_Idle);
}


/******************************************************************************
 * FUNCTION NAME:
 *   thread_IDLE_Init
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void thread_IDLE_Init(void)
{
    PT_INIT(&vTCB_Idle);

	/* system init */
    CFG_Init();
    DRV_Init();
    APL_Init();
}

