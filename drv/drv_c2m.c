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
 *   Simulated C2 Master driver related.
 *    see "AN127.pdf" for details.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_C2M_SUPPORT

/* porting part */
#if 1

#if (CORE_CLOCK != 24000000UL)
 #error "Only support 24MHz Core Clock for C2M yet!"
#endif

#define C2CK_PP()       drv_io_SetOutputPP(IO(IO_C2M_SCL))
#define C2CK_OD()       drv_io_SetOutputOD(IO(IO_C2M_SCL))
#define C2CK_SET(_v)    DRV_IO_Write(IO(IO_C2M_SCL), (_v))
#define C2CK_GET()      DRV_IO_Read(IO(IO_C2M_SCL))

#define C2D_PP()        drv_io_SetOutputPP(IO(IO_C2M_SDA))
#define C2D_OD()        drv_io_SetOutputOD(IO(IO_C2M_SDA))
#define C2D_SET(_v)     DRV_IO_Write(IO(IO_C2M_SDA), (_v))
#define C2D_GET()       DRV_IO_Read(IO(IO_C2M_SDA))

#define DELAY_US(_n)    DRV_CPU_DelayUs(_n)
#define DELAY_MS(_n)    DRV_CPU_DelayMs(_n)

#endif


/* low-level driver */
#if 1

#define C2_TIMEOUT_VAL              10000       /* us */
#define C2_PAGE_ERASE_TIMEOUT_VAL   40000       /* us */
#define C2_CHIP_ERASE_TIMEOUT_VAL   20000000UL  /* us */

static BOOL bHigh = HIGH;
static BOOL bLow  = LOW;

static BOOL bIns0;
static BOOL bIns1;
static BOOL bLength0;
static BOOL bLength1;

static UINT8 SEG_BDATA  vC2Data;
SBIT(bC2Bit0, vC2Data, 0);
SBIT(bC2Bit1, vC2Data, 1);
SBIT(bC2Bit2, vC2Data, 2);
SBIT(bC2Bit3, vC2Data, 3);
SBIT(bC2Bit4, vC2Data, 4);
SBIT(bC2Bit5, vC2Data, 5);
SBIT(bC2Bit6, vC2Data, 6);
SBIT(bC2Bit7, vC2Data, 7);

#define c2m_TxBit(_v)       do {                                        \
                                C2D_SET(_v);                            \
                                C2CK_SET(LOW);                          \
                                NOP(); NOP(); NOP(); NOP();             \
                                C2CK_SET(HIGH);                         \
                            } while (0)
#define c2m_RxBit(_v)       do {                                        \
                                NOP(); NOP();                           \
                                C2CK_SET(LOW);                          \
                                NOP(); NOP();                           \
                                CY = C2D_GET();                         \
                                C2CK_SET(HIGH);                         \
                                (_v) = CY;                              \
                            } while (0)

#define c2m_Init()          do {                                        \
                                /* set both pin to open-drain mode,     \
                                 *  to release C2 bus.                  \
                                 */                                     \
                                C2CK_OD();                              \
                                C2D_OD();                               \
                                C2CK_SET(HIGH);                         \
                                C2D_SET(HIGH);                          \
                            } while (0)
#define c2m_Reset()         do {                                        \
                                /* reset target device */               \
                                C2CK_PP();      /* stretch C2CK */      \
                                C2CK_SET(LOW);                          \
                                DELAY_US(20);   /* wait >=20us */       \
                                C2CK_SET(HIGH);                         \
                                DELAY_US(2);    /* wait >=2us */        \
                                C2CK_OD();      /* release C2CK */      \
                            } while (0)
#define c2m_TxStart()       do {                                        \
                                C2D_OD();       /* release C2D */       \
                                C2CK_PP();      /* stretch C2CK */      \
                                c2m_TxBit(bHigh);                       \
                                C2D_PP();       /* stretch C2D */       \
                            } while (0)
#define c2m_TxIns()         do {                                        \
                                c2m_TxBit(bIns0);                       \
                                c2m_TxBit(bIns1);                       \
                            } while (0)
#define c2m_TxLength()      do {                                        \
                                c2m_TxBit(bLength0);                    \
                                c2m_TxBit(bLength1);                    \
                            } while (0)
#define c2m_TxByte()        do {                                        \
                                c2m_TxBit(bC2Bit0);                     \
                                c2m_TxBit(bC2Bit1);                     \
                                c2m_TxBit(bC2Bit2);                     \
                                c2m_TxBit(bC2Bit3);                     \
                                c2m_TxBit(bC2Bit4);                     \
                                c2m_TxBit(bC2Bit5);                     \
                                c2m_TxBit(bC2Bit6);                     \
                                c2m_TxBit(bC2Bit7);                     \
                            } while (0)
#define c2m_RxByte()        do {                                        \
                                c2m_RxBit(bC2Bit0);                     \
                                c2m_RxBit(bC2Bit1);                     \
                                c2m_RxBit(bC2Bit2);                     \
                                c2m_RxBit(bC2Bit3);                     \
                                c2m_RxBit(bC2Bit4);                     \
                                c2m_RxBit(bC2Bit5);                     \
                                c2m_RxBit(bC2Bit6);                     \
                                c2m_RxBit(bC2Bit7);                     \
                            } while (0)
#define c2m_TxTurnAround()  do {                                        \
                                C2D_OD();       /* release C2D */       \
                                C2D_SET(HIGH);                          \
                                C2CK_SET(LOW);                          \
                                NOP();                                  \
                                C2CK_SET(HIGH);                         \
                                NOP(); NOP();                           \
                            } while (0)
#define c2m_Wait()          do {                                        \
                                UINT16  _timeout = C2_TIMEOUT_VAL;      \
                                do {                                    \
                                    c2m_RxBit(bC2Bit0);                 \
                                    DELAY_US(1);                        \
                                } while ((bC2Bit0==LOW) && _timeout--); \
                            } while (0)
#define c2m_TxStop()        do {                                        \
                                /* set both pin to open-drain mode,     \
                                 *  to release C2 bus.                  \
                                 */                                     \
                                C2D_SET(HIGH);                          \
                                C2D_OD();       /* release C2D */       \
                                c2m_TxBit(bHigh);                       \
                                C2CK_OD();      /* release C2CK */      \
                            } while (0)
#define c2m_RxStop()        do {                                        \
                                /* set both pin to open-drain mode,     \
                                 *  to release C2 bus.                  \
                                 */                                     \
                                C2D_OD();       /* release C2D */       \
                                C2CK_OD();      /* release C2CK */      \
                            } while (0)
#define c2m_SetIns(_v)      do {                                        \
                                bIns0 = ((_v)>>0)&0x1;                  \
                                bIns1 = ((_v)>>1)&0x1;                  \
                            } while (0)
#define c2m_SetLength(_v)   do {                                        \
                                bLength0 = (((_v)-1)>>0)&0x1;           \
                                bLength1 = (((_v)-1)>>1)&0x1;           \
                            } while (0)
#define c2m_SetAddr(_v)     do { vC2Data = (UINT16)(_v); } while (0)
#define c2m_SetData(_v)     do { vC2Data = (UINT16)(_v); } while (0)
#define c2m_GetAddr()       (vC2Data)
#define c2m_GetData()       (vC2Data)

/* Performing the Address Write Instruction */
static void c2m_WriteAR(UINT8 vAddr)
{
    BOOL    bIntState;

    c2m_SetIns(0x3);    /* instruction: write address */
    c2m_SetAddr(vAddr);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    c2m_TxStart();      /* tx frame start */
    c2m_TxIns();        /* tx instruction */
    c2m_TxByte();       /* tx address */
    c2m_TxStop();       /* tx frame stop */

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);
}

/* Performing the Address Read Instruction */
static UINT8 c2m_ReadAR(void)
{
    BOOL    bIntState;

    c2m_SetIns(0x2);    /* instruction: read address */

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    c2m_TxStart();      /* tx frame start */
    c2m_TxIns();        /* tx instruction */
    c2m_TxTurnAround(); /* tx turn-around */
    c2m_RxByte();       /* rx address */
    c2m_RxStop();       /* rx frame stop */

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    return c2m_GetAddr();
}

/* Performing the Data Write Instruction */
static void c2m_WriteDR(UINT8 vData)
{
    BOOL    bIntState;

    c2m_SetIns(0x1);    /* instruction: write data */
    c2m_SetLength(0x1); /* length: 1 byte */
    c2m_SetData(vData);

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    c2m_TxStart();      /* tx frame start */
    c2m_TxIns();        /* tx instruction */
    c2m_TxLength();     /* tx length */
    c2m_TxByte();       /* tx address */
    c2m_TxTurnAround(); /* tx turn-around */
    c2m_Wait();         /* wait for target device ready */
    c2m_RxStop();       /* rx frame stop */

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);
}

/* Performing the Data Read Instruction */
static UINT8 c2m_ReadDR(void)
{
    BOOL    bIntState;

    c2m_SetIns(0x0);    /* instruction: read data */
    c2m_SetLength(0x1); /* length: 1 byte */

    /* lock globally interrupt */
    bIntState = DRV_INT_LockGlobalInterrupt();

    c2m_TxStart();      /* tx frame start */
    c2m_TxIns();        /* tx instruction */
    c2m_TxLength();     /* tx length */
    c2m_TxTurnAround(); /* tx turn-around */
    c2m_Wait();         /* wait for target device ready */
    c2m_RxByte();       /* rx data */
    c2m_RxStop();       /* rx frame stop */

    /* unlock globally interrupt */
    DRV_INT_UnlockGlobalInterrupt(bIntState);

    return c2m_GetData();
}

#endif


#if 1

#define C2_DEVICEID             0x00
#define C2_REVID                0x01
#define C2_FPCTL                0x02

#define C2_AR_OUTREADY          0x01
#define C2_AR_INBUSY            0x02
#define C2_AR_OTPBUSY           0x80
#define C2_AR_OTPERROR          0x40
#define C2_AR_FLBUSY            0x80

#define C2_FPDAT_GET_VERSION    0x01
#define C2_FPDAT_GET_DERIVATIVE 0x02
#define C2_FPDAT_DEVICE_ERASE   0x03
#define C2_FPDAT_BLOCK_READ     0x06
#define C2_FPDAT_BLOCK_WRITE    0x07
#define C2_FPDAT_PAGE_ERASE     0x08
#define C2_FPDAT_DIRECT_READ    0x09
#define C2_FPDAT_DIRECT_WRITE   0x0A
#define C2_FPDAT_INDIRECT_READ  0x0B
#define C2_FPDAT_INDIRECT_WRITE 0x0C

#define C2_COMMAND_OK           0x0D

#define C2_FPDAT                0xB4
#define C2_FPDAT2               0xAD
static UINT8    vFPDAT;

#define drv_c2m_IsReady()       ((C2CK_GET() == HIGH) && (C2D_GET() == HIGH))
#define drv_c2m_Reset()         c2m_Reset()
#define drv_c2m_Init()          do {                                            \
                                    /* init programming interface */            \
                                    c2m_Reset();                                \
                                    c2m_WriteAR(C2_FPCTL);                      \
                                    c2m_WriteDR(0x02);                          \
                                    c2m_WriteDR(0x04);                          \
                                    c2m_WriteDR(0x01);                          \
                                    DELAY_MS(20);   /* delay >=20ms */          \
                                } while (0)
#define drv_c2m_PollInBusy(timeout)                                             \
                                do {                                            \
                                    UINT16  _timeout = (timeout);               \
                                    while (((c2m_ReadAR()&C2_AR_INBUSY) != 0)   \
                                           && _timeout--)                       \
                                    {                                           \
                                        DELAY_US(1);                            \
                                    }                                           \
                                } while (0)
#define drv_c2m_PollOutBusy(timeout)                                            \
                                do {                                            \
                                    UINT32  _timeout = (timeout);               \
                                    while (((c2m_ReadAR()&C2_AR_OUTREADY) == 0) \
                                           && _timeout--)                       \
                                    {                                           \
                                        DELAY_US(1);                            \
                                    }                                           \
                                } while (0)
#define drv_c2m_CheckResponse(timeout)                                          \
                                do {                                            \
                                    drv_c2m_PollOutBusy(timeout);               \
                                    if (c2m_ReadDR() != C2_COMMAND_OK)          \
                                    {                                           \
                                        /* invalid response */                  \
                                        goto _exit;                             \
                                    }                                           \
                                } while (0)

static void drv_c2m_WriteSFR(UINT8 vAddr, UINT8 vData)
{
    c2m_WriteAR(vAddr);
    c2m_WriteDR(vData);
}

static UINT8 drv_c2m_ReadSFR(UINT8 vAddr)
{
    c2m_WriteAR(vAddr);
    return c2m_ReadDR();
}

static void drv_c2m_WriteData(UINT8 vCmd)
{
    c2m_WriteDR(vCmd);
    drv_c2m_PollInBusy(C2_TIMEOUT_VAL);
}

static UINT8 drv_c2m_ReadData(void)
{
    drv_c2m_PollOutBusy(C2_TIMEOUT_VAL);
    return c2m_ReadDR();
}

static void drv_c2m_WriteDirect(UINT8 vAddr, UINT8 vData, BOOL bIndirect)
{
    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(bIndirect?C2_FPDAT_DIRECT_WRITE:C2_FPDAT_INDIRECT_WRITE);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(vAddr);   /* SFR address          */
    drv_c2m_WriteData(1);       /* write length: 1 byte */
    drv_c2m_WriteData(vData);   /* write SFR value      */

_exit:
    return;
}

static UINT8 drv_c2m_ReadDirect(UINT8 vAddr, BOOL bIndirect)
{
    UINT8   vData = 0x00;

    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(bIndirect?C2_FPDAT_DIRECT_READ:C2_FPDAT_INDIRECT_READ);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(vAddr);       /* SFR address         */
    drv_c2m_WriteData(1);           /* read length: 1 byte */
    vData = drv_c2m_ReadData();     /* read SFR value      */

_exit:
    return vData;
}

#endif

#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_Reset
 * DESCRIPTION:
 *   C2 master reset target device.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   =TRUE,  reset target device successfully;
 *   =FALSE, reset target device failed;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_C2M_Reset(void)
{
    if (!drv_c2m_IsReady())
    {
        /* C2 bus is not ready */
        return FALSE;
    }

    c2m_Reset();
    return TRUE;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_Probe
 * DESCRIPTION:
 *   C2 master probe target device id.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   Probed target device id. (0xFFFFFFFF indicates no device present)
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
UINT32 DRV_C2M_Probe(void)
{
    UU32    vDevice;

    vDevice.U32 = 0xFFFFFFFFUL;

    if (!drv_c2m_IsReady())
    {
        /* C2 bus is not ready */
        goto _exit;
    }

    drv_c2m_Init();

    /* get C2 device id & revision id */
    vDevice.U8[0] = drv_c2m_ReadSFR(C2_DEVICEID);
    vDevice.U8[1] = drv_c2m_ReadSFR(C2_REVID);

    if (vDevice.U8[0] == 0xFF)
    {
        /* no device probed */
        goto _exit;
    }

    /* get C2 device derivative id */
    vFPDAT = C2_FPDAT;
    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(C2_FPDAT_GET_DERIVATIVE);
    if (drv_c2m_ReadData() != C2_COMMAND_OK)
    {
        /* the FPDAT address may be incorrect, try another FPDAT address */
        vFPDAT = C2_FPDAT2;
        c2m_WriteAR(vFPDAT);
        drv_c2m_WriteData(C2_FPDAT_GET_DERIVATIVE);
        drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    }
    vDevice.U8[2] = drv_c2m_ReadData();

    /* get C2 device derivative version */
    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(C2_FPDAT_GET_VERSION);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    vDevice.U8[3] = drv_c2m_ReadData();

_exit:
    return vDevice.U32;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_ChipErase
 * DESCRIPTION:
 *   C2 master target device chip erase.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   =TRUE : target device chip erase successfully;
 *   =FALSE: target device chip erase failed;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_C2M_ChipErase(void)
{
    BOOL    bDone = FALSE;

    if (!drv_c2m_IsReady())
    {
        /* C2 bus is not ready */
        goto _exit;
    }

    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(C2_FPDAT_DEVICE_ERASE);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(0xDE);     /* send sequence #1 */
    drv_c2m_WriteData(0xAD);     /* send sequence #2 */
    drv_c2m_WriteData(0xA5);     /* send sequence #3 */
    drv_c2m_CheckResponse(C2_CHIP_ERASE_TIMEOUT_VAL);
    bDone = TRUE;

_exit:
    return bDone;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_PageErase
 * DESCRIPTION:
 *   C2 master target device page erase.
 * PARAMETERS:
 *   vPageNo: Flash page number to be erased.
 * RETURN:
 *   =TRUE : target device page erase successfully;
 *   =FALSE: target device page erase failed;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_C2M_PageErase(UINT8 vPageNo)
{
    BOOL    bDone = FALSE;

    if (!drv_c2m_IsReady())
    {
        /* C2 bus is not ready */
        goto _exit;
    }

    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(C2_FPDAT_PAGE_ERASE);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(vPageNo); /* send page number */
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(0x00);    /* initiate erase   */
    drv_c2m_CheckResponse(C2_PAGE_ERASE_TIMEOUT_VAL);
    bDone = TRUE;

_exit:
    return bDone;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_FlashRead
 * DESCRIPTION:
 *   C2 master target device read flash content.
 * PARAMETERS:
 *   pBuf  : Read data buffer;
 *   vAddr : Flash base address to be read;
 *   vCount: Read byte count; (=0: 256 bytes)
 * RETURN:
 *   =TRUE : target device read flash content successfully;
 *   =FALSE: target device read flash content failed;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_C2M_FlashRead
(
    OUT UINT8 SEG_XDATA *pBuf,
    IN  UINT16           vAddr,
    IN  UINT8            vCount
)
{
    UINT16  vLen = ((vCount==0)?256:vCount);
    BOOL    bDone = FALSE;

    if (!drv_c2m_IsReady())
    {
        /* C2 bus is not ready */
        goto _exit;
    }

    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(C2_FPDAT_BLOCK_READ);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(vAddr>>8);    /* MSB of address */
    drv_c2m_WriteData(vAddr&0xFF);  /* LSB of address */
    drv_c2m_WriteData(vCount);      /* read length    */
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    while (vLen--)
    {
        /* read flash data into buffer */
        *pBuf++ = drv_c2m_ReadData();
    }
    bDone = TRUE;

_exit:
    return bDone;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_FlashWrite
 * DESCRIPTION:
 *   C2 master target device write flash content.
 * PARAMETERS:
 *   vAddr : Flash base address to be written;
 *   pBuf  : Data buffer to be written;
 *   vCount: Write byte count; (=0: 256 bytes)
 * RETURN:
 *   =TRUE : target device write flash content successfully;
 *   =FALSE: target device write flash content failed;
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_C2M_FlashWrite
(
    IN       UINT16           vAddr,
    IN const UINT8 SEG_XDATA *pBuf,
    IN       UINT8            vCount
)
{
    UINT16  vLen = ((vCount==0)?256:vCount);
    BOOL    bDone = FALSE;

    if (!drv_c2m_IsReady())
    {
        /* C2 bus is not ready */
        goto _exit;
    }

    c2m_WriteAR(vFPDAT);
    drv_c2m_WriteData(C2_FPDAT_BLOCK_WRITE);
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    drv_c2m_WriteData(vAddr>>8);    /* MSB of address */
    drv_c2m_WriteData(vAddr&0xFF);  /* LSB of address */
    drv_c2m_WriteData(vCount);      /* write length   */
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    while (vLen--)
    {
        /* write data into flash */
        drv_c2m_WriteData(*pBuf++);
    }
    drv_c2m_CheckResponse(C2_TIMEOUT_VAL);
    bDone = TRUE;

_exit:
    return bDone;
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_C2M_Init
 * DESCRIPTION:
 *   C2 master driver init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_C2M_Init(void)
{
    c2m_Init();
}

#endif

#endif

