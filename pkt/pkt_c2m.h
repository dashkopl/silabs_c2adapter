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

