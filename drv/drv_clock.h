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
 *   Clock related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_CLOCK_H
#define __DRV_CLOCK_H


#if DRV_CLOCK_SUPPORT

#if (CORE_CLOCK != 24000000UL)
 #error "Unsupported Core Clock!"
#endif

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_CLOCK_Init
 * DESCRIPTION:
 *   Init clock.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.4.26        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_CLOCK_Init()                                                    \
    do {                                                                    \
        /* enable internal oscillator (12MHz) */                            \
        OSCICN = 0x83;                                                      \
                                                                            \
        /* wait for internal osciallator ready */                           \
        while (READ_BIT(OSCICN,6) == 0)                                     \
        {}                                                                  \
                                                                            \
        /* clock multiplier: (48MHz)                                        \
         *  source: internal oscillator (12MHz);                            \
         */                                                                 \
        CLKMUL  = 0x80;                                                     \
        DRV_CPU_DelayUs(5); /* wait for initialization */                   \
        CLKMUL |= 0xC0;                                                     \
        while (READ_BIT(CLKMUL,5) == 0)                                     \
        {}                                                                  \
                                                                            \
        /* clock select:                                                    \
         *  core clock: 4 x clock multiplier / 2;                           \
         *  USB  clock: 4 x clock multiplier;                               \
         */                                                                 \
        CLKSEL = 0x02;                                                      \
                                                                            \
        /* enable flash one-shot */                                         \
        FLSCL = 0x80;                                                       \
   } while (0)

#endif


#endif /* __DRV_CLOCK_H */

