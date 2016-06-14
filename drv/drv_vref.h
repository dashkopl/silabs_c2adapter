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

