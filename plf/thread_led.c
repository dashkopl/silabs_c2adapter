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
            DRV_IO_Write(IO(IO_LED_1_OUT), HIGH);
            DRV_IO_Write(IO(IO_LED_2_OUT), LOW);
        }
        else
      #endif
        {
            /* system running abnormally */
            DRV_IO_Write(IO(IO_LED_1_OUT), LOW);
            DRV_IO_Write(IO(IO_LED_2_OUT), HIGH);
        }

        DRV_IO_Toggle(IO(IO_LED_STATUS_OUT));
        OS_SLEEP_MS(&vTCB_LED, 500);
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

