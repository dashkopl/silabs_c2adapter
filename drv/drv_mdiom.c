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
 *   Simulated MDIO Master driver related. (IEEE802.3 Clause 45)
 *    Support 3MHz MDC rate for C8051F32x @24MHz core clock.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_MDIOM_SUPPORT

/* porting part */
#if 1

#define MDC_PP()        DRV_IO_Write(IO(IO_DUT_MDIOM_SCL_OEn), LOW)
#define MDC_OD()        DRV_IO_Write(IO(IO_DUT_MDIOM_SCL_OEn), HIGH)
#define MDC_SET(_v)     DRV_IO_Write(IO(IO_DUT_MDIOM_SCL_OUT), (_v))
#define MDC_GET()       DRV_IO_Read(IO(IO_DUT_MDIOM_SCL_IN))

#define MDIO_PP()       DRV_IO_Write(IO(IO_DUT_MDIOM_SDA_OEn), LOW)
#define MDIO_OD()       DRV_IO_Write(IO(IO_DUT_MDIOM_SDA_OEn), HIGH)
#define MDIO_SET(_v)    DRV_IO_Write(IO(IO_DUT_MDIOM_SDA_OUT), (_v))
#define MDIO_GET()      DRV_IO_Read(IO(IO_DUT_MDIOM_SDA_IN))

#endif


#if 1

static const BOOL bMdioPreamble = 1;

static SEG_BDATA UINT16 vMdioCtrl = 0x0000;
SBIT(bMdioStartFrame1,    vMdioCtrl, 15);
SBIT(bMdioStartFrame0,    vMdioCtrl, 14);
SBIT(bMdioOperationCode1, vMdioCtrl, 13);
SBIT(bMdioOperationCode0, vMdioCtrl, 12);
SBIT(bMdioPortAddr4,      vMdioCtrl, 11);
SBIT(bMdioPortAddr3,      vMdioCtrl, 10);
SBIT(bMdioPortAddr2,      vMdioCtrl,  9);
SBIT(bMdioPortAddr1,      vMdioCtrl,  8);
SBIT(bMdioPortAddr0,      vMdioCtrl,  7);
SBIT(bMdioDeviceAddr4,    vMdioCtrl,  6);
SBIT(bMdioDeviceAddr3,    vMdioCtrl,  5);
SBIT(bMdioDeviceAddr2,    vMdioCtrl,  4);
SBIT(bMdioDeviceAddr1,    vMdioCtrl,  3);
SBIT(bMdioDeviceAddr0,    vMdioCtrl,  2);
SBIT(bMdioTurnAround1,    vMdioCtrl,  1);
SBIT(bMdioTurnAround0,    vMdioCtrl,  0);

static SEG_BDATA UINT16 vMdioAddr = 0x0000;
SBIT(bMdioAddr15, vMdioAddr,  7);
SBIT(bMdioAddr14, vMdioAddr,  6);
SBIT(bMdioAddr13, vMdioAddr,  5);
SBIT(bMdioAddr12, vMdioAddr,  4);
SBIT(bMdioAddr11, vMdioAddr,  3);
SBIT(bMdioAddr10, vMdioAddr,  2);
SBIT(bMdioAddr9,  vMdioAddr,  1);
SBIT(bMdioAddr8,  vMdioAddr,  0);
SBIT(bMdioAddr7,  vMdioAddr, 15);
SBIT(bMdioAddr6,  vMdioAddr, 14);
SBIT(bMdioAddr5,  vMdioAddr, 13);
SBIT(bMdioAddr4,  vMdioAddr, 12);
SBIT(bMdioAddr3,  vMdioAddr, 11);
SBIT(bMdioAddr2,  vMdioAddr, 10);
SBIT(bMdioAddr1,  vMdioAddr,  9);
SBIT(bMdioAddr0,  vMdioAddr,  8);

static SEG_BDATA UINT16 vMdioData = 0x0000;
SBIT(bMdioData15, vMdioData,  7);
SBIT(bMdioData14, vMdioData,  6);
SBIT(bMdioData13, vMdioData,  5);
SBIT(bMdioData12, vMdioData,  4);
SBIT(bMdioData11, vMdioData,  3);
SBIT(bMdioData10, vMdioData,  2);
SBIT(bMdioData9,  vMdioData,  1);
SBIT(bMdioData8,  vMdioData,  0);
SBIT(bMdioData7,  vMdioData, 15);
SBIT(bMdioData6,  vMdioData, 14);
SBIT(bMdioData5,  vMdioData, 13);
SBIT(bMdioData4,  vMdioData, 12);
SBIT(bMdioData3,  vMdioData, 11);
SBIT(bMdioData2,  vMdioData, 10);
SBIT(bMdioData1,  vMdioData,  9);
SBIT(bMdioData0,  vMdioData,  8);


#define drv_mdiom_TxBit(_v)         do {                                            \
                                        CY = (_v);                                  \
                                        MDC_SET(HIGH);                              \
                                        MDIO_SET(CY);                               \
                                        MDC_SET(LOW);                               \
                                    } while (0)
#define drv_mdiom_RxBit(_v)         do {                                            \
                                        MDC_SET(LOW);                               \
                                        CY = MDIO_GET();                            \
                                        MDC_SET(HIGH);                              \
                                        (_v) = CY;                                  \
                                    } while (0)


/* 32-bit preamble */
#define drv_mdiom_TxPreamble()      do {                                            \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                        drv_mdiom_TxBit(bMdioPreamble);             \
                                    } while (0)

#define drv_mdiom_TxStartFrame()    do {                                            \
                                        drv_mdiom_TxBit(bMdioStartFrame1);          \
                                        drv_mdiom_TxBit(bMdioStartFrame0);          \
                                    } while (0)
#define drv_mdiom_TxOperationCode() do {                                            \
                                        drv_mdiom_TxBit(bMdioOperationCode1);       \
                                        drv_mdiom_TxBit(bMdioOperationCode0);       \
                                    } while (0)
#define drv_mdiom_TxPortAddress()   do {                                            \
                                        drv_mdiom_TxBit(bMdioPortAddr4);            \
                                        drv_mdiom_TxBit(bMdioPortAddr3);            \
                                        drv_mdiom_TxBit(bMdioPortAddr2);            \
                                        drv_mdiom_TxBit(bMdioPortAddr1);            \
                                        drv_mdiom_TxBit(bMdioPortAddr0);            \
                                    } while (0)
#define drv_mdiom_TxDeviceAddress() do {                                            \
                                        drv_mdiom_TxBit(bMdioDeviceAddr4);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr3);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr2);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr1);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr0);          \
                                    } while (0)
#define drv_mdiom_TxTurnAround()    do {                                            \
                                        drv_mdiom_TxBit(bMdioTurnAround1);          \
                                        drv_mdiom_TxBit(bMdioTurnAround0);          \
                                    } while (0)
#define drv_mdiom_RxTurnAround()    do {                                            \
                                        /* turn-around 1 */                         \
                                        NOP(); NOP();                               \
                                        MDC_SET(HIGH);                              \
                                        MDIO_SET(HIGH);                             \
                                        MDC_SET(LOW);                               \
                                        MDIO_OD();  /* release MDIO */              \
                                        MDC_SET(HIGH);                              \
                                        NOP(); NOP();                               \
                                                                                    \
                                        /* turn-around 0 */                         \
                                        drv_mdiom_RxBit(bMdioTurnAround0);          \
                                    } while (0)
#define drv_mdiom_IsReadSuccess()    (bMdioTurnAround0 == 0)

#define drv_mdiom_TxAddr()          do {                                            \
                                        drv_mdiom_TxBit(bMdioAddr15);               \
                                        drv_mdiom_TxBit(bMdioAddr14);               \
                                        drv_mdiom_TxBit(bMdioAddr13);               \
                                        drv_mdiom_TxBit(bMdioAddr12);               \
                                        drv_mdiom_TxBit(bMdioAddr11);               \
                                        drv_mdiom_TxBit(bMdioAddr10);               \
                                        drv_mdiom_TxBit(bMdioAddr9);                \
                                        drv_mdiom_TxBit(bMdioAddr8);                \
                                        drv_mdiom_TxBit(bMdioAddr7);                \
                                        drv_mdiom_TxBit(bMdioAddr6);                \
                                        drv_mdiom_TxBit(bMdioAddr5);                \
                                        drv_mdiom_TxBit(bMdioAddr4);                \
                                        drv_mdiom_TxBit(bMdioAddr3);                \
                                        drv_mdiom_TxBit(bMdioAddr2);                \
                                        drv_mdiom_TxBit(bMdioAddr1);                \
                                        drv_mdiom_TxBit(bMdioAddr0);                \
                                        NOP(); NOP();                               \
                                    } while (0)
#define drv_mdiom_TxData()          do {                                            \
                                        drv_mdiom_TxBit(bMdioData15);               \
                                        drv_mdiom_TxBit(bMdioData14);               \
                                        drv_mdiom_TxBit(bMdioData13);               \
                                        drv_mdiom_TxBit(bMdioData12);               \
                                        drv_mdiom_TxBit(bMdioData11);               \
                                        drv_mdiom_TxBit(bMdioData10);               \
                                        drv_mdiom_TxBit(bMdioData9);                \
                                        drv_mdiom_TxBit(bMdioData8);                \
                                        drv_mdiom_TxBit(bMdioData7);                \
                                        drv_mdiom_TxBit(bMdioData6);                \
                                        drv_mdiom_TxBit(bMdioData5);                \
                                        drv_mdiom_TxBit(bMdioData4);                \
                                        drv_mdiom_TxBit(bMdioData3);                \
                                        drv_mdiom_TxBit(bMdioData2);                \
                                        drv_mdiom_TxBit(bMdioData1);                \
                                        drv_mdiom_TxBit(bMdioData0);                \
                                        NOP(); NOP();                               \
                                    } while (0)
#define drv_mdiom_RxData()          do {                                            \
                                        drv_mdiom_RxBit(bMdioData15);               \
                                        drv_mdiom_RxBit(bMdioData14);               \
                                        drv_mdiom_RxBit(bMdioData13);               \
                                        drv_mdiom_RxBit(bMdioData12);               \
                                        drv_mdiom_RxBit(bMdioData11);               \
                                        drv_mdiom_RxBit(bMdioData10);               \
                                        drv_mdiom_RxBit(bMdioData9);                \
                                        drv_mdiom_RxBit(bMdioData8);                \
                                        drv_mdiom_RxBit(bMdioData7);                \
                                        drv_mdiom_RxBit(bMdioData6);                \
                                        drv_mdiom_RxBit(bMdioData5);                \
                                        drv_mdiom_RxBit(bMdioData4);                \
                                        drv_mdiom_RxBit(bMdioData3);                \
                                        drv_mdiom_RxBit(bMdioData2);                \
                                        drv_mdiom_RxBit(bMdioData1);                \
                                        drv_mdiom_RxBit(bMdioData0);                \
                                    } while (0)

#define drv_mdiom_SetFrameType(_v)  do {                                            \
                                        bMdioOperationCode1 = READ_BIT((_v), 1);    \
                                        bMdioOperationCode0 = READ_BIT((_v), 0);    \
                                    } while (0)
#define drv_mdiom_SetCtrl(_v)       do { vMdioCtrl = (UINT16)(_v); } while (0)
#define drv_mdiom_SetAddr(_v)       do { vMdioAddr = (UINT16)(_v); } while (0)
#define drv_mdiom_SetData(_v)       do { vMdioData = (UINT16)(_v); } while (0)

#define drv_mdiom_StartFrame()      do {                                            \
                                        /* set both pin to push-pull mode,          \
                                         *  to stretch MDIO bus.                    \
                                         */                                         \
                                        MDC_PP();                                   \
                                        MDIO_PP();                                  \
                                    } while (0)
#define drv_mdiom_StopFrame()       do {                                            \
                                        /* set both pin to open-drain mode,         \
                                         *  to release MDIO bus.                    \
                                         */                                         \
                                        MDC_SET(HIGH);                              \
                                        MDIO_SET(HIGH);                             \
                                        MDC_OD();                                   \
                                        MDIO_OD();                                  \
                                    } while (0)

#endif

#if 1

#define FRAME_TYPE_ADDR     0x0
#define FRAME_TYPE_WRITE    0x1
#define FRAME_TYPE_READ     0x3
#define FRAME_TYPE_PRIA     0x2
#define FRAME_ADDR          (FRAME_TYPE_ADDR  | 0x0002)
#define FRAME_WRITE         (FRAME_TYPE_WRITE | 0x0002)
#define FRAME_READ          (FRAME_TYPE_READ  | 0x0003)
#define FRAME_PRIA          (FRAME_TYPE_PRIA  | 0x0003)
#define drv_mdiom_CreateFrame(_frameType, _portAddr, _devAddr, _regAddr)            \
                                    do {                                            \
                                        drv_mdiom_SetCtrl((UINT16)(_frameType)    | \
                                                          ((UINT8)(_portAddr)<<7) | \
                                                          ((UINT8)(_devAddr)<<2));  \
                                        drv_mdiom_SetAddr(_regAddr);                \
                                    } while (0)

static void drv_mdiom_TxAddrFrame(void)
{
    drv_mdiom_StartFrame();
    drv_mdiom_TxPreamble();
    drv_mdiom_TxStartFrame();
    drv_mdiom_TxOperationCode();
    drv_mdiom_TxPortAddress();
    drv_mdiom_TxDeviceAddress();
    drv_mdiom_TxTurnAround();
    drv_mdiom_TxAddr();
    drv_mdiom_StopFrame();
}

static void drv_mdiom_TxDataFrame(void)
{
    drv_mdiom_StartFrame();
    drv_mdiom_TxPreamble();
    drv_mdiom_TxStartFrame();
    drv_mdiom_TxOperationCode();
    drv_mdiom_TxPortAddress();
    drv_mdiom_TxDeviceAddress();
    drv_mdiom_TxTurnAround();
    drv_mdiom_TxData();
    drv_mdiom_StopFrame();
}

static void drv_mdiom_RxDataFrame(void)
{
    drv_mdiom_StartFrame();
    drv_mdiom_TxPreamble();
    drv_mdiom_TxStartFrame();
    drv_mdiom_TxOperationCode();
    drv_mdiom_TxPortAddress();
    drv_mdiom_TxDeviceAddress();
    drv_mdiom_RxTurnAround();
    drv_mdiom_RxData();
    drv_mdiom_StopFrame();
}

#endif


/* MDIO Low-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FrameAddr
 * DESCRIPTION:
 *   MDIO Low-Level API: Execute Frame - Address.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 *   vRegAddr  : MDIO Register Address;
 * RETURN:
 *   TRUE  : MDIO Frame Executed Success;
 *   FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_MDIOM_FrameAddr
(
    IN  UINT8           vPortAddr,
    IN  UINT8           vDevAddr,
    IN  UINT16          vRegAddr
)
{
    BOOL    bIntState;

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* create frame: ADDR */
    drv_mdiom_CreateFrame(FRAME_TYPE_ADDR, vPortAddr, vDevAddr, vRegAddr);

    /* transmit frame: ADDR */
    drv_mdiom_TxAddrFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check frame result */
    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FrameWrite
 * DESCRIPTION:
 *   MDIO Low-Level API: Execute Frame - Write.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 *   vData     : MDIO Write Data;
 * RETURN:
 *   TRUE  : MDIO Frame Executed Success;
 *   FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_MDIOM_FrameWrite
(
    IN  UINT8           vPortAddr,
    IN  UINT8           vDevAddr,
    IN  UINT16          vData
)
{
    BOOL    bIntState;

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* create frame: WRITE */
    drv_mdiom_CreateFrame(FRAME_TYPE_WRITE, vPortAddr, vDevAddr, vData);

    /* transmit frame: WRITE */
    drv_mdiom_TxDataFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check frame result */
    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FrameRead
 * DESCRIPTION:
 *   MDIO Low-Level API: Execute Frame - Read.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 *   pData     : MDIO Read Data;
 * RETURN:
 *   TRUE  : MDIO Frame Executed Success;
 *   FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_MDIOM_FrameRead
(
    IN  UINT8               vPortAddr,
    IN  UINT8               vDevAddr,
    OUT UINT16 SEG_XDATA   *pData
)
{
    BOOL    bIntState;

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* create frame: READ */
    drv_mdiom_CreateFrame(FRAME_TYPE_READ, vPortAddr, vDevAddr, 0xFFFF);

    /* transmit frame: READ */
    drv_mdiom_RxDataFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check read status */
    if (pData != NULL)
    {
        *pData = vMdioData;
    }
    return drv_mdiom_IsReadSuccess();
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FramePRIA
 * DESCRIPTION:
 *   MDIO Low-Level API: Execute Frame - Post-Read-Inc-Address.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 *   pData     : MDIO Read Data;
 * RETURN:
 *   TRUE  : MDIO Frame Executed Success;
 *   FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_MDIOM_FramePRIA
(
    IN  UINT8               vPortAddr,
    IN  UINT8               vDevAddr,
    OUT UINT16 SEG_XDATA   *pData
)
{
    BOOL    bIntState;

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* create frame: PRIA */
    drv_mdiom_CreateFrame(FRAME_TYPE_PRIA, vPortAddr, vDevAddr, 0xFFFF);

    /* transmit frame: PRIA */
    drv_mdiom_RxDataFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check read status */
    if (pData != NULL)
    {
        *pData = vMdioData;
    }
    return drv_mdiom_IsReadSuccess();
}

#endif


/* MDIO High-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_Read
 * DESCRIPTION:
 *   MDIO Read Words Data.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 *   vRegAddr  : MDIO Register Address;
 *   vDataLen  : MDIO Read Data Length;
 *   pDataBuf  : MDIO Read Register Buffer;
 * RETURN:
 *   TRUE  : MDIO Read Words Data Success;
 *   FALSE : MDIO Read Words Data Fail;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_MDIOM_Read
(
    IN  UINT8               vPortAddr,
    IN  UINT8               vDevAddr,
    IN  UINT16              vRegAddr,
    IN  UINT16              vDataLen,
    OUT UINT16 SEG_XDATA   *pDataBuf
)
{
    BOOL    bResult = TRUE;
    BOOL    bIntState;

    for (; vDataLen-- != 0; vRegAddr++, pDataBuf++)
    {
        /* lock globally interrupt */
        bIntState = DRV_INT_LockGlobalInterrupt();

        /* create frame: ADDR */
        drv_mdiom_CreateFrame(FRAME_TYPE_ADDR, vPortAddr, vDevAddr, vRegAddr);

        /* transmit frame: ADDR */
        drv_mdiom_TxAddrFrame();

        /* set frame type: READ */
        drv_mdiom_SetFrameType(FRAME_TYPE_READ);

        /* transmit frame: READ */
        drv_mdiom_RxDataFrame();

        /* unlock globally interrupt */
        DRV_INT_UnlockGlobalInterrupt(bIntState);

        /* check read status */
        *pDataBuf++ = vMdioData;
        if (!drv_mdiom_IsReadSuccess())
        {
            bResult = FALSE;
            break;
        }
    }

    return bResult;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_Write
 * DESCRIPTION:
 *   MDIO Write Words Data.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 *   vRegAddr  : MDIO Register Address;
 *   vDataLen  : MDIO Write Data Length;
 *   pDataBuf  : MDIO Write Register Buffer;
 * RETURN:
 *   TRUE  : MDIO Write Words Data Success;
 *   FALSE : MDIO Write Words Data Fail;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_MDIOM_Write
(
    IN       UINT8              vPortAddr,
    IN       UINT8              vDevAddr,
    IN       UINT16             vRegAddr,
    IN       UINT16             vDataLen,
    IN const UINT16 SEG_XDATA  *pDataBuf
)
{
    BOOL    bIntState;

    for (; vDataLen-- != 0; vRegAddr++, pDataBuf++)
    {
        /* prepare data */
        drv_mdiom_SetData(*pDataBuf);

        /* lock globally interrupt */
        bIntState = DRV_INT_LockGlobalInterrupt();

        /* create frame: ADDR */
        drv_mdiom_CreateFrame(FRAME_TYPE_ADDR, vPortAddr, vDevAddr, vRegAddr);

        /* transmit frame: ADDR */
        drv_mdiom_TxAddrFrame();

        /* set frame type: WRITE */
        drv_mdiom_SetFrameType(FRAME_TYPE_WRITE);

        /* transmit frame: WRITE */
        drv_mdiom_TxDataFrame();

        /* unlock globally interrupt */
        DRV_INT_UnlockGlobalInterrupt(bIntState);
    }

    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_Init
 * DESCRIPTION:
 *   MDIO Driver Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_MDIOM_Init(void)
{
    /* stop frame */
    drv_mdiom_StopFrame();
}

#endif

#endif

