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

#include "cfg.h"
#include "drv.h"


#if PKT_I2CM_SUPPORT

#include "pkt_define.h"
#include "pkt_i2cm.h"

/* porting part */
#if 1

#if (CORE_CLOCK != 24000000UL)
 #error "Only support 24MHz Core Clock for I2CM yet!"
#endif

/* note: these timing are fully tested, for the 4.7K ohm pull-up resisters */
#if   (PKT_I2CM_RATE == 80)
 #define PKT_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_DelayUs(4);                     \
                                } while (0)
#elif (PKT_I2CM_RATE == 100)
 #define PKT_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_DelayUs(3);                     \
                                } while (0)
#elif (PKT_I2CM_RATE == 200)
 #define PKT_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_DelayUs(1);                     \
                                    DRV_CPU_Delay125ns();                   \
                                    NOP(); NOP();                           \
                                } while (0)
#elif (PKT_I2CM_RATE == 400)
 #define PKT_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_Delay125ns();                   \
                                    DRV_CPU_Delay125ns();                   \
                                } while (0)
#else
 #error "Unsupported I2C Master Rate!"
#endif

#define PKT_I2CM_SET_SCL(_v)     do {                                       \
                                    PKT_I2CM_FixRate();                     \
                                    DRV_IO_Write(IO(IO_DUT_I2CM_SCL),(_v)); \
                                                                            \
                                    /* clock-stretch, maximum 500us */      \
                                    if ((_v) == HIGH)                       \
                                    {                                       \
                                        UINT16  _loop = 500;                \
                                        while ((PKT_I2CM_GET_SCL() == LOW)  \
                                               && _loop--)                  \
                                        {                                   \
                                            DRV_CPU_DelayUs(1);             \
                                        }                                   \
                                    }                                       \
                                } while (0)
#define PKT_I2CM_SET_SDA(_v)     DRV_IO_Write(IO(IO_DUT_I2CM_SDA), (_v))
#define PKT_I2CM_GET_SCL()       DRV_IO_Read(IO(IO_DUT_I2CM_SCL))
#define PKT_I2CM_GET_SDA()       DRV_IO_Read(IO(IO_DUT_I2CM_SDA))

#endif


/* low-level driver */
#if 1

#define _pkt_i2cm_Init()                                                    \
    do {                                                                    \
        /* make sure both SCL/SDA lines are idle state */                   \
        PKT_I2CM_SET_SCL(HIGH);                                             \
        PKT_I2CM_SET_SDA(HIGH);                                             \
    } while (0)

#define _pkt_i2cm_Start()                                                   \
    do {                                                                    \
        /* I2C Start/ReStart:                                               \
         *   SDA changed from HIGH(1) to LOW(0), while SCL is HIGH(1).      \
         */                                                                 \
        PKT_I2CM_SET_SDA(HIGH);                                             \
        PKT_I2CM_SET_SCL(HIGH);                                             \
        PKT_I2CM_FixRate(); /* t_BUF */                                     \
        PKT_I2CM_SET_SDA(LOW);                                              \
                            /* t_HD;STA */                                  \
        PKT_I2CM_SET_SCL(LOW);                                              \
    } while (0)

#define _pkt_i2cm_Stop()                                                    \
    do {                                                                    \
        /* SDA changed from LOW to HIGH, while SCL is HIGH */               \
        PKT_I2CM_SET_SDA(LOW);                                              \
        PKT_I2CM_SET_SCL(HIGH);                                             \
        PKT_I2CM_FixRate(); /* t_SU;STO */                                  \
        PKT_I2CM_SET_SDA(HIGH);                                             \
    } while (0)

/* return:
 *  =TRUE,  an ACK received;
 *  =FALSE, no ACK received.
 */
static BOOL _pkt_i2cm_TxByte(UINT8 vData)
{
    UINT8   vLoop;
    BOOL    vAck;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        /* transmitting data, MSB first, LSB last */
        CROL(vData, 1);
        PKT_I2CM_SET_SDA(vData & 0x1);

        PKT_I2CM_SET_SCL(HIGH);
        PKT_I2CM_SET_SCL(LOW);
    }

    /* release SDA */
    PKT_I2CM_SET_SDA(HIGH);

    /* check ACK */
    PKT_I2CM_SET_SCL(HIGH);
    vAck = PKT_I2CM_GET_SDA();
    PKT_I2CM_SET_SCL(LOW);

    return !vAck;
}

static UINT8 _pkt_i2cm_RxByte(BOOL bSendNAK)
{
    UINT8   vLoop;
    UINT8   vData = 0;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        PKT_I2CM_SET_SCL(HIGH);
        vData <<= 1;
        vData |= PKT_I2CM_GET_SDA();
        PKT_I2CM_SET_SCL(LOW);
    }

    /* send ACK/NAK */
    PKT_I2CM_SET_SDA(bSendNAK);
    PKT_I2CM_SET_SCL(HIGH);
    PKT_I2CM_SET_SCL(LOW);
    PKT_I2CM_SET_SDA(HIGH);

    return vData;
}

/* check I2C bus is ready to operate or not */
static BOOL _pkt_i2cm_CheckReady(void)
{
    if ((PKT_I2CM_GET_SCL() == HIGH)
        && (PKT_I2CM_GET_SDA() == HIGH))
    {
        /* the I2C only can be started, while SCL/SDA is at high level */
        return TRUE;
    }
    else if ((PKT_I2CM_GET_SCL() == HIGH)
             && (PKT_I2CM_GET_SDA() == LOW))
    {
        /* SCL line is OK, but SDA line has been stretched by I2C slave,
         *  we should attempt to reset the I2C bus,
         *  to recover the SDA to idle state.
         *
         * Memory (Management Interface) Reset:
         *  1) Clock up to 9 cycles.
         *  2) Look for SDA high in each cycle while SCL is high.
         *  3) Create a START condition as SDA is high.
         */

        UINT8   vLoop;

        for (vLoop = 9; vLoop != 0; vLoop--)
        {
            PKT_I2CM_SET_SCL(LOW);
            PKT_I2CM_SET_SCL(HIGH);
        }

        if (PKT_I2CM_GET_SDA() == HIGH)
        {
            _pkt_i2cm_Start();
            _pkt_i2cm_Stop();

            /* we have successfully recovered the SDA line to idle state */
            return TRUE;
        }
    }
    else
    {
        /* unsupported stretching on SCL/SDA line, operation fail */
    }

    return FALSE;
}

static BOOL pkt_i2cm_Stream(IN OUT PKT_I2CM_STREAM_T SEG_XDATA *pPayload)
{
    UINT16  vWriteLen = pPayload->vWriteLen;
    UINT16  vReadLen  = pPayload->vReadLen;
    BOOL    bIntState;
    BOOL    bDone = FALSE;
    UINT16  vLoop;

    /* make sure the I2C is ready */
    if (!_pkt_i2cm_CheckReady())
    {
        return bDone;
    }

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* send write stream */
    if ((vWriteLen != 0)
        || ((vWriteLen == 0) && (vReadLen == 0)))
    {
        /* send I2C start */
        _pkt_i2cm_Start();

        /* send I2C slave address + write */
        if (!_pkt_i2cm_TxByte(pPayload->vI2cAddr&0xFE))
        {
            goto _exit;
        }

        /* send write buffer */
        for (vLoop = 0; vLoop < vWriteLen; vLoop++)
        {
            if (!_pkt_i2cm_TxByte(pPayload->aBuf[vLoop]))
            {
                goto _exit;
            }
        }
    }

    /* send read stream */
    if (vReadLen != 0)
    {
        /* send I2C start/restart */
        _pkt_i2cm_Start();

        /* send I2C slave address + read */
        if (!_pkt_i2cm_TxByte(pPayload->vI2cAddr|0x01))
        {
            goto _exit;
        }

        /* read data */
        for (vLoop = 0; vLoop < vReadLen; vLoop++)
        {
            pPayload->aBuf[vWriteLen+vLoop] =
                _pkt_i2cm_RxByte(vLoop==(vReadLen-1));
        }
    }

    /* I2C stream done */
    bDone = TRUE;

_exit:
    /* send I2C stop */
    _pkt_i2cm_Stop();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    return bDone;
}

#endif

#if PKT_I2CM_VS_SUPPORT

static BOOL pkt_i2cm_vs_Stream(IN OUT PKT_I2CM_STREAM_T SEG_XDATA *pPayload)
{
    static UINT8 vRegOffset = 0x00;
    UINT16  vWriteLen = pPayload->vWriteLen;
    UINT16  vReadLen  = pPayload->vReadLen;

    /* send write stream */
    if (vWriteLen != 0)
    {
        /* 1st byte is always register offset */
        vRegOffset = pPayload->aBuf[0];
        if (vWriteLen > 0x100)
        {
            /* write length overflow */
            return FALSE;
        }

        /* send write buffer */
        CFG_DB_WriteFlush(vRegOffset, (UINT8)(vWriteLen-1), &(pPayload->aBuf[1]));
        vRegOffset = (UINT8)(vRegOffset+vWriteLen-1);
    }

    /* send read stream */
    if (vReadLen != 0)
    {
        UINT16  vLoop;

        /* read data */
        for (vLoop = 0; vLoop < vReadLen; vLoop++)
        {
            pPayload->aBuf[vWriteLen+vLoop] = CFG_DB_ReadByte(vRegOffset++);
        }
    }

    return TRUE;
}

#endif

#if 1

UINT16 PKT_I2CM_Inspect(void)
{
    _pkt_i2cm_Init();

    PKT_SetPayloadSize(0x00);
    return PKT_REPLY_Done_ExecNoError;
}

UINT16 PKT_I2CM_Stream(void)
{
    PKT_I2CM_STREAM_T SEG_XDATA *pPayload =
            (PKT_I2CM_STREAM_T SEG_XDATA *)PKT_GetPayload();

    if ((PKT_GetPayloadSize() != (PKT_I2CM_STREAM_HEADER_LEN+pPayload->vWriteLen))
        || (pPayload->vWriteLen+pPayload->vReadLen > COUNT_OF(pPayload->aBuf)))
    {
        return PKT_REPLY_Fail_InvalidLen;
    }

  #if PKT_I2CM_VS_SUPPORT
    if ((pPayload->vI2cAddr == PKT_I2CM_VS_ADDR) ?
        pkt_i2cm_vs_Stream(pPayload) :
        pkt_i2cm_Stream(pPayload))
  #else
    if (pkt_i2cm_Stream(pPayload))
  #endif
    {
        PKT_SetPayloadSize(PKT_I2CM_STREAM_HEADER_LEN
                           + pPayload->vWriteLen
                           + pPayload->vReadLen);
        return PKT_REPLY_Done_ExecNoError;
    }
    else
    {
        return PKT_REPLY_Fail_I2cNoAck;
    }
}

#endif

#endif

