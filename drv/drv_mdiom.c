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
 *   Simulated MDIO Master driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_MDIOM_SUPPORT

/* porting part */
#if 1

/* can support 3MHz MDC rate; (tested on C8051F321 @ 24MHz) */

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

static SEG_BDATA UINT16 vMdioCtrl  = 0x0000;
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


#define drv_mdiom_TxBit(_v)          do {                                           \
                                        CY = (_v);                                  \
                                        MDC_SET(HIGH);                              \
                                        MDIO_SET(CY);                               \
                                        MDC_SET(LOW);                               \
                                    } while (0)
#define drv_mdiom_RxBit(_v)          do {                                           \
                                        MDC_SET(LOW);                               \
                                        CY = MDIO_GET();                            \
                                        MDC_SET(HIGH);                              \
                                        (_v) = CY;                                  \
                                    } while (0)


/* 32-bit preamble */
#define drv_mdiom_TxPreamble()       do {                                           \
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

/* 2-bit start frame */
#define drv_mdiom_TxStartFrame()     do {                                           \
                                        drv_mdiom_TxBit(bMdioStartFrame1);          \
                                        drv_mdiom_TxBit(bMdioStartFrame0);          \
                                    } while (0)
#define drv_mdiom_SetStartFrame(_v1, _v0)  do {                                     \
                                        bMdioStartFrame1 = (_v1);                   \
                                        bMdioStartFrame0 = (_v0);                   \
                                    } while (0)

/* 2-bit operation code */
#define drv_mdiom_TxOperationCode()  do {                                           \
                                        drv_mdiom_TxBit(bMdioOperationCode1);       \
                                        drv_mdiom_TxBit(bMdioOperationCode0);       \
                                    } while (0)
#define drv_mdiom_SetOperationCode(_v1, _v0) do {                                   \
                                        bMdioOperationCode1 = (_v1);                \
                                        bMdioOperationCode0 = (_v0);                \
                                    } while (0)

/* 5-bit port address */
#define drv_mdiom_TxPortAddress()    do {                                           \
                                        drv_mdiom_TxBit(bMdioPortAddr4);            \
                                        drv_mdiom_TxBit(bMdioPortAddr3);            \
                                        drv_mdiom_TxBit(bMdioPortAddr2);            \
                                        drv_mdiom_TxBit(bMdioPortAddr1);            \
                                        drv_mdiom_TxBit(bMdioPortAddr0);            \
                                    } while (0)
#define drv_mdiom_SetPortAddress(_v) do {                                           \
                                        bMdioPortAddr4 = ((UINT8)(_v) >> 4) & 1;    \
                                        bMdioPortAddr3 = ((UINT8)(_v) >> 3) & 1;    \
                                        bMdioPortAddr2 = ((UINT8)(_v) >> 2) & 1;    \
                                        bMdioPortAddr1 = ((UINT8)(_v) >> 1) & 1;    \
                                        bMdioPortAddr0 = ((UINT8)(_v) >> 0) & 1;    \
                                    } while (0)

/* 5-bit device address */
#define drv_mdiom_TxDeviceAddress()  do {                                           \
                                        drv_mdiom_TxBit(bMdioDeviceAddr4);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr3);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr2);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr1);          \
                                        drv_mdiom_TxBit(bMdioDeviceAddr0);          \
                                    } while (0)
#define drv_mdiom_SetDeviceAddress(_v) do {                                         \
                                        bMdioDeviceAddr4 = ((UINT8)(_v) >> 4) & 1;  \
                                        bMdioDeviceAddr3 = ((UINT8)(_v) >> 3) & 1;  \
                                        bMdioDeviceAddr2 = ((UINT8)(_v) >> 2) & 1;  \
                                        bMdioDeviceAddr1 = ((UINT8)(_v) >> 1) & 1;  \
                                        bMdioDeviceAddr0 = ((UINT8)(_v) >> 0) & 1;  \
                                    } while (0)

/* 2-bit turn around */
#define drv_mdiom_TxTurnAround()     do {                                           \
                                        drv_mdiom_TxBit(bMdioTurnAround1);          \
                                        drv_mdiom_TxBit(bMdioTurnAround0);          \
                                    } while (0)
#define drv_mdiom_RxTurnAround()     do {                                           \
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
#define drv_mdiom_SetTurnAround(_v1, _v0)  do {                                     \
                                        bMdioTurnAround1 = (_v1);                   \
                                        bMdioTurnAround0 = (_v0);                   \
                                    } while (0)
#define drv_mdiom_IsReadSuccess()    (bMdioTurnAround0 == 0)

/* 16-bit address/data */
#define drv_mdiom_TxAddr()           do {                                           \
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
#define drv_mdiom_TxData()           do {                                           \
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
#define drv_mdiom_RxData()           do {                                           \
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
#define drv_mdiom_SetAddr(_v)        do { vMdioAddr = (UINT16)(_v); } while (0)
#define drv_mdiom_SetData(_v)        do { vMdioData = (UINT16)(_v); } while (0)

#define drv_mdiom_StartFrame()       do {                                           \
                                        /* set both pin to push-pull mode,          \
                                         *  to stretch MDIO bus.                    \
                                         */                                         \
                                        MDC_PP();                                   \
                                        MDIO_PP();                                  \
                                    } while (0)
#define drv_mdiom_StopFrame()        do {                                           \
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

/* create MDIO frame: Address */
static void drv_mdiom_CreateAddrFrame
(
    IN UINT8    vPortAddr,
    IN UINT8    vDevAddr,
    IN UINT16   vRegAddr
)
{
    drv_mdiom_SetStartFrame(0, 0);
    drv_mdiom_SetOperationCode(0, 0);
    drv_mdiom_SetPortAddress(vPortAddr);
    drv_mdiom_SetDeviceAddress(vDevAddr);
    drv_mdiom_SetTurnAround(1, 0);
    drv_mdiom_SetAddr(vRegAddr);
}

/* create MDIO frame: Write */
static void drv_mdiom_CreateWriteFrame
(
    IN UINT8    vPortAddr,
    IN UINT8    vDevAddr,
    IN UINT16   vRegData
)
{
    drv_mdiom_SetStartFrame(0, 0);
    drv_mdiom_SetOperationCode(0, 1);
    drv_mdiom_SetPortAddress(vPortAddr);
    drv_mdiom_SetDeviceAddress(vDevAddr);
    drv_mdiom_SetTurnAround(1, 0);
    drv_mdiom_SetData(vRegData);
}

/* create MDIO frame: Read */
static void drv_mdiom_CreateReadFrame
(
    IN UINT8    vPortAddr,
    IN UINT8    vDevAddr
)
{
    drv_mdiom_SetStartFrame(0, 0);
    drv_mdiom_SetOperationCode(1, 1);
    drv_mdiom_SetPortAddress(vPortAddr);
    drv_mdiom_SetDeviceAddress(vDevAddr);
    drv_mdiom_SetTurnAround(1, 1);
    drv_mdiom_SetData(0xFFFF);
}

/* create MDIO frame: Post-Read-Inc-Addr */
static void drv_mdiom_CreatePRIAFrame
(
    IN UINT8    vPortAddr,
    IN UINT8    vDevAddr
)
{
    drv_mdiom_SetStartFrame(0, 0);
    drv_mdiom_SetOperationCode(1, 0);
    drv_mdiom_SetPortAddress(vPortAddr);
    drv_mdiom_SetDeviceAddress(vDevAddr);
    drv_mdiom_SetTurnAround(1, 1);
    drv_mdiom_SetData(0xFFFF);
}

#endif


/* MDIO Low-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FrameAddress
 * DESCRIPTION:
 *      MDIO Low-Level API: Execute Frame - Address.
 * PARAMETERS:
 *      vPortAddr : MDIO Port Address;
 *      vDevAddr  : MDIO Device Address;
 *      vRegAddr  : MDIO Register Address;
 * RETURN:
 *      TRUE  : MDIO Frame Executed Success;
 *      FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
BOOL DRV_MDIOM_FrameAddress
(
    IN  UINT8           vPortAddr,
    IN  UINT8           vDevAddr,
    IN  UINT16          vRegAddr
)
{
    BOOL    bIntState;

    /* create MDIO frame: Address */
    drv_mdiom_CreateAddrFrame(vPortAddr, vDevAddr, vRegAddr);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* transmit frame: Address */
    drv_mdiom_TxAddrFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check frame result */
    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FrameWrite
 * DESCRIPTION:
 *      MDIO Low-Level API: Execute Frame - Write.
 * PARAMETERS:
 *      vPortAddr : MDIO Port Address;
 *      vDevAddr  : MDIO Device Address;
 *      vData     : MDIO Write Data;
 * RETURN:
 *      TRUE  : MDIO Frame Executed Success;
 *      FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
BOOL DRV_MDIOM_FrameWrite
(
    IN  UINT8           vPortAddr,
    IN  UINT8           vDevAddr,
    IN  UINT16          vData
)
{
    BOOL    bIntState;

    /* create MDIO frame: Write */
    drv_mdiom_CreateWriteFrame(vPortAddr, vDevAddr, vData);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* transmit frame: Write */
    drv_mdiom_TxDataFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check frame result */
    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FrameRead
 * DESCRIPTION:
 *      MDIO Low-Level API: Execute Frame - Read.
 * PARAMETERS:
 *      vPortAddr : MDIO Port Address;
 *      vDevAddr  : MDIO Device Address;
 *      pData     : MDIO Read Data;
 * RETURN:
 *      TRUE  : MDIO Frame Executed Success;
 *      FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
BOOL DRV_MDIOM_FrameRead
(
    IN  UINT8               vPortAddr,
    IN  UINT8               vDevAddr,
    OUT UINT16 SEG_XDATA   *pData
)
{
    BOOL    bIntState;

    /* create MDIO frame: Read */
    drv_mdiom_CreateReadFrame(vPortAddr, vDevAddr);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* transmit frame: Read */
    drv_mdiom_RxDataFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check read status */
    *pData = vMdioData;
    return drv_mdiom_IsReadSuccess();
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FramePRIA
 * DESCRIPTION:
 *      MDIO Low-Level API: Execute Frame - Post-Read-Inc-Address.
 * PARAMETERS:
 *      vPortAddr : MDIO Port Address;
 *      vDevAddr  : MDIO Device Address;
 *      pData     : MDIO Read Data;
 * RETURN:
 *      TRUE  : MDIO Frame Executed Success;
 *      FALSE : MDIO Frame Executed Fail;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
BOOL DRV_MDIOM_FramePRIA
(
    IN  UINT8               vPortAddr,
    IN  UINT8               vDevAddr,
    OUT UINT16 SEG_XDATA   *pData
)
{
    BOOL    bIntState;

    /* create MDIO frame: Post-Read-Inc-Address */
    drv_mdiom_CreatePRIAFrame(vPortAddr, vDevAddr);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* transmit frame: Read */
    drv_mdiom_RxDataFrame();

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    /* check read status */
    *pData = vMdioData;
    return drv_mdiom_IsReadSuccess();
}

#endif


/* MDIO High-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_Read
 * DESCRIPTION:
 *      MDIO Read Words Data.
 * PARAMETERS:
 *      vPortAddr : MDIO Port Address;
 *      vDevAddr  : MDIO Device Address;
 *      vRegAddr  : MDIO Register Address;
 *      vDataLen  : MDIO Read Data Length;
 *      pDataBuf  : MDIO Read Register Buffer;
 * RETURN:
 *      TRUE  : MDIO Read Words Data Success;
 *      FALSE : MDIO Read Words Data Fail;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
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

    /* create MDIO frame: Address */
    drv_mdiom_CreateAddrFrame(vPortAddr, vDevAddr, vRegAddr);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    /* transmit frame: Address */
    drv_mdiom_TxAddrFrame();

    /* create MDIO frame: Post-Read-Increment-Address */
    drv_mdiom_SetOperationCode(1, 0);

    /* transmit frame: Post-Read-Increment-Address */
    while (vDataLen-- != 0)
    {
        drv_mdiom_RxDataFrame();

        /* check read status */
        *pDataBuf++ = vMdioData;
        if (!drv_mdiom_IsReadSuccess())
        {
            bResult = FALSE;
            break;
        }
    }

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    return bResult;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_Write
 * DESCRIPTION:
 *      MDIO Write Words Data.
 * PARAMETERS:
 *      vPortAddr : MDIO Port Address;
 *      vDevAddr  : MDIO Device Address;
 *      vRegAddr  : MDIO Register Address;
 *      vDataLen  : MDIO Write Data Length;
 *      pDataBuf  : MDIO Write Register Buffer;
 * RETURN:
 *      TRUE  : MDIO Write Words Data Success;
 *      FALSE : MDIO Write Words Data Fail;
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
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
        /* prepare MDIO data */
        drv_mdiom_SetData(*pDataBuf);

        /* create MDIO frame: Address */
        drv_mdiom_CreateAddrFrame(vPortAddr, vDevAddr, vRegAddr);

        /* lock globally interrupt */
        bIntState = DRV_INT_LockGlobalInterrupt();

        /* transmit frame: Address */
        drv_mdiom_TxAddrFrame();

        /* create MDIO frame: Write */
        drv_mdiom_SetOperationCode(0, 1);

        /* transmit frame: Write */
        drv_mdiom_TxDataFrame();

        /* unlock globally interrupt */
        DRV_INT_UnlockGlobalInterrupt(bIntState);
    }

    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_Init
 * DESCRIPTION:
 *      MDIO Driver Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void DRV_MDIOM_Init(void)
{
    /* stop frame */
    drv_mdiom_StopFrame();
}

#endif

#endif

