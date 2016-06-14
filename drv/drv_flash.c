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
 *   Flash driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_FLASH_SUPPORT

/* flash KEY definition, these KEYs must be written sequentially into
 * FLKEY register, to enable erase/write.
 *
 * Note: Plus EA status to the flash key, to improve the firmware stability,
 *        and prevent the flash data changed accidentally while MCU crashed;
 *       Because in normal status, while controlling flash, the interrupt
 *        must be disabled.
 */
#define FLASH_KEY_1        (0xA5 + (UINT8)EA)
#define FLASH_KEY_2         0xF1

/* PSCTL register */
#define PSWE_BIT            0   /* =1, enable flash write; =0, disable flash write. */
#define PSEE_BIT            1   /* =1, enable flash erase; =0, disable flash erase. */

/* flash block size mask */
#define FLASH_PAGE_MASK    (UINT16)(~(FLASH_PAGE_SIZE-1))

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_Flash_Control
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   vFlashAddr: Flash Address.
 *   vPSCTL    : PSCTL Value.
 *   vData     : Write Data.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
static void drv_flash_Control(UINT16 vFlashAddr, UINT8 vPSCTL, UINT8 vData)
{
  #if DRV_WATCHDOG_SUPPORT
    /* kick watchdog, to prevent watchdog reset MCU */
    DRV_WATCHDOG_Kick();
  #endif

    /* Force Enable VDD Monitor as a reset source */
    DRV_RESET_EnableVDDMonitor();

    /* enable flash erase/write */
    PSCTL = vPSCTL;

    /* write KEYs to unlock flash */
    FLKEY = FLASH_KEY_1;
    FLKEY = FLASH_KEY_2;

    /* write data into flash */
    XDATA_U8(vFlashAddr) = vData;

    /* disable flash erase/write */
    PSCTL = 0x00;
}


/******************************************************************************
 * FUNCTION NAME:
 *   drv_flash_ErasePage
 * DESCRIPTION:
 *   Erase flash page.
 * PARAMETERS:
 *   _flashAddr : flash address.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define drv_flash_ErasePage(_flashAddr)                                     \
    drv_flash_Control((_flashAddr), (1<<PSEE_BIT)|(1<<PSWE_BIT), 0x00)


/******************************************************************************
 * FUNCTION NAME:
 *   drv_flash_WriteByte
 * DESCRIPTION:
 *   Write one byte to flash.
 * PARAMETERS:
 *   _flashAddr : Flash address.
 *   _data      : Data to be written.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define drv_flash_WriteByte(_flashAddr, _data)                              \
    drv_flash_Control((_flashAddr), (1<<PSWE_BIT), (_data))


/******************************************************************************
 * FUNCTION NAME:
 *   drv_flash_WriteBytes
 * DESCRIPTION:
 *   Flash write bytes driver.
 * PARAMETERS:
 *   vFlashAddr : Flash start address to be written.
 *   vLen       : Write byte length to flash, count as byte.
 *   vDataAddr  : Write data buffer.
 *   bFromFlash : =TRUE,  the data is from Flash;
 *                =FALSE, the data is from RAM.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
static void drv_flash_WriteBytes
(
    IN UINT16     vFlashAddr,
    IN UINT16     vLen,
    IN UINT16     vDataAddr,
    IN BOOL       bFromFlash
)
{
    while (vLen--)
    {
        UINT8   vData;

        vData = (bFromFlash? CODE_U8(vDataAddr) : XDATA_U8((vDataAddr)&0xFF));
        if (CODE_U8(vFlashAddr) != vData)
        {
            drv_flash_WriteByte(vFlashAddr, vData);
        }
        vFlashAddr++;
        vDataAddr++;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   DRV_FLASH_Update
 * DESCRIPTION:
 *   Flash update driver.
 *   i.e., if the update area is not empty, will auto-erase it,
 *         then write the new data into it.
 * PARAMETERS:
 *   vFlashAddr : Flash start address to be updated.
 *   vLen       : Update byte length from flash, count as byte. (max.256 Byte)
 *   pBuf       : Update data buffer in XRAM.
 * RETURN:
 *   N/A
 * NOTES:
 *   Only support update one flash page, if overlap flash pages,
 *    the result is unknown.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_FLASH_Update
(
    IN       UINT16           vFlashAddr,
    IN       UINT8            vLen,
    IN const UINT8 SEG_XDATA *pBuf
)
{
    UINT8  bIntStatus;
    UINT8  bErase;
    UINT8  vLoop;
    UINT16 vPageBase;
    UINT16 vPageOffset;

    /* globally lock interrupt */
    bIntStatus = DRV_INT_LockGlobalInterrupt();

    /* calculate flash page base address & offset of this page */
    vPageBase   = vFlashAddr & FLASH_PAGE_MASK;
    vPageOffset = vFlashAddr & ~FLASH_PAGE_MASK;

    /* check whether need to erase flash page */
    bErase = FALSE;
    for (vLoop = 0; vLoop < vLen; vLoop++)
    {
        UINT8   vFlashData = CODE_U8(vPageBase+vPageOffset+vLoop);
        UINT8   vRamData   = pBuf[vLoop];

        if ((vFlashData & vRamData) != vRamData)
        {
            bErase = TRUE;
            break;
        }
    }

    if (!bErase)
    {
        /* no need to erase,
          * just write the new data into flash is OK.
          */
        drv_flash_WriteBytes(vFlashAddr, vLen, (UINT16)pBuf, FALSE);
    }
    else
    {
        UINT16 vWriteOffset;

        /* prepare cache page content, to the final flash page content:
         *   1) copy other content into cache page;
         *   2) update cache page with new data;
         */
        vWriteOffset  = FLASH_CACHE_PAGE_BASE;
        drv_flash_WriteBytes(vWriteOffset, vPageOffset, vPageBase, TRUE);
        vWriteOffset += vPageOffset;
        drv_flash_WriteBytes(vWriteOffset, vLen, (UINT16)pBuf, FALSE);
        vWriteOffset += vLen;
        drv_flash_WriteBytes(vWriteOffset,
                             FLASH_PAGE_SIZE - (vPageOffset+vLen),
                             vPageBase+vPageOffset + vLen,
                             TRUE);

        /* erase target flash page */
        drv_flash_ErasePage(vPageBase);

        /* copy cache page content into target flash page */
        vWriteOffset  = FLASH_CACHE_PAGE_BASE;
        drv_flash_WriteBytes(vPageBase, FLASH_PAGE_SIZE, vWriteOffset, TRUE);

        /* erase flash cache page */
        drv_flash_ErasePage(FLASH_CACHE_PAGE_BASE);
    }

    /* restore interrupt status */
    DRV_INT_UnlockGlobalInterrupt(bIntStatus);
}

#endif

