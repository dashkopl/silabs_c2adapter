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

#ifndef __DRV_WATCHDOG_H
#define __DRV_WATCHDOG_H


#if DRV_WATCHDOG_SUPPORT

#if (DRV_PCA_SOURCE_CLOCK != PCA_CLK_T0_OVERFLOW)
 #error "Watchdog can only support T0 overflow as PCA clock!"
#endif

#define TIMER0_INTERVAL     100 /* us */
#define TIMER0_INIT()       do {                                                            \
                                /* timer 0:                                                 \
                                 *  clock source: system clock /48;                         \
                                 *  mode: 8-bit auto-reload;                                \
                                 *  gate: controlled by TR0;                                \
                                 */                                                         \
                                CKCON = (CKCON&0xF8) | (0x2<<0);                            \
                                TMOD  = (TMOD&0xF0)  | (0x2<<0);                            \
                                TH0   = (256 - CORE_CLOCK/1000000UL*TIMER0_INTERVAL/48);    \
                                TR0   = 1; /* enable timer 0 */                             \
                            } while (0)
#define WATCHDOG_RELOAD_VAL (DRV_WATCHDOG_TIMEOUT*1000UL/256/TIMER0_INTERVAL)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_WATCHDOG_Kick
 * DESCRIPTION:
 *   Kick watchdog timer, to prevent watchdog timeout.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_WATCHDOG_Kick()     PCA0CPH4 = 0x00 /* kick watchdog */

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_WATCHDOG_Enable
 * DESCRIPTION:
 *   Enable watchdog timer.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_WATCHDOG_Enable()                                               \
    do {                                                                    \
        /* init timer 0 */                                                  \
        TIMER0_INIT();                                                      \
                                                                            \
        /* set watchdog reload value */                                     \
        PCA0CPL4 = WATCHDOG_RELOAD_VAL;                                     \
                                                                            \
        /* enable watchdog */                                               \
        PCA0MD |= 0x40;                                                     \
                                                                            \
        /* kick watchdog */                                                 \
        DRV_WATCHDOG_Kick();                                                \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_WATCHDOG_Disable
 * DESCRIPTION:
 *   Disable watchdog timer.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_WATCHDOG_Disable()                                              \
    do {                                                                    \
        PCA0MD &= ~0x40;            /* PCA watchdog timer disabled */       \
        PCA0MD  = 0x00;                                                     \
    } while (0)

#else

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_WATCHDOG_Kick
 * DESCRIPTION:
 *   Kick watchdog timer, to prevent watchdog timeout.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_WATCHDOG_Kick()         NOP()

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_WATCHDOG_Enable
 * DESCRIPTION:
 *   Enable watchdog timer.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_WATCHDOG_Enable()       /* do nothing */

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_WATCHDOG_Disable
 * DESCRIPTION:
 *   Disable watchdog timer.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_WATCHDOG_Disable()       /* do nothing */

#endif


#endif /* __DRV_WATCHDOG_H */

