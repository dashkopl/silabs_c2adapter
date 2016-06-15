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
 *   Configuration database related.
 * HISTORY:
 *   2016.2.15        Panda.Xiong          Create
 *
 *****************************************************************************/

#define _CFG_DB_INTERNAL_
#include "cfg.h"
#include "drv.h"


#if CFG_SUPPORT

/* page read/write password level table */
static UINT8 SEG_CODE   aPagePwdReadTable[]  = MEMPAGE_READ_PWD_LEVEL_TABLE;
static UINT8 SEG_CODE   aPagePwdWriteTable[] = MEMPAGE_WRITE_PWD_LEVEL_TABLE;

/******************************************************************************
 * FUNCTION NAME:
 *   cfg_db_GetPID
 * DESCRIPTION:
 *   Get page PID.
 * PARAMETERS:
 *   vOffset : page offset.
 * RETURN:
 *   Page PID.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.2.17        Panda.Xiong          Create
 *****************************************************************************/
static SINT8 cfg_db_GetPID(IN UINT8 vOffset)
{
    if (vOffset < MEMMAP_REAL_OFFSET(DDM_EVB_TEMP))
    {
        return MEMPAGE_PID_DIRECT_FE_00;
    }
    else if (vOffset < I2CS_PAGE_SIZE)
    {
        return MEMPAGE_PID_DIRECT_FE_60;
    }
    else
    {
        switch (CFG_GET8(Vendor_Page_Select))
        {
            /* RAM pages */
            case 0xC0:
                if (vOffset < I2CS_PAGE_SIZE+CFG_RAM_PAGE_SIZE)
                {
                    return MEMPAGE_PID_EXTEND_FE_C0;
                }
                break;

            /* ROM pages */
            case 0x80: return MEMPAGE_PID_EXTEND_FE_80;
            case 0x81: return MEMPAGE_PID_EXTEND_FE_81;
            case 0x82: return MEMPAGE_PID_EXTEND_FE_82;

            /* virtual pages */
            case 0xFF: return MEMPAGE_PID_EXTEND_FE_FF;

            default:
                break;
        }
    }

    return MEMPAGE_PID_INVALID;
}


/******************************************************************************
 * FUNCTION NAME:
 *   CFG_DB_ReadByte
 * DESCRIPTION:
 *   Read byte data for I2C slave.
 * PARAMETERS:
 *   vOffset : offset to read.
 * RETURN:
 *   Read byte data.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
UINT8 CFG_DB_ReadByte(IN UINT8 vOffset)
{
    SINT8   vPID = cfg_db_GetPID(vOffset);
    UINT8   vPageSize;

    if (vPID == MEMPAGE_PID_INVALID)
    {
        /* invalid page */
        return (UINT8)I2CS_INVALID_DATA;
    }

    vPageSize = (MEMPAGE_IsRAM(vPID)? CFG_RAM_PAGE_SIZE : CFG_ROM_PAGE_SIZE);
    vOffset  &= (vPageSize - 1);

    /* check password level, to make sure it's readable */
    if (CFG_PWD_GetLevel() >= aPagePwdReadTable[vPID])
    {
        /* password check pass */
        switch (vPID)
        {
            case MEMPAGE_PID_DIRECT_FE_60:
                switch (vOffset)
                {
                    /* for security reason,
                     *  the password entry is write-only field.
                     */
                    case CFG(Vendor_PWD_Entry)+0:
                    case CFG(Vendor_PWD_Entry)+1:
                    case CFG(Vendor_PWD_Entry)+2: return 0x00;
                    case CFG(Vendor_PWD_Entry)+3: return CFG_PWD_GetLevel();

                    default:
                        break;
                }
                break;

            case MEMPAGE_PID_EXTEND_FE_FF:
                return (((vOffset >= CFG_HEAD(Vendor_FwVersion))
                            && (vOffset <= CFG_TAIL(Vendor_FwVersion)))?
                        FW_VERSION(vOffset-CFG_HEAD(Vendor_FwVersion)):
                        (UINT8)I2CS_INVALID_DATA);

            default:
                break;
        }

        return CFG_GETV8(vPID, vOffset);
    }
    else
    {
        /* password check fail */
        return (UINT8)I2CS_INVALID_DATA;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   CFG_DB_WriteFlush
 * DESCRIPTION:
 *   Write flush data from I2C slave.
 * PARAMETERS:
 *   vOffset : offset to read.
 *   vCount  : flush buffer count.
 *   pBuf    : flush buffer.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void CFG_DB_WriteFlush
(
    IN       UINT8            vOffset,
    IN       UINT8            vCount,
    IN const UINT8 SEG_XDATA *pBuf
)
{
    SINT8   vPID = cfg_db_GetPID(vOffset);
    UINT8   vPageSize;

    if ((vPID == MEMPAGE_PID_INVALID) || (vCount == 0))
    {
        /* invalid page, or zero flush length */
        return;
    }

    /* limit Rx FIFO length to page boundary */
    vPageSize = (MEMPAGE_IsRAM(vPID)? CFG_RAM_PAGE_SIZE : CFG_ROM_PAGE_SIZE);
    vOffset  &= (vPageSize - 1);
    if (vOffset+vCount > vPageSize)
    {
        vCount = (vOffset+vCount) - vPageSize;
    }

    if (vPID == MEMPAGE_PID_DIRECT_FE_60)
    {
        /* FE.60-7F page */

        UINT8   vLoop;
        for (vLoop=0; vLoop<vCount; vLoop++,vOffset++)
        {
            UINT8   vData = pBuf[vLoop];

            switch (vOffset)
            {
                case CFG(RT_EVB_CTRL):
                    /* EVB/DUT related */
                case CFG(Vendor_PWD_Entry)+0:
                case CFG(Vendor_PWD_Entry)+1:
                case CFG(Vendor_PWD_Entry)+2:
                case CFG(Vendor_PWD_Entry)+3:
                case CFG(Vendor_Page_Select):
                    CFG_SETV8(MEMPAGE_PID_DIRECT_FE_60, vOffset, vData);
                    break;

                default:    /* read-only field */
                    /* do nothing */
                    break;
            }
        }

        /* refresh password level */
        CFG_PWD_RefreshLevel();
    }
    else    /* other pages */
    {
        if (vPID == MEMPAGE_PID_DIRECT_FE_00)
        {
            if (vOffset+vCount > MEMMAP_REAL_OFFSET(DDM_EVB_TEMP))
            {
                /* cross-write from A2.00-5F to A2.60-7F field,
                 * only accept A2.00-5F field data.
                 */
                vCount = (vOffset+vCount) - MEMMAP_REAL_OFFSET(DDM_EVB_TEMP);
            }
        }

        /* check password level, to make sure it's writable */
        if (CFG_PWD_GetLevel() >= aPagePwdWriteTable[vPID])
        {
            if (MEMPAGE_IsRAM(vPID))
            {
                /* RAM page */

                UINT8   vLoop;
                for (vLoop=0; vLoop<vCount; vLoop++)
                {
                    CFG_SETV8(vPID, vOffset+vLoop, pBuf[vLoop]);
                }
            }
            else if (MEMPAGE_IsROM(vPID))
            {
                /* ROM page */
                EEPROM_MEMCPY(MEMPAGE_ROM_LMA(vPID)+vOffset, pBuf, vCount);
            }
            else
            {
                /* VIRTUAL page */
                /* do nothing */
            }
        }
    }
}

#endif

