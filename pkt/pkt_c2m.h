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

#ifndef __PKT_C2M_H
#define __PKT_C2M_H


#if PKT_C2M_SUPPORT

typedef struct
{
    UINT32  vAddr;
    UINT16  vDataLen;
    UINT8   aBuf[PKT_PayloadMaxLen-6];
} PKT_C2M_RW_T;
#define PKT_C2M_RW_HEADER_LEN   offsetof(PKT_C2M_RW_T, aBuf)


UINT16 PKT_C2M_Inspect(void);
UINT16 PKT_C2M_Reset(void);
UINT16 PKT_C2M_Probe(void);
UINT16 PKT_C2M_FlashChipErase(void);
UINT16 PKT_C2M_FlashPageErase(void);
UINT16 PKT_C2M_FlashRead(void);
UINT16 PKT_C2M_FlashWrite(void);

/* C2 related commands */
#define PKT_C2M_CMD_LIST                                                    \
    { 0x1200, PKT_C2M_Inspect,          },                                  \
    { 0x1210, PKT_C2M_Reset,            },                                  \
    { 0x1211, PKT_C2M_Probe,            },                                  \
    { 0x1212, PKT_C2M_FlashChipErase,   },                                  \
    { 0x1213, PKT_C2M_FlashPageErase,   },                                  \
    { 0x1214, PKT_C2M_FlashRead,        },                                  \
    { 0x1215, PKT_C2M_FlashWrite,       },                                  \

#else

/* C2 related commands */
#define PKT_C2M_CMD_LIST       /* empty */

#endif


#endif /* __PKT_C2M_H */

