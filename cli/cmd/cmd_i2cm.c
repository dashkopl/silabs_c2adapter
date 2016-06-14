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
 *   CLI: I2C Master commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#define __CLI_INTERNAL
#include "cfg.h"
#include "drv.h"
#include "cli_porting.h"


#if (CLI_SUPPORT && DRV_I2CM_SUPPORT)

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_I2CM_Scan
 * DESCRIPTION:
 *   CLI Command: I2C Master Scan.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_I2CM_Scan(void)
{
    UINT16  vLoop;

    printf("\n\rAll I2C Slave(s):");
    for (vLoop = 0x00; vLoop < 0x100; vLoop += 2)
    {
        if (DRV_I2CM_Probe((UINT8)vLoop))
        {
            printf("\n\r -> 0x%.2bX", (UINT8)vLoop);
        }
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_I2CM_Read
 * DESCRIPTION:
 *   CLI Command: I2C Master Read.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_I2CM_Read(void)
{
    UINT8           vAddr;
    UINT32          vOffset;
    UINT8           vWriteLen;
    UINT8 SEG_XDATA aWriteBuf[4];
    UINT8           vReadLen;
    UINT8 SEG_XDATA aReadBuf[128];

    memset(aWriteBuf, 0, sizeof(aWriteBuf));
    memset(aReadBuf,  0, sizeof(aReadBuf));

    if (CLI_vParam == 4)
    {
        vReadLen = 1;
    }
    else if (CLI_vParam == 5)
    {
        vReadLen = (UINT8)strtoul(CLI_aParam[4], NULL, 0);
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vAddr   = (UINT8) strtoul(CLI_aParam[2], NULL, 0);
    vOffset = (UINT32)strtoul(CLI_aParam[3], NULL, 0);
    if (strcmp(CLI_aParam[1], "-o0") == 0)
    {
        vWriteLen = 0;
        aWriteBuf[0] = (UINT8)vOffset;
    }
    else if (strcmp(CLI_aParam[1], "-o8") == 0)
    {
        vWriteLen = 1;
        aWriteBuf[0] = (UINT8)vOffset;
    }
    else if (strcmp(CLI_aParam[1], "-o16") == 0)
    {
        vWriteLen = 2;
        aWriteBuf[0] = ((vOffset>>8) & 0xFF);
        aWriteBuf[1] = ((vOffset>>0) & 0xFF);
    }
    else if (strcmp(CLI_aParam[1], "-o24") == 0)
    {
        vWriteLen = 3;
        aWriteBuf[0] = ((vOffset>>16) & 0xFF);
        aWriteBuf[1] = ((vOffset>> 8) & 0xFF);
        aWriteBuf[2] = ((vOffset>> 0) & 0xFF);
    }
    else if (strcmp(CLI_aParam[1], "-o32") == 0)
    {
        vWriteLen = 4;
        aWriteBuf[0] = ((vOffset>>24) & 0xFF);
        aWriteBuf[1] = ((vOffset>>16) & 0xFF);
        aWriteBuf[2] = ((vOffset>> 8) & 0xFF);
        aWriteBuf[3] = ((vOffset>> 0) & 0xFF);
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }
    if (vReadLen > sizeof(aReadBuf))
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    printf("\n\rI2C Master Read: addr=0x%.2bX, offset=0x%lX(%bdB), len=0x%.2bX ... ",
           vAddr, vOffset, vWriteLen, vReadLen);
    if (DRV_I2CM_Stream(vAddr, vWriteLen, aWriteBuf, vReadLen, aReadBuf))
    {
        UINT8   vLoop;

        printf("Done.");

        for (vLoop = 0; vLoop < vReadLen; vLoop++)
        {
            if ((vLoop%16) == 0)
            {
                switch (vWriteLen)
                {
                    default:
                    case 0 : printf("\n\r ");                              break;
                    case 1 : printf("\n\r %.2bX:", (UINT8)vOffset+vLoop);  break;
                    case 2 : printf("\n\r %.4hX:", (UINT16)vOffset+vLoop); break;
                    case 3 :
                    case 4 : printf("\n\r %.8lX:", vOffset+vLoop);         break;
                }
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
 *   CMD_I2CM_Write
 * DESCRIPTION:
 *   CLI Command: I2C Master Write.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_I2CM_Write(void)
{
    UINT8           vAddr;
    UINT32          vOffset;
    UINT8           vOffsetLen;
    UINT8           vDataLen;
    UINT8 SEG_XDATA aWriteBuf[CLI_CMD_MAX_PARAM];
    UINT8           vLoop;

    memset(aWriteBuf, 0, sizeof(aWriteBuf));

    if (CLI_vParam >= 5)
    {
        vDataLen = CLI_vParam - 4;
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vAddr    = (UINT8) strtoul(CLI_aParam[2], NULL, 0);
    vOffset  = (UINT32)strtoul(CLI_aParam[3], NULL, 0);
    if (strcmp(CLI_aParam[1], "-o0") == 0)
    {
        vOffsetLen = 0;
    }
    else if (strcmp(CLI_aParam[1], "-o8") == 0)
    {
        vOffsetLen = 1;
        aWriteBuf[0] = (UINT8)vOffset;
    }
    else if (strcmp(CLI_aParam[1], "-o16") == 0)
    {
        vOffsetLen = 2;
        aWriteBuf[0] = ((vOffset>>8) & 0xFF);
        aWriteBuf[1] = ((vOffset>>0) & 0xFF);
    }
    else if (strcmp(CLI_aParam[1], "-o24") == 0)
    {
        vOffsetLen = 3;
        aWriteBuf[0] = ((vOffset>>16) & 0xFF);
        aWriteBuf[1] = ((vOffset>> 8) & 0xFF);
        aWriteBuf[2] = ((vOffset>> 0) & 0xFF);
    }
    else if (strcmp(CLI_aParam[1], "-o32") == 0)
    {
        vOffsetLen = 4;
        aWriteBuf[0] = ((vOffset>>24) & 0xFF);
        aWriteBuf[1] = ((vOffset>>16) & 0xFF);
        aWriteBuf[2] = ((vOffset>> 8) & 0xFF);
        aWriteBuf[3] = ((vOffset>> 0) & 0xFF);
    }
    else
    {
        printf("\n\rInvalid Parameter!");
        return;
    }
    if (vOffsetLen+vDataLen > sizeof(aWriteBuf))
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    for (vLoop = 0; vLoop < vDataLen; vLoop++)
    {
        aWriteBuf[vOffsetLen+vLoop] = (UINT8)strtoul(CLI_aParam[4+vLoop], NULL, 0);
    }

    printf("\n\rI2C Master Write: addr=0X%.2bX, offset=0x%lX(%bdB), len=0x%.2bX ... ",
           vAddr, vOffset, vOffsetLen, vDataLen);
    if (DRV_I2CM_Stream(vAddr, vOffsetLen+vDataLen, aWriteBuf, 0, NULL))
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
        printf(" %.2bX", aWriteBuf[vOffsetLen+vLoop]);
    }
}

#endif

