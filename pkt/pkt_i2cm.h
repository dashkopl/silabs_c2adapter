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

