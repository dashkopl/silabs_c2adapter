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
 *   Application related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"
#include "apl.h"


#if 1

#define Slope_ZoomIn_ShiftBits      (8)
#define GET_SLOPE_DELTA(_slope)     (CFG(_slope) - CFG(DDM_EVB_TEMP_Slope))

static UINT16 apl_ddm_Calibrate
(
    IN UINT16   vRawADC,
    IN UINT8    vSlopeDelta,
    IN BOOL     bSignDDM
)
{
    SINT64  vTmpData;
    SINT32  vTmpSlope, vTmpOffset;

    vTmpSlope  = (SINT32)CFG_GETO32(DDM_EVB_TEMP_Slope,  vSlopeDelta);
    vTmpOffset = (SINT32)CFG_GETO32(DDM_EVB_TEMP_Offset, vSlopeDelta);

    vTmpData = (((SINT64)vTmpSlope * vRawADC) >> Slope_ZoomIn_ShiftBits)
                + vTmpOffset;

    /* limit the calibrated value to 16-bit formatting,
     *  to strictly follow MSA Standard.
     */
    return (UINT16)(bSignDDM? LIMIT_S16(vTmpData): LIMIT_U16(vTmpData));
}

static UINT16 apl_ddm_GetEVBTemp(void)
{
    UINT16  vRawADC;

    /* get raw ADC value, and record it */
    vRawADC = (UINT16)DRV_ADC_Sample(ADC(ADC_EVB_TEMP));
    CFG_SET(DDM_ADC_EVB_TEMP, vRawADC);

    /* calibration */
    return apl_ddm_Calibrate(vRawADC,
                             GET_SLOPE_DELTA(DDM_EVB_TEMP_Slope),
                             TRUE);
}

static UINT16 apl_ddm_GetEVBVCC(void)
{
    UINT16  vRawADC;

    /* get raw ADC value, and record it */
    vRawADC = (UINT16)DRV_ADC_Sample(ADC(ADC_EVB_VCC));
    CFG_SET(DDM_ADC_EVB_VCC, vRawADC);

    /* calibration */
    return apl_ddm_Calibrate(vRawADC,
                             GET_SLOPE_DELTA(DDM_EVB_VCC_Slope),
                             FALSE);
}

static UINT16 apl_ddm_GetEVBVBUF(void)
{
    UINT16  vRawADC;

    /* get raw ADC value, and record it */
    vRawADC = (UINT16)DRV_ADC_Sample(ADC(ADC_EVB_VBUF));
    CFG_SET(DDM_ADC_EVB_VBUF, vRawADC);

    /* calibration */
    return apl_ddm_Calibrate(vRawADC,
                             GET_SLOPE_DELTA(DDM_EVB_VBUF_Slope),
                             FALSE);
}

#endif


/******************************************************************************
 * FUNCTION NAME:
 *   APL_Entry
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void APL_Entry(void)
{
    /* PWM_VBUF */
    DRV_PCA_Write(PCA(PWM_VBUF), CFG_GET(RT_EVB_CTRL_PWM_VBUF));

	/* DDM */
	CFG_SET_DDM(DDM_EVB_TEMP, apl_ddm_GetEVBTemp());
	CFG_SET_DDM(DDM_EVB_VCC,  apl_ddm_GetEVBVCC());
	CFG_SET_DDM(DDM_EVB_VBUF, apl_ddm_GetEVBVBUF());

    /* RT_EVB_STAT */
  #if 1
    /* EVB Temperature */
    if (((SINT16)CFG_GET(DDM_EVB_TEMP) > (SINT16)CFG_GET(DDM_EVB_TEMP_Max)) ||
        ((SINT16)CFG_GET(DDM_EVB_TEMP) < (SINT16)CFG_GET(DDM_EVB_TEMP_Min)))
    {
        CFG_SET(RT_EVB_STAT_EVB_TEMP_Ready, LOW);
    }
    else
    {
        CFG_SET(RT_EVB_STAT_EVB_TEMP_Ready, HIGH);
    }

    /* EVB VCC */
    if (((UINT16)CFG_GET(DDM_EVB_VCC) > (UINT16)CFG_GET(DDM_EVB_VCC_Max)) ||
        ((UINT16)CFG_GET(DDM_EVB_VCC) < (UINT16)CFG_GET(DDM_EVB_VCC_Min)))
    {
        CFG_SET(RT_EVB_STAT_EVB_VCC_Ready, LOW);
    }
    else
    {
        CFG_SET(RT_EVB_STAT_EVB_VCC_Ready, HIGH);
    }

    /* EVB VBUF */
    if (((UINT16)CFG_GET(DDM_EVB_VBUF) > (UINT16)CFG_GET(DDM_EVB_VBUF_Max)) ||
        ((UINT16)CFG_GET(DDM_EVB_VBUF) < (UINT16)CFG_GET(DDM_EVB_VBUF_Min)))
    {
        CFG_SET(RT_EVB_STAT_EVB_VBUF_Ready, LOW);
    }
    else
    {
        CFG_SET(RT_EVB_STAT_EVB_VBUF_Ready, HIGH);
    }

    /* EVB Global Ready */
    if ((CFG_GET(RT_EVB_STAT_EVB_TEMP_Ready) == HIGH) &&
        (CFG_GET(RT_EVB_STAT_EVB_VCC_Ready)  == HIGH) &&
        (CFG_GET(RT_EVB_STAT_EVB_VBUF_Ready) == HIGH))
    {
        CFG_SET(RT_EVB_STAT_Global_Ready, HIGH);
    }
    else
    {
        CFG_SET(RT_EVB_STAT_Global_Ready, LOW);
    }
  #endif
}


/******************************************************************************
 * FUNCTION NAME:
 *   APL_InitializeState
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void APL_Init(void)
{
    /* copy initial setting */
    CFG_SET(RT_EVB_CTRL, CFG_GET(INIT_RT_EVB_CTRL));

    /* enable PWM_VBUF output */
    DRV_PCA_Write(PCA(PWM_VBUF), CFG_GET(RT_EVB_CTRL_PWM_VBUF));
    DRV_CPU_DelayMs(10);
    DRV_IO_Write(IO(IO_VBUF_OEn), LOW);
}

