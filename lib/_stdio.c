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

