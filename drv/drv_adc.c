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
 *   ADC driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_ADC_SUPPORT

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
SINT16 DRV_ADC_Sample(UINT8 vPositive, UINT8 vNegative, UINT8 vAvgNum)
{
    SINT16  vAdcSum;
    UINT8   vLoop;

    /* select positive/negative channel */
    AMX0P = vPositive;
    AMX0N = vNegative;

    /* wait for ADC input stable */
    DRV_CPU_DelayUs(ADC_SettlingTime);

    /* sampling */
    vAdcSum = 0;
    for (vLoop = (1<<vAvgNum); vLoop > 0; vLoop--)
    {
        /* clear the ADC last converted flag */
        AD0INT = 0;

        /* start a new ADC converting */
        AD0BUSY = 1;

        /* waiting for ADC converted */
        while (!AD0INT)
        {}

        /* sum the ADC result */
        vAdcSum += (SINT16)(((UINT16)ADC0H<<8)|ADC0L);
    }

    /* calculate the averaged value */
    return (vAdcSum>>vAvgNum);
}


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
void DRV_ADC_Init(void)
{
  /* AD0SC value */
  #define AD0SC_VAL (((CORE_CLOCK*10/DRV_ADC_SAR_RATE/1000/ADC_SAR_ConvClock+5)/10-1)&0x1F)

    /* default:
     *  positive channel: temperature sensor;
     *  negative channel: GND;
     */
    AMX0P = ADC_CHP_TEMP;
    AMX0N = ADC_CHN_GND;

    /* ADC control:
     *  right justify;
     *  ADC start-of-conversion source is write of '1' to ADC0BUSY;
     *  clear ADC flag;
     *  enable ADC;
     */
    ADC0CF = (AD0SC_VAL<<3) | (0<<2);
    ADC0CN = 0x80;
}

#endif

