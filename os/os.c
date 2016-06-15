/******************************************************************************
 *
 * COPYRIGHT:
 *   Copyright (c) 2016    PANDA(yaxi1984@gmail.com)    All rights reserved.
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA 02111-1307 USA
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

