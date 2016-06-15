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
 *   ADC driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_ADC_H
#define __DRV_ADC_H


#if DRV_ADC_SUPPORT

/* ADC related timing */
#define ADC_SettlingTime    200 /* us, t = ln(2^n/SA) * R_total * C_sample */
#define ADC_SAR_ConvClock   10  /* conversion time in SAR clocks */

#if defined(__C8051F320__)

/* ADC positive channel */
#define ADC_CHP_P1_0        0x00
#define ADC_CHP_P1_1        0x01
#define ADC_CHP_P1_2        0x02
#define ADC_CHP_P1_3        0x03
#define ADC_CHP_P1_4        0x04
#define ADC_CHP_P1_5        0x05
#define ADC_CHP_P1_6        0x06
#define ADC_CHP_P1_7        0x07
#define ADC_CHP_P2_0        0x08
#define ADC_CHP_P2_1        0x09
#define ADC_CHP_P2_2        0x0A
#define ADC_CHP_P2_3        0x0B
#define ADC_CHP_P2_4        0x0C
#define ADC_CHP_P2_5        0x0D
#define ADC_CHP_P2_6        0x0E
#define ADC_CHP_P2_7        0x0F
#define ADC_CHP_P3_0        0x10
#define ADC_CHP_TEMP        0x1E
#define ADC_CHP_VDD         0x1F

/* ADC negative channel */
#define ADC_CHN_P1_0        0x00
#define ADC_CHN_P1_1        0x01
#define ADC_CHN_P1_2        0x02
#define ADC_CHN_P1_3        0x03
#define ADC_CHN_P1_4        0x04
#define ADC_CHN_P1_5        0x05
#define ADC_CHN_P1_6        0x06
#define ADC_CHN_P1_7        0x07
#define ADC_CHN_P2_0        0x08
#define ADC_CHN_P2_1        0x09
#define ADC_CHN_P2_2        0x0A
#define ADC_CHN_P2_3        0x0B
#define ADC_CHN_P2_4        0x0C
#define ADC_CHN_P2_5        0x0D
#define ADC_CHN_P2_6        0x0E
#define ADC_CHN_P2_7        0x0F
#define ADC_CHN_P3_0        0x10
#define ADC_CHN_VREF        0x1E
#define ADC_CHN_GND         0x1F

#elif defined(__C8051F321__)

/* ADC positive channel */
#define ADC_CHP_P1_0        0x00
#define ADC_CHP_P1_1        0x01
#define ADC_CHP_P1_2        0x02
#define ADC_CHP_P1_3        0x03
#define ADC_CHP_P1_4        0x04
#define ADC_CHP_P1_5        0x05
#define ADC_CHP_P1_6        0x06
#define ADC_CHP_P1_7        0x07
#define ADC_CHP_P2_0        0x08
#define ADC_CHP_P2_1        0x09
#define ADC_CHP_P2_2        0x0A
#define ADC_CHP_P2_3        0x0B
#define ADC_CHP_P3_0        0x10
#define ADC_CHP_TEMP        0x1E
#define ADC_CHP_VDD         0x1F

/* ADC negative channel */
#define ADC_CHN_P1_0        0x00
#define ADC_CHN_P1_1        0x01
#define ADC_CHN_P1_2        0x02
#define ADC_CHN_P1_3        0x03
#define ADC_CHN_P1_4        0x04
#define ADC_CHN_P1_5        0x05
#define ADC_CHN_P1_6        0x06
#define ADC_CHN_P1_7        0x07
#define ADC_CHN_P2_0        0x08
#define ADC_CHN_P2_1        0x09
#define ADC_CHN_P2_2        0x0A
#define ADC_CHN_P2_3        0x0B
#define ADC_CHN_P3_0        0x10
#define ADC_CHN_VREF        0x1E
#define ADC_CHN_GND         0x1F

#else
 #error "Unsupported CPU!"
#endif

/* ADC average number */
#define ADC_AVGNO_1         0
#define ADC_AVGNO_2         1
#define ADC_AVGNO_4         2
#define ADC_AVGNO_8         3
#define ADC_AVGNO_16        4
#define ADC_AVGNO_32        5
#define ADC_AVGNO_64        6
#define ADC_AVGNO_128       7

#define _ADC_CH_P(_name)        COMBINE(ADC_CH_POS_, _name)
#define _ADC_CH_N(_name)        COMBINE(ADC_CH_NEG_, _name)
#define _ADC_CH_AVGNO(_name)    COMBINE(ADC_CH_AVGNO_, _name)
#define ADC(_name)              _ADC_CH_P(_name), _ADC_CH_N(_name), _ADC_CH_AVGNO(_name)

/* ADC channel definition */
#define DECLARE_ADC(_name, _PosCh, _NegCh, _AvgNO, _desc)           \
                                _ADC_CH_P(_name)     = (_PosCh),    \
                                _ADC_CH_N(_name)     = (_NegCh),    \
                                _ADC_CH_AVGNO(_name) = (_AvgNO),
typedef enum
{
#include "cfg_hw_def.h"
    ADC_CH_MAX
} ADC_CH_T;
#undef DECLARE_ADC

/* ADC value: 10-bit unsigned data */
#define DRV_ADC_Resolution      10
#define DRV_ADC_MaxValue        (SINT16)((1U<<DRV_ADC_Resolution)-1)
#define DRV_ADC_MinValue        (SINT16)(~((1U<<DRV_ADC_Resolution)-1))

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_ADC_Sample
 * DESCRIPTION:
 *   Sample ADC value.
 * PARAMETERS:
 *   vPositive : Positive channel;
 *   vNegative : Negative channel;
 *   vAvgNum   : ADC average number;
 * RETURN:
 *   Sampled ADC value.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
SINT16 DRV_ADC_Sample(UINT8 vPositive, UINT8 vNegative, UINT8 vAvgNum);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_ADC_Init
 * DESCRIPTION:
 *   ADC init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_ADC_Init(void);

#endif


#endif /* __DRV_ADC_H */

