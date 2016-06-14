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
 *   Thread: LED related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


static OS_TCB   vTCB_LED;

/******************************************************************************
 * FUNCTION NAME:
 *   thread_LED_Entry
 * DESCRIPTION:
 *   LED Thread Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   OS_HANDLE
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
OS_HANDLE thread_LED_Entry(void)
{
    PT_BEGIN(&vTCB_LED);

    for (;;)
    {
      #if CFG_SUPPORT
        if (CFG_GET(RT_EVB_STAT_Global_Ready) == HIGH)
        {
            /* system running OK */
            DRV_IO_Write(IO(IO_LED_STATUS_OUT), LOW);
        }
        else
      #endif
        {
            /* system running abnormally */
            DRV_IO_Toggle(IO(IO_LED_STATUS_OUT));
        }

        OS_SLEEP_MS(&vTCB_LED, 100);
    }

    PT_END(&vTCB_LED);
}


/******************************************************************************
 * FUNCTION NAME:
 *   thread_LED_Init
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
void thread_LED_Init(void)
{
    PT_INIT(&vTCB_LED);
}

