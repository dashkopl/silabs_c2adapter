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
 *   Thread: USB packet related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if PKT_SUPPORT

#if 1

#include "pkt_define.h"

static UINT16   vMagicNo;

static BOOL     bFlushFIFO;
SEG_XDATA PKT_T vFrame;

static struct
{
    UINT16  vCmd;
    UINT16  (SEG_CODE *pExec)(void);
} SEG_CODE aCmdTable[] = PKT_CMD_LIST;


static UINT16 _thread_pkt_CalcCRC(void)
{
    /* CRC16-CCITT: X16+X15+X2+1 */
    static SEG_CODE UINT16 aCRC16[256] =
    {
        0x0000, 0x1189, 0x2312, 0x329B, 0x4624, 0x57AD, 0x6536, 0x74BF,
        0x8C48, 0x9DC1, 0xAF5A, 0xBED3, 0xCA6C, 0xDBE5, 0xE97E, 0xF8F7,
        0x0919, 0x1890, 0x2A0B, 0x3B82, 0x4F3D, 0x5EB4, 0x6C2F, 0x7DA6,
        0x8551, 0x94D8, 0xA643, 0xB7CA, 0xC375, 0xD2FC, 0xE067, 0xF1EE,
        0x1232, 0x03BB, 0x3120, 0x20A9, 0x5416, 0x459F, 0x7704, 0x668D,
        0x9E7A, 0x8FF3, 0xBD68, 0xACE1, 0xD85E, 0xC9D7, 0xFB4C, 0xEAC5,
        0x1B2B, 0x0AA2, 0x3839, 0x29B0, 0x5D0F, 0x4C86, 0x7E1D, 0x6F94,
        0x9763, 0x86EA, 0xB471, 0xA5F8, 0xD147, 0xC0CE, 0xF255, 0xE3DC,
        0x2464, 0x35ED, 0x0776, 0x16FF, 0x6240, 0x73C9, 0x4152, 0x50DB,
        0xA82C, 0xB9A5, 0x8B3E, 0x9AB7, 0xEE08, 0xFF81, 0xCD1A, 0xDC93,
        0x2D7D, 0x3CF4, 0x0E6F, 0x1FE6, 0x6B59, 0x7AD0, 0x484B, 0x59C2,
        0xA135, 0xB0BC, 0x8227, 0x93AE, 0xE711, 0xF698, 0xC403, 0xD58A,
        0x3656, 0x27DF, 0x1544, 0x04CD, 0x7072, 0x61FB, 0x5360, 0x42E9,
        0xBA1E, 0xAB97, 0x990C, 0x8885, 0xFC3A, 0xEDB3, 0xDF28, 0xCEA1,
        0x3F4F, 0x2EC6, 0x1C5D, 0x0DD4, 0x796B, 0x68E2, 0x5A79, 0x4BF0,
        0xB307, 0xA28E, 0x9015, 0x819C, 0xF523, 0xE4AA, 0xD631, 0xC7B8,
        0x48C8, 0x5941, 0x6BDA, 0x7A53, 0x0EEC, 0x1F65, 0x2DFE, 0x3C77,
        0xC480, 0xD509, 0xE792, 0xF61B, 0x82A4, 0x932D, 0xA1B6, 0xB03F,
        0x41D1, 0x5058, 0x62C3, 0x734A, 0x07F5, 0x167C, 0x24E7, 0x356E,
        0xCD99, 0xDC10, 0xEE8B, 0xFF02, 0x8BBD, 0x9A34, 0xA8AF, 0xB926,
        0x5AFA, 0x4B73, 0x79E8, 0x6861, 0x1CDE, 0x0D57, 0x3FCC, 0x2E45,
        0xD6B2, 0xC73B, 0xF5A0, 0xE429, 0x9096, 0x811F, 0xB384, 0xA20D,
        0x53E3, 0x426A, 0x70F1, 0x6178, 0x15C7, 0x044E, 0x36D5, 0x275C,
        0xDFAB, 0xCE22, 0xFCB9, 0xED30, 0x998F, 0x8806, 0xBA9D, 0xAB14,
        0x6CAC, 0x7D25, 0x4FBE, 0x5E37, 0x2A88, 0x3B01, 0x099A, 0x1813,
        0xE0E4, 0xF16D, 0xC3F6, 0xD27F, 0xA6C0, 0xB749, 0x85D2, 0x945B,
        0x65B5, 0x743C, 0x46A7, 0x572E, 0x2391, 0x3218, 0x0083, 0x110A,
        0xE9FD, 0xF874, 0xCAEF, 0xDB66, 0xAFD9, 0xBE50, 0x8CCB, 0x9D42,
        0x7E9E, 0x6F17, 0x5D8C, 0x4C05, 0x38BA, 0x2933, 0x1BA8, 0x0A21,
        0xF2D6, 0xE35F, 0xD1C4, 0xC04D, 0xB4F2, 0xA57B, 0x97E0, 0x8669,
        0x7787, 0x660E, 0x5495, 0x451C, 0x31A3, 0x202A, 0x12B1, 0x0338,
        0xFBCF, 0xEA46, 0xD8DD, 0xC954, 0xBDEB, 0xAC62, 0x9EF9, 0x8F70,
    };

    UINT16  vCRC = 0xFFFF;
    UINT16  vLoop;

    for (vLoop = 0; vLoop < vFrame.vLen; vLoop++)
    {
        vCRC = (vCRC<<8) ^ aCRC16[(UINT8)(vCRC>>8)^(vFrame.vContent.buf[vLoop])];
    }

    return vCRC;
}

static void _thread_pkt_Dump(IN BOOL bRx)
{
  #if PKT_DEBUG_SUPPORT

    UINT16 vLoop;

  #if DRV_WATCHDOG_SUPPORT
    DRV_WATCHDOG_Kick();
  #endif

    printf("USB-%s-PKT: (magic=%.4hX,rev=%.4hX,len=%04hX,CRC=%04hX)",
           (bRx?"RX":"TX"),
           vFrame.vMagicNo, vFrame.vVersion, vFrame.vLen, vFrame.vCRC);
    for (vLoop = 0; vLoop < vFrame.vLen; vLoop++)
    {
        if ((vLoop%16) == 0)
        {
            printf("\n");
        }
        else if ((vLoop%8) == 0)
        {
            printf(" -");
        }

        printf(" %02bX", vFrame.vContent.buf[vLoop]);
    }
    printf("\n");

  #if DRV_WATCHDOG_SUPPORT
    DRV_WATCHDOG_Kick();
  #endif

  #else
    NO_WARNING(bRx);
  #endif
}

static BOOL _thread_pkt_Receive(void)
{
    UINT16  vRxTotalLen;
    UINT8   vBlockLen;
    UINT16  vElaspedTime;

  #if 1
    /* receive frame:
     *  -> 1st block: pkt_header + pkt_content
     *  -> 2nd block: pkt_content
     *  -> 3rd block: pkt_content
     *  -> ...
     */

    /* receive 1st block */
    memset(&vFrame, 0x00, sizeof(vFrame));
    vBlockLen = DRV_USB_ReadBlock((UINT8 *)&vFrame, DRV_USB_BLOCK_MAX_LEN);
    if (bFlushFIFO)
    {
        /* flush FIFO */
        printf("flush FIFO!\n");
        return FALSE;
    }
    if ((vBlockLen < PKT_HEADER_LEN) || (vFrame.vMagicNo != vMagicNo))
    {
        /* invalid frame, force flush FIFO, w/o responding */
        printf("invalid frame! (blockLen=%.2bX, magicNo=%.4hX)\n", vBlockLen, vFrame.vMagicNo);
        bFlushFIFO = TRUE;
        return FALSE;
    }
    if (vFrame.vVersion != PKT_VERSION)
    {
        /* invalid frame version, return supported version to host */
        printf("invalid frame version!\n");
        vFrame.vVersion = PKT_VERSION;
        return FALSE;
    }
    vRxTotalLen = vBlockLen-PKT_HEADER_LEN;

    /* receive remaining blocks */
    vElaspedTime = 0;
    while (vRxTotalLen < vFrame.vLen)
    {
        vBlockLen = DRV_USB_ReadBlock(vFrame.vContent.buf+vRxTotalLen,
                                      DRV_USB_BLOCK_MAX_LEN);

        if (vBlockLen == 0)
        {
            /* next block is still not ready */

            DRV_CPU_DelayUs(1);
            if (++vElaspedTime >= 50000)
            {
                /* timeout: 50ms */
                printf("rx packet timeout!\n");
                PKT_SetReply(PKT_REPLY_Fail_InvalidContent);
                return FALSE;
            }

            continue;
        }

        vRxTotalLen += vBlockLen;
    }

    if (vRxTotalLen != vFrame.vLen)
    {
        printf("invalid packet length!\n");
        PKT_SetReply(PKT_REPLY_Fail_InvalidContent);
        return FALSE;
    }
  #endif

	/* dump rx frame */
    _thread_pkt_Dump(TRUE);

    /* frame verify: CRC */
    if (vFrame.vCRC != _thread_pkt_CalcCRC())
    {
        printf("invalid CRC!\n");
        PKT_SetReply(PKT_REPLY_Fail_InvalidCRC);
        return FALSE;
    }

    return TRUE;
}

static void _thread_pkt_Handle(void)
{
	UINT16  vCmd;
	UINT16  vReply;
	UINT8   vLoop;

    vCmd = PKT_GetCmd();
	vReply = PKT_REPLY_Fail_InvalidCmd;
	for (vLoop = 0; vLoop < COUNT_OF(aCmdTable); vLoop++)
	{
		if (aCmdTable[vLoop].vCmd == vCmd)
		{
			vReply = aCmdTable[vLoop].pExec();
			break;
		}
	}

	PKT_SetReply(vReply);
    if (PKT_GetReplyState(vReply) == PKT_ReplyState_Fail)
    {
        PKT_SetPayloadSize(0x00);
    }
}

static void _thread_pkt_Transmit(void)
{
    if (bFlushFIFO)
    {
        /* flush FIFO */
        memset(&vFrame, 0x00, sizeof(vFrame));
        bFlushFIFO = FALSE;
    }
    else
    {
        /* update content length, and re-calculate CRC value */
        vFrame.vLen = 4+PKT_GetPayloadSize();
        vFrame.vCRC = _thread_pkt_CalcCRC();

        /* dump tx frame */
        _thread_pkt_Dump(FALSE);

        /* emit frame */
    	DRV_USB_WriteBlock((UINT8 *)&vFrame, PKT_HEADER_LEN+vFrame.vLen);
    }
}

#endif

#if 1

static volatile OS_SCB  vSCB_RxPkt;
static          OS_TCB  vTCB_Pkt;

/******************************************************************************
 * FUNCTION NAME:
 *   thread_Pkt_Notify
 * DESCRIPTION:
 *   Thread-Packet event notify callback.
 * PARAMETERS:
 *   vEvent : Notify event.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void thread_Pkt_Notify(IN UINT8 vEvent)
{
	if (vEvent & RX_COMPLETE)
	{
		/* notify packet has been received */
		PT_SEM_SIGNAL(NULL, &vSCB_RxPkt);
	}

	if (vEvent & FIFO_PURGE)
	{
        /* notify the FIFO needs to be flushed */
		PT_SEM_SIGNAL(NULL, &vSCB_RxPkt);
        bFlushFIFO = TRUE;
	}
}


/******************************************************************************
 * FUNCTION NAME:
 *   thread_PKT_Entry
 * DESCRIPTION:
 *   Pkt Thread Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   OS_HANDLE
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.25        Panda.Xiong        Create/Update
 *****************************************************************************/
OS_HANDLE thread_PKT_Entry(void)
{
    PT_BEGIN(&vTCB_Pkt);

    for (;;)
    {
        /* wait for packet */
        PT_SEM_WAIT(&vTCB_Pkt, &vSCB_RxPkt);

        if (_thread_pkt_Receive())
        {
            _thread_pkt_Handle();
        }
        _thread_pkt_Transmit();

        /* reset packet counter */
        PT_SEM_INIT(&vSCB_RxPkt, 0);
    }

    PT_END(&vTCB_Pkt);
}


/******************************************************************************
 * FUNCTION NAME:
 *   thread_PKT_Init
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void thread_PKT_Init(void)
{
    PT_INIT(&vTCB_Pkt);
    PT_SEM_INIT(&vSCB_RxPkt, 0);

    vMagicNo = CFG_GET(Vendor_PKT_MagicNo);
}

#endif

#endif

