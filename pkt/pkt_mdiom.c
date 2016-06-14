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

UINT16 PKT_MDIOM_Read(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    NO_WARNING(pPayload);
    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_MDIOM_Write(void)
{
    PKT_MDIOM_T SEG_XDATA *pPayload = (PKT_MDIOM_T SEG_XDATA *)PKT_GetPayload();

    NO_WARNING(pPayload);
    return PKT_REPLY_Done_ExecNoError;
}

#endif

