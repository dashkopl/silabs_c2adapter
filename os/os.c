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
 *   OS related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"
#include "cfg_thread_def.h"


/* thread list */
#define DECLARE_THREAD(entry, init, desc)   { entry, init },
static struct
{
    PT_FUNC         pEntry;
    PT_INIT_FUNC    pInit;
} SEG_CODE aThreadList[] =
{
#include "cfg_thread_def.h"
};
#undef DECLARE_THREAD

/******************************************************************************
 * FUNCTION NAME:
 *   OS_Start
 * DESCRIPTION:
 *   OS Start Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 ******************************************************************************/
void OS_Start(void)
{
    for (;;)
    {
        UINT8   i;

        for (i = 0; i < COUNT_OF(aThreadList); i++)
        {
            aThreadList[i].pEntry();
        }
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   OS_Init
 * DESCRIPTION:
 *   OS Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 ******************************************************************************/
void OS_Init(void)
{
    UINT8   i;

    for (i = 0; i < COUNT_OF(aThreadList); i++)
    {
        aThreadList[i].pInit();
    }
}

