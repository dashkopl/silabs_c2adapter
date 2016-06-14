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
 *   CLI: Memory commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#define __CLI_INTERNAL
#include "cfg.h"
#include "drv.h"
#include "cli_porting.h"


#if CLI_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_Mem_Read
 * DESCRIPTION:
 *   CLI Command: Read memory data.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_Mem_Read(void)
{
    BOOL    bCode;
    UINT16  vAddr;
    UINT16  vCount;
    UINT16  vLoop;

    if ((CLI_vParam < 3) || (CLI_vParam > 4))
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    if (IsStrEqual(CLI_aParam[1], "code"))
    {
        bCode = TRUE;
    }
    else if (IsStrEqual(CLI_aParam[1], "xdata"))
    {
        bCode = FALSE;
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vAddr = (UINT16)strtoul(CLI_aParam[2], NULL, 0);

    if (CLI_vParam == 4)
    {
        vCount = (UINT16)strtoul(CLI_aParam[3], NULL, 0);
    }
    else
    {
        vCount = 1;
    }

    for (vLoop = 0; vLoop < vCount; vLoop++)
    {
        UINT16  vAddrLoop = vAddr+vLoop;

        if ((vLoop%16) == 0)
        {
            printf("\n\r %.4hX:", vAddrLoop);
        }
        else if ((vLoop%8) == 0)
        {
            printf(" -");
        }

        printf(" %.2bX", (bCode ? CODE_U8(vAddrLoop) : XDATA_U8(vAddrLoop)));
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_Mem_Write
 * DESCRIPTION:
 *   CLI Command: Memory write Data.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_Mem_Write(void)
{
    BOOL    bCode;
    UINT16  vAddr;
    UINT8   vCount;
    UINT8   vLoop;

    if (CLI_vParam < 4)
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    if (IsStrEqual(CLI_aParam[1], "code"))
    {
        bCode = TRUE;
    }
    else if (IsStrEqual(CLI_aParam[1], "xdata"))
    {
        bCode = FALSE;
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vAddr  = (UINT16)strtoul(CLI_aParam[2], NULL, 0);
    vCount = CLI_vParam - 3;

    for (vLoop = 0; vLoop < vCount; vLoop++)
    {
        UINT16  vAddrLoop = vAddr+vLoop;
        UINT8   vData = (UINT8)strtoul(CLI_aParam[3+vLoop], NULL, 0);

        if ((vLoop%16) == 0)
        {
            printf("\n\r %.4hX:", vAddrLoop);
        }
        else if ((vLoop%8) == 0)
        {
            printf(" -");
        }

        if (bCode)
        {
            EEPROM_MEMCPY(vAddrLoop, 1, &vData);
            printf(" %.2bX", CODE_U8(vAddrLoop));
        }
        else
        {
            XDATA_U8(vAddrLoop) = vData;
            printf(" %.2bX", XDATA_U8(vAddrLoop));
        }
    }
}

#endif

