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
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_CPU_DelayUs
 * DESCRIPTION:
 *   CPU delay microseconds.
 * PARAMETERS:
 *   vUsec : How many microseconds to delay, 1~65535 us.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_CPU_DelayUs(UINT16 vUsec)
{
    NOP(); NOP(); NOP();

    while (--vUsec)
    {
      #if (CORE_CLOCK == 24000000UL)
		NOP(); NOP(); NOP(); NOP(); NOP();
		NOP(); NOP(); NOP(); NOP(); NOP();
		NOP(); NOP(); NOP(); NOP(); NOP();
		NOP(); NOP(); NOP();
      #else
        #error "Unsupported Core Clock!"
      #endif
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_CPU_DelayMs
 * DESCRIPTION:
 *   CPU delay milliseconds.
 * PARAMETERS:
 *   vMsec : How many milliseconds to delay, 0~65535 ms.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_CPU_DelayMs(UINT16 vMsec)
{
  #if DRV_TIMER_SUPPORT
    if (DRV_INT_IsGlobalInterruptEnable())
    {
        UINT64  vStopTick = DRV_TIMER_GetTick() + vMsec/DRV_TIMER_INTERVAL;

        while (DRV_TIMER_GetTick() < vStopTick)
        {
          #if DRV_WATCHDOG_SUPPORT
            DRV_WATCHDOG_Kick();
          #endif
        }
    }
    else
  #endif
    {
    	while (vMsec--)
    	{
          #if DRV_WATCHDOG_SUPPORT
    		DRV_WATCHDOG_Kick();
          #endif

    		DRV_CPU_DelayUs(1000);
    	}
    }
}

