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
 *   CLI: C2 Master commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#define __CLI_INTERNAL
#include "cfg.h"
#include "drv.h"
#include "cli_porting.h"


#if (CLI_SUPPORT && DRV_C2M_SUPPORT)

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_Reset
 * DESCRIPTION:
 *   CLI Command: C2 Master Reset Target Device.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_Reset(void)
{
    printf("\n\rC2M Reset Target Device ... ");
    printf(DRV_C2M_Reset()?"Done.":"Fail.");
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_Probe
 * DESCRIPTION:
 *   CLI Command: C2 Master Probe Target Device ID.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_Probe(void)
{
    printf("\n\rC2M Probe Target Device ID ... ");
    printf("%.8lX", DRV_C2M_Probe());
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_ChipErase
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Chip Erase.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_ChipErase(void)
{
    printf("\n\rC2M Target Device Chip Erase ... ");
    printf(DRV_C2M_ChipErase()?"Done.":"Fail.");
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_PageErase
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Page Erase.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_PageErase(void)
{
    UINT8   vPageNo;

    if (CLI_vParam != 2)
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vPageNo = (UINT8)strtoul(CLI_aParam[1], NULL, 0);

    printf("\n\rC2 Master Page Erase: page_no=0x%.2bX ... ", vPageNo);
    if (DRV_C2M_PageErase(vPageNo))
    {
        printf("Done.");
    }
    else
    {
        printf("Fail.");
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_ReadFlash
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Read Flash.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_ReadFlash(void)
{
    UINT16          vAddr;
    UINT8           vReadLen;
    UINT8 SEG_XDATA aReadBuf[128];

    memset(aReadBuf, 0, sizeof(aReadBuf));

    if (CLI_vParam == 2)
    {
        vReadLen = 1;
    }
    else if (CLI_vParam == 3)
    {
        vReadLen = (UINT8)strtoul(CLI_aParam[2], NULL, 0);
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vAddr = (UINT16)strtoul(CLI_aParam[1], NULL, 0);
    if (vReadLen > sizeof(aReadBuf))
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    printf("\n\rC2 Master Read Flash: addr=0x%.4hX, len=0x%.2bX ... ",
           vAddr, vReadLen);
    if (DRV_C2M_FlashRead(aReadBuf, vAddr, vReadLen))
    {
        UINT8   vLoop;

        printf("Done.");

        for (vLoop = 0; vLoop < vReadLen; vLoop++)
        {
            if ((vLoop%16) == 0)
            {
                printf("\n\r %.4hX:", vAddr+vLoop);
            }
            else if ((vLoop%8) == 0)
            {
                printf(" -");
            }

            printf(" %.2bX", aReadBuf[vLoop]);
        }
    }
    else
    {
        printf("Fail.");
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_WriteFlash
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Write Flash.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_WriteFlash(void)
{
    UINT8           vAddr;
    UINT8           vDataLen;
    UINT8 SEG_XDATA aWriteBuf[CLI_CMD_MAX_PARAM];
    UINT8           vLoop;

    memset(aWriteBuf, 0, sizeof(aWriteBuf));

    if (CLI_vParam >= 3)
    {
        vDataLen = CLI_vParam - 2;
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vAddr = (UINT8)strtoul(CLI_aParam[1], NULL, 0);
    if (vDataLen > sizeof(aWriteBuf))
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    for (vLoop = 0; vLoop < vDataLen; vLoop++)
    {
        aWriteBuf[vLoop] = (UINT8)strtoul(CLI_aParam[2+vLoop], NULL, 0);
    }

    printf("\n\rC2 Master Write Flash: addr=0X%.4hX, len=0x%.2bX ... ",
           vAddr, vDataLen);
    if (DRV_C2M_FlashWrite(vAddr, aWriteBuf, vDataLen))
    {
        printf("Done.");
    }
    else
    {
        printf("Fail.");
    }

    printf("\n\rData:");
    for (vLoop = 0; vLoop < vDataLen; vLoop++)
    {
        printf(" %.2bX", aWriteBuf[vLoop]);
    }
}

#endif

