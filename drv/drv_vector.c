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

