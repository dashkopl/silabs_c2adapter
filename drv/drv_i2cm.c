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
 *   Simulated I2C Master driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_I2CM_SUPPORT

/* porting part */
#if 1

#if (CORE_CLOCK != 24000000UL)
 #error "Only support 24MHz Core Clock for I2CM yet!"
#endif

/* note: these timing are fully tested, for the 4.7K ohm pull-up resisters */
#if   (DRV_I2CM_RATE == 80)
 #define DRV_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_DelayUs(4);                     \
                                } while (0)
#elif (DRV_I2CM_RATE == 100)
 #define DRV_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_DelayUs(3);                     \
                                } while (0)
#elif (DRV_I2CM_RATE == 200)
 #define DRV_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_DelayUs(1);                     \
                                    DRV_CPU_Delay125ns();                   \
                                    NOP(); NOP();                           \
                                } while (0)
#elif (DRV_I2CM_RATE == 400)
 #define DRV_I2CM_FixRate()     do {                                        \
                                    DRV_CPU_Delay125ns();                   \
                                    DRV_CPU_Delay125ns();                   \
                                } while (0)
#else
 #error "Unsupported I2C Master Rate!"
#endif

#define DRV_I2CM_SET_SCL(_v)    do {                                        \
                                    DRV_I2CM_FixRate();                     \
                                    DRV_IO_Write(IO(IO_EVB_I2CM_SCL),(_v)); \
                                                                            \
                                    /* clock-stretch, maximum 500us */      \
                                    if ((_v) == HIGH)                       \
                                    {                                       \
                                        UINT16  _loop = 500;                \
                                        while ((DRV_I2CM_GET_SCL() == LOW)  \
                                               && _loop--)                  \
                                        {                                   \
                                            DRV_CPU_DelayUs(1);             \
                                        }                                   \
                                    }                                       \
                                } while (0)
#define DRV_I2CM_SET_SDA(_v)    DRV_IO_Write(IO(IO_EVB_I2CM_SDA), (_v))
#define DRV_I2CM_GET_SCL()      DRV_IO_Read(IO(IO_EVB_I2CM_SCL))
#define DRV_I2CM_GET_SDA()      DRV_IO_Read(IO(IO_EVB_I2CM_SDA))

#endif


/* low-level driver */
#if 1

#define _drv_i2cm_Init()                                                    \
    do {                                                                    \
        /* make sure both SCL/SDA lines are idle state */                   \
        DRV_I2CM_SET_SCL(HIGH);                                             \
        DRV_I2CM_SET_SDA(HIGH);                                             \
    } while (0)

#define _drv_i2cm_Start()                                                   \
    do {                                                                    \
        /* I2C Start/ReStart:                                               \
         *   SDA changed from HIGH(1) to LOW(0), while SCL is HIGH(1).      \
         */                                                                 \
        DRV_I2CM_SET_SDA(HIGH);                                             \
        DRV_I2CM_SET_SCL(HIGH);                                             \
        DRV_I2CM_FixRate(); /* t_BUF */                                     \
        DRV_I2CM_SET_SDA(LOW);                                              \
                            /* t_HD;STA */                                  \
        DRV_I2CM_SET_SCL(LOW);                                              \
    } while (0)

#define _drv_i2cm_Stop()                                                    \
    do {                                                                    \
        /* SDA changed from LOW to HIGH, while SCL is HIGH */               \
        DRV_I2CM_SET_SDA(LOW);                                              \
        DRV_I2CM_SET_SCL(HIGH);                                             \
        DRV_I2CM_FixRate(); /* t_SU;STO */                                  \
        DRV_I2CM_SET_SDA(HIGH);                                             \
    } while (0)

/* return:
 *  =TRUE,  an ACK received;
 *  =FALSE, no ACK received.
 */
static BOOL _drv_i2cm_TxByte(UINT8 vData)
{
    UINT8   vLoop;
    BOOL    vAck;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        /* transmitting data, MSB first, LSB last */
        CROL(vData, 1);
        DRV_I2CM_SET_SDA(vData&0x1);

        DRV_I2CM_SET_SCL(HIGH);
        DRV_I2CM_SET_SCL(LOW);
    }

    /* release SDA */
    DRV_I2CM_SET_SDA(HIGH);

    /* check ACK */
    DRV_I2CM_SET_SCL(HIGH);
    vAck = DRV_I2CM_GET_SDA();
    DRV_I2CM_SET_SCL(LOW);

    return !vAck;
}

static UINT8 _drv_i2cm_RxByte(BOOL bSendNAK)
{
    UINT8   vLoop;
    UINT8   vData = 0;

    for (vLoop = 8; vLoop != 0; vLoop--)
    {
        DRV_I2CM_SET_SCL(HIGH);
        vData <<= 1;
        vData |= DRV_I2CM_GET_SDA();
        DRV_I2CM_SET_SCL(LOW);
    }

    /* send ACK/NAK */
    DRV_I2CM_SET_SDA(bSendNAK);
    DRV_I2CM_SET_SCL(HIGH);
    DRV_I2CM_SET_SCL(LOW);
    DRV_I2CM_SET_SDA(HIGH);

    return vData;
}

/* check I2C bus is ready to operate or not */
static BOOL _drv_i2cm_CheckReady(void)
{
    if ((DRV_I2CM_GET_SCL() == HIGH)
        && (DRV_I2CM_GET_SDA() == HIGH))
    {
        /* the I2C only can be started, while SCL/SDA is at high level */
        return TRUE;
    }
    else if ((DRV_I2CM_GET_SCL() == HIGH)
             && (DRV_I2CM_GET_SDA() == LOW))
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
            DRV_I2CM_SET_SCL(LOW);
            DRV_I2CM_SET_SCL(HIGH);
        }

        if (DRV_I2CM_GET_SDA() == HIGH)
        {
            _drv_i2cm_Start();
            _drv_i2cm_Stop();

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

#endif


#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_Stream
 * DESCRIPTION:
 *   I2C master send write/read combined stream.
 * PARAMETERS:
 *   vI2cAddr  : I2C slave chip address.
 *   vWriteLen : Write length.
 *   aWriteBuf : Write buffer.
 *   vReadLen  : Read length.
 *   aReadBuf  : Read buffer.
 * RETURN:
 *   TRUE   : Send stream successfully.
 *   FALSE  : Send stream failed.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_I2CM_Stream
(
    IN       UINT8      vI2cAddr,
    IN       UINT8      vWriteLen,
    IN const UINT8     *aWriteBuf,
    IN       UINT8      vReadLen,
    OUT      UINT8     *aReadBuf
)
{
    BOOL    bDone = FALSE;
    UINT8   vLoop;

    /* make sure the I2C is ready */
    if (!_drv_i2cm_CheckReady())
    {
        return bDone;
    }

    /* send write stream */
    if ((vWriteLen != 0)
        || ((vWriteLen == 0) && (vReadLen == 0)))
    {
        /* send I2C start */
        _drv_i2cm_Start();

        /* send I2C slave address + write */
        if (!_drv_i2cm_TxByte(vI2cAddr&0xFE))
        {
            goto _exit;
        }

        /* send write buffer */
        for (vLoop = 0; vLoop < vWriteLen; vLoop++)
        {
            if (!_drv_i2cm_TxByte(aWriteBuf[vLoop]))
            {
                goto _exit;
            }
        }
    }

    /* send write stream */
    if (vReadLen != 0)
    {
        /* send I2C start/restart */
        _drv_i2cm_Start();

        /* send I2C slave address + read */
        if (!_drv_i2cm_TxByte(vI2cAddr|0x01))
        {
            goto _exit;
        }

        /* read data */
        for (vLoop = 0; vLoop < vReadLen; vLoop++)
        {
            aReadBuf[vLoop] = _drv_i2cm_RxByte(vLoop==(vReadLen-1));
        }
    }

    /* I2C stream done */
    bDone = TRUE;

_exit:
    /* send I2C stop */
    _drv_i2cm_Stop();

    return bDone;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_Probe
 * DESCRIPTION:
 *   I2C master probe chip.
 * PARAMETERS:
 *   vI2cAddr : I2C chip address.
 * RETURN:
 *   TRUE   : Probe successfully.
 *   FALSE  : Probe failed.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_I2CM_Probe(IN UINT8 vI2cAddr)
{
    return DRV_I2CM_Stream(vI2cAddr, 0, NULL, 0, NULL);
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_ReadByte
 * DESCRIPTION:
 *   I2C master random read one byte.
 * PARAMETERS:
 *   vI2cAddr : I2C slave chip address.
 *   vOffset  : I2C offset.
 * RETURN:
 *   I2C read data.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
UINT8 DRV_I2CM_ReadByte(IN UINT8 vI2cAddr, IN UINT8 vOffset)
{
    UINT8   vData;

    while (!DRV_I2CM_Stream(vI2cAddr, 1, &vOffset, 1, &vData))
    {}

    return vData;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_WriteByte
 * DESCRIPTION:
 *   I2C master random write one byte.
 * PARAMETERS:
 *   vI2cAddr : I2C slave chip address.
 *   vOffset  : I2C offset.
 *   vData    : I2C data to be written.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_I2CM_WriteByte(IN UINT8 vI2cAddr, IN UINT8 vOffset, IN UINT8 vData)
{
    UINT8   aBuf[2];

    aBuf[0] = vOffset;
    aBuf[1] = vData;
    while (!DRV_I2CM_Stream(vI2cAddr, sizeof(aBuf), &aBuf, 0, NULL))
    {}
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_Init
 * DESCRIPTION:
 *   I2C master driver init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_I2CM_Init(void)
{
    _drv_i2cm_Init();
}

#endif

#endif

