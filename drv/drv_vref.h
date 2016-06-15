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
 *   VREF(Voltage Reference) driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_VREF_H
#define __DRV_VREF_H


#if DRV_VREF_SUPPORT

#define REF0CN_REFSL_BIT    3   /* Voltage Reference Select              */
#define REF0CN_TEMPE_BIT    2   /* Temperature Sensor Enable             */
#define REF0CN_BIASE_BIT    1   /* Internal Analog Bias Generator Enable */
#define REF0CN_REFBE_BIT    0   /* On-chip Reference Buffer Enable       */

/* VREF related timing */
#define VREF_TurnOnTime     2000    /* us, C=0.1uF||4.7uF */
#define VREF_Voltage        24400   /* 2.44V, zoom-in'd by 10000 */

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_VREF_Init
 * DESCRIPTION:
 *   VREF init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_VREF_Init()                                                     \
    do {                                                                    \
        /* enable:                                                          \
         *  -> internal temperature sensor                                  \
         *  -> internal analog bias generator                               \
         *  -> on-chip reference buffer                                     \
         */                                                                 \
        REF0CN = ( (1<<REF0CN_TEMPE_BIT)                                    \
                 | (1<<REF0CN_BIASE_BIT)                                    \
                 | (1<<REF0CN_REFBE_BIT) );                                 \
                                                                            \
        /* wait for VREF ready */                                           \
        DRV_CPU_DelayUs(VREF_TurnOnTime);                                   \
    } while (0)

#endif


#endif /* __DRV_VREF_H */

