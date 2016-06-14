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
 *   USB packet definition.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __PKT_DEFINE_H
#define __PKT_DEFINE_H


#if PKT_SUPPORT

/* frame definition */
#if 1

/* frame content (version 1) */
typedef struct
{
    UINT16  vCmdReply;                  /* command/reply */
    UINT16  vPayloadSize;               /* payload size  */
    UINT8   aPayload[PKT_MAX_LEN-4];    /* payload       */
} CONTENT_REV1_T;

/* frame brief */
typedef struct
{
    /* header */
    UINT16  vMagicNo;   /* magic number    */
    UINT16  vVersion;   /* content version */
    UINT16  vLen;       /* content length  */
    UINT16  vCRC;       /* content CRC16   */

    /* content */
    union
    {
        UINT8           buf[PKT_MAX_LEN];
        CONTENT_REV1_T  rev1;
    } vContent;
} PKT_T;
#define PKT_HEADER_LEN          offsetof(PKT_T, vContent)

extern SEG_XDATA PKT_T  vFrame;
#define PKT_GetCmd()            (vFrame.vContent.rev1.vCmdReply)
#define PKT_SetReply(_reply)    do { PKT_GetCmd() = (_reply); } while (0)
#define PKT_GetPayloadSize()    (vFrame.vContent.rev1.vPayloadSize)
#define PKT_SetPayloadSize(_ps) do { PKT_GetPayloadSize() = (_ps); } while (0)
#define PKT_GetPayload()        (vFrame.vContent.rev1.aPayload)
#define PKT_PayloadMaxLen       (PKT_MAX_LEN-4)

#endif


/* packet reply related */
#if 1

/* reply state */
#define PKT_GetReplyState(_reply)           (((_reply)>>8)&0xFF)
#define PKT_ReplyState_Idle                 0x00
#define PKT_ReplyState_Done                 0x01
#define PKT_ReplyState_Busy                 0x02
#define PKT_ReplyState_Fail                 0x03

/* reply */
#define PKT_REPLY(_stat, _msg)              (((UINT16)(_stat)<<8) | ((_msg)<<0))
#define PKT_REPLY_Idle_Ready                PKT_REPLY(PKT_ReplyState_Idle,0x01) /* Standard Reply: Ready to accept host command           */
#define PKT_REPLY_Busy_CmdCaptured          PKT_REPLY(PKT_ReplyState_Busy,0x01) /* Standard Reply: Command is captured but not processed  */
#define PKT_REPLY_Busy_CmdChecking          PKT_REPLY(PKT_ReplyState_Busy,0x02) /* Standard Reply: Command checking is in progress        */
#define PKT_REPLY_Busy_CmdExecuting         PKT_REPLY(PKT_ReplyState_Busy,0x03) /* Standard Reply: Command execution is in progress       */
#define PKT_REPLY_Fail_InvalidContent       PKT_REPLY(PKT_ReplyState_Fail,0x01) /* Standard Reply: Invalid frame content                  */
#define PKT_REPLY_Fail_InvalidCRC           PKT_REPLY(PKT_ReplyState_Fail,0x02) /* Standard Reply: Invalid frame CRC                      */
#define PKT_REPLY_Fail_InvalidCmd           PKT_REPLY(PKT_ReplyState_Fail,0x03) /* Standard Reply: Invalid command                        */
#define PKT_REPLY_Fail_InvalidLen           PKT_REPLY(PKT_ReplyState_Fail,0x04) /* Standard Reply: Invalid payload length                 */
#define PKT_REPLY_Fail_InvalidPwd           PKT_REPLY(PKT_ReplyState_Fail,0x05) /* Standard Reply: Password error                         */
#define PKT_REPLY_Fail_CmdCheckFail         PKT_REPLY(PKT_ReplyState_Fail,0x06) /* Standard Reply: Command checking error without detail  */
#define PKT_REPLY_Fail_CmdCheckTimeout      PKT_REPLY(PKT_ReplyState_Fail,0x07) /* Standard Reply: Command checking timeout               */
#define PKT_REPLY_Fail_CmdExecFail          PKT_REPLY(PKT_ReplyState_Fail,0x10) /* Standard Reply: Command execution error without detail */
#define PKT_REPLY_Done_ExecNoError          PKT_REPLY(PKT_ReplyState_Done,0x40) /* Extended Reply: Command execution without error        */
#define PKT_REPLY_Fail_ExecErrorCode0       PKT_REPLY(PKT_ReplyState_Fail,0x40) /* Extended Reply: Command execution with error code 0    */
#define PKT_REPLY_Fail_ExecErrorCode1       PKT_REPLY(PKT_ReplyState_Fail,0x41) /* Extended Reply: Command execution with error code 1    */
#define PKT_REPLY_Fail_ExecErrorCode2       PKT_REPLY(PKT_ReplyState_Fail,0x42) /* Extended Reply: Command execution with error code 2    */

#endif


/* packet command related */
#if 1

#include "pkt_system.h"
#include "pkt_i2cm.h"
#include "pkt_mdiom.h"
#include "pkt_c2m.h"

#define PKT_CMD_LIST                {                               \
                                        PKT_SYSTEM_CMD_LIST         \
                                        PKT_I2CM_CMD_LIST           \
                                        PKT_MDIOM_CMD_LIST          \
                                        PKT_C2M_CMD_LIST            \
                                    }

#endif

#endif


#endif /* __PKT_DEFINE_H */

