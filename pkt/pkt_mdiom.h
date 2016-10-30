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
UINT16 PKT_MDIOM_FrameAddr(void);
UINT16 PKT_MDIOM_FrameWrite(void);
UINT16 PKT_MDIOM_FrameRead(void);
UINT16 PKT_MDIOM_FramePRIA(void);

/* MDIO related commands */
#define PKT_MDIOM_CMD_LIST                                                  \
    { 0x1100, PKT_MDIOM_Inspect,    },                                      \
    { 0x1110, PKT_MDIOM_Probe,      },                                      \
    { 0x1111, PKT_MDIOM_Read,       },                                      \
    { 0x1112, PKT_MDIOM_Write,      },                                      \
    { 0x1120, PKT_MDIOM_FrameAddr,  },                                      \
    { 0x1121, PKT_MDIOM_FrameWrite, },                                      \
    { 0x1122, PKT_MDIOM_FrameRead,  },                                      \
    { 0x1123, PKT_MDIOM_FramePRIA,  },                                      \

#else

/* MDIO related commands */
#define PKT_MDIOM_CMD_LIST      /* empty */

#endif


#endif /* __PKT_MDIOM_H */

