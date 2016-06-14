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

#ifndef __PKT_MDIOM_H
#define __PKT_MDIOM_H


#if PKT_MDIOM_SUPPORT

#define PKT_REPLY_Fail_MdioNoAck    PKT_REPLY_Fail_ExecErrorCode0

typedef struct
{
    UINT8   vPortAddr;
    UINT8   vDevAddr;
    UINT16  vOffset;
    UINT16  vDataCount;
    UINT16  aData[(PKT_PayloadMaxLen-6)/2];
} PKT_MDIOM_T;
#define PKT_MDIOM_HEADER_LEN    offsetof(PKT_MDIOM_T, aData)


UINT16 PKT_MDIOM_Inspect(void);
UINT16 PKT_MDIOM_Probe(void);
UINT16 PKT_MDIOM_Read(void);
UINT16 PKT_MDIOM_Write(void);

/* MDIO related commands */
#define PKT_MDIOM_CMD_LIST                                                  \
    { 0x1100, PKT_MDIOM_Inspect,    },                                      \
    { 0x1110, PKT_MDIOM_Probe,      },                                      \
    { 0x1111, PKT_MDIOM_Read,       },                                      \
    { 0x1112, PKT_MDIOM_Write,      },                                      \

#else

/* MDIO related commands */
#define PKT_MDIOM_CMD_LIST      /* empty */

#endif


#endif /* __PKT_MDIOM_H */

