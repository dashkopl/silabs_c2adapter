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
 *   Packet command: C2 master related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if PKT_C2M_SUPPORT

#include "pkt_define.h"
#include "pkt_c2m.h"


UINT16 PKT_C2M_Inspect(void)
{
    PKT_SetPayloadSize(0x00);
    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_C2M_Reset(void)
{
    PKT_SetPayloadSize(0x00);
    return (DRV_C2M_Reset() ?
            PKT_REPLY_Done_ExecNoError :
            PKT_REPLY_Fail_ExecErrorCode0);
}

UINT16 PKT_C2M_Probe(void)
{
    XDATA_U32(PKT_GetPayload()) = DRV_C2M_Probe();
    PKT_SetPayloadSize(sizeof(UINT32));
    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_C2M_FlashChipErase(void)
{
    PKT_SetPayloadSize(0x00);
    return (DRV_C2M_ChipErase() ?
            PKT_REPLY_Done_ExecNoError :
            PKT_REPLY_Fail_ExecErrorCode0);
}

UINT16 PKT_C2M_FlashPageErase(void)
{
    if (PKT_GetPayloadSize() != 1)
    {
        return PKT_REPLY_Fail_InvalidLen;
    }

    return (DRV_C2M_PageErase(XDATA_U8(PKT_GetPayload())) ?
            PKT_REPLY_Done_ExecNoError :
            PKT_REPLY_Fail_ExecErrorCode0);
}

UINT16 PKT_C2M_FlashRead(void)
{
    PKT_C2M_RW_T SEG_XDATA *pPayload = (PKT_C2M_RW_T SEG_XDATA *)PKT_GetPayload();
    UINT8 SEG_XDATA *pBuf  = pPayload->aBuf;
    UINT16           vAddr = (UINT16)pPayload->vAddr;
    UINT16           vLen  = pPayload->vDataLen;

    if ((PKT_GetPayloadSize() != PKT_C2M_RW_HEADER_LEN)
        || (vLen > sizeof(pPayload->aBuf)))
    {
        return PKT_REPLY_Fail_InvalidLen;
    }

    /* split too long read data buffer into pieces to read */
    PKT_SetPayloadSize(PKT_C2M_RW_HEADER_LEN+vLen);
    while (vLen != 0)
    {
        UINT16 vReadLen = ((vLen<0x100)?vLen:0x100);

      #if DRV_WATCHDOG_SUPPORT
        DRV_WATCHDOG_Kick();
      #endif

        if (!DRV_C2M_FlashRead(pBuf, vAddr, (UINT8)vReadLen))
        {
            return PKT_REPLY_Fail_ExecErrorCode0;
        }

        pBuf  += vReadLen;
        vAddr += vReadLen;
        vLen  -= vReadLen;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_C2M_FlashWrite(void)
{
    PKT_C2M_RW_T SEG_XDATA *pPayload = (PKT_C2M_RW_T SEG_XDATA *)PKT_GetPayload();
    UINT8 SEG_XDATA *pBuf  = pPayload->aBuf;
    UINT16           vAddr = (UINT16)pPayload->vAddr;
    UINT16           vLen  = pPayload->vDataLen;

    if (PKT_GetPayloadSize() != (PKT_C2M_RW_HEADER_LEN+vLen))
    {
        return PKT_REPLY_Fail_InvalidLen;
    }

    /* split too long write data buffer into pieces to write */
    while (vLen != 0)
    {
        UINT16 vWriteLen = ((vLen<0x100)?vLen:0x100);

      #if DRV_WATCHDOG_SUPPORT
        DRV_WATCHDOG_Kick();
      #endif

        if (!DRV_C2M_FlashWrite(vAddr, pBuf, (UINT8)vWriteLen))
        {
            return PKT_REPLY_Fail_ExecErrorCode0;
        }

        pBuf  += vWriteLen;
        vAddr += vWriteLen;
        vLen  -= vWriteLen;
    }

    return PKT_REPLY_Done_ExecNoError;
}

#endif

