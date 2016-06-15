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
 *   Extended stdio.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


/* stdio porting part */
#if 1
 #define __delayms(n)       DRV_CPU_DelayMs(n)
 #define __putchar(c)       DRV_UART_WriteByte(c)
 #define __getchar()        DRV_UART_ReadByte()
 #define __is_tx_empty()    DRV_UART_IsTxEmpty()
 #define __is_rx_empty()    DRV_UART_IsRxEmpty()
 #define __watchdog_kick()  DRV_WATCHDOG_Kick()
#endif


/* stdio low-level part */
#if 1

int _getchar(int timeout)
{
    if (timeout != NO_PENDING)
    {
        while (__is_rx_empty())
        {
            if ((timeout >= 0) && (timeout-- == 0))
            {
                break;
            }

            __delayms(1);
        }
    }

    return (__is_rx_empty()? -1 : __getchar());
}

#endif

