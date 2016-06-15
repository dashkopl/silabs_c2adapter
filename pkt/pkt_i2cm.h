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
 *   Packet command: I2C master related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __PKT_I2CM_H
#define __PKT_I2CM_H


#if PKT_I2CM_SUPPORT

#define PKT_REPLY_Fail_I2cNoAck     PKT_REPLY_Fail_ExecErrorCode0

typedef struct
{
    UINT8   vI2cAddr;
    UINT16  vWriteLen;
    UINT16  vReadLen;
    UINT8   aBuf[PKT_PayloadMaxLen-5];
} PKT_I2CM_STREAM_T;
#define PKT_I2CM_STREAM_HEADER_LEN  offsetof(PKT_I2CM_STREAM_T, aBuf)


UINT16 PKT_I2CM_Inspect(void);
UINT16 PKT_I2CM_Stream(void);

/* I2C related commands */
#define PKT_I2CM_CMD_LIST                                                   \
    { 0x1000, PKT_I2CM_Inspect,  },                                         \
    { 0x1010, PKT_I2CM_Stream,   },                                         \

#else

/* I2C related commands */
#define PKT_I2CM_CMD_LIST       /* empty */

#endif


#endif /* __PKT_I2CM_H */

