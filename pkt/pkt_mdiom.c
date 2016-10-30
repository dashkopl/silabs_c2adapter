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
 *   Packet command: MDIO master related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if PKT_MDIOM_SUPPORT

#include "pkt_define.h"
#include "pkt_mdiom.h"


UINT16 PKT_MDIOM_Inspect(void)
{
    PKT_SetPayloadSize(0x00);
    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_Probe(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();
    UINT16      SEG_XDATA  vData;

    if (!DRV_MDIOM_FrameRead(pPayload->vPortAddr,
                             pPayload->vDevAddr,
                             &vData))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_Read(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    if (!DRV_MDIOM_Read(pPayload->vPortAddr,
                        pPayload->vDevAddr,
                        pPayload->vOffset,
                        pPayload->vDataCount,
                        pPayload->aData))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_Write(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    if (!DRV_MDIOM_Write(pPayload->vPortAddr,
                         pPayload->vDevAddr,
                         pPayload->vOffset,
                         pPayload->vDataCount,
                         pPayload->aData))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_FrameAddr(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    if (!DRV_MDIOM_FrameAddr(pPayload->vPortAddr,
                             pPayload->vDevAddr,
                             pPayload->vOffset))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_FrameWrite(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    if (!DRV_MDIOM_FrameWrite(pPayload->vPortAddr,
                              pPayload->vDevAddr,
                              pPayload->aData[0]))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_FrameRead(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    if (!DRV_MDIOM_FrameRead(pPayload->vPortAddr,
                             pPayload->vDevAddr,
                             pPayload->aData))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_FramePRIA(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    if (!DRV_MDIOM_FramePRIA(pPayload->vPortAddr,
                             pPayload->vDevAddr,
                             pPayload->aData))
    {
        return PKT_REPLY_Fail_MdioNoAck;
    }

    return PKT_REPLY_Done_ExecNoError;
}

#endif

