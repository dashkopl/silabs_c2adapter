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
 *   Timer driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_TIMER_H
#define __DRV_TIMER_H


#if DRV_TIMER_SUPPORT

#ifdef _DRV_TIMER_INTERNAL_
 #define _DRV_TIMER_EXTERN_   /* empty */
#else
 #define _DRV_TIMER_EXTERN_   extern
#endif

/* timer reload value */
#define DRV_TIMER_ReloadValue   (65536UL - DRV_TIMER_INTERVAL*CORE_CLOCK/1000)
#if (DRV_TIMER_ReloadValue < 0)
  #error "Invalid timer reload value!"
#endif

/* clear timer timeout flag */
#define DRV_TIMER_ClearTimeoutFlag()    do { TF2H = 0; } while (0)

/* =TRUE, timer is timeout; else, not timeout */
#define DRV_TIMER_IsTimeout()           (TF2H)

/* reload timer init value */
#define DRV_TIMER_Reload()                                              \
    do {                                                                \
        TMR2L = TMR2RLL = ((DRV_TIMER_ReloadValue >> 0) & 0xFF);        \
        TMR2H = TMR2RLH = ((DRV_TIMER_ReloadValue >> 8) & 0xFF);        \
    } while (0)

/* real-time system tick counter */
_DRV_TIMER_EXTERN_ volatile UINT64  vTickCount;

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_TIMER_GetTick
 * DESCRIPTION:
 *   Get current tick counter.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   Current tick counter.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_TIMER_GetTick()         (vTickCount)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_TIMER_UpdateTick
 * DESCRIPTION:
 *   Update tick counter, every time update 1 tick.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_TIMER_UpdateTick()      do { vTickCount++; } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_TIMER_Enable
 * DESCRIPTION:
 *   Timer enable.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_TIMER_Enable()                                              \
    do {                                                                \
        DRV_TIMER_Reload();             /* reload timer */              \
        DRV_TIMER_ClearTimeoutFlag();   /* clear timeout flag */        \
        TR2 = 1;                        /* start timer */               \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_TIMER_Init
 * DESCRIPTION:
 *   Timer disable.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_TIMER_Disable()                                             \
    do {                                                                \
        TR2 = 0;                        /* stop timer */                \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_TIMER_Init
 * DESCRIPTION:
 *   Timer init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_TIMER_Init()                                                \
    do {                                                                \
        SET_BIT(CKCON, 4);  /* timer 2 clock use TMR2CN setting */      \
        TMR2CN = 0x00;      /* 16-bit auto-reload,                      \
                             * clock source: CORE_CLOCK,                \
                             * clear timer 2 overflow flag,             \
                             * disable Timer 2.                         \
                             */                                         \
        DRV_TIMER_Enable(); /* enable timer */                          \
        PT2 = 0;            /* force timer interrupt to low priority */ \
        ET2 = 1;            /* enable timer interrupt */                \
        vTickCount = 0;     /* reset system tick counter */             \
    } while (0)

#endif


#endif /* __DRV_TIMER_H */

