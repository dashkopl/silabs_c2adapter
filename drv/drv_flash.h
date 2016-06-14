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

#ifndef __DRV_FLASH_H
#define __DRV_FLASH_H


#if DRV_FLASH_SUPPORT

/* the last flash page is used as flash auto-update cache */
#define FLASH_CACHE_PAGE_BASE       ((FLASH_BASE+FLASH_SIZE) - FLASH_PAGE_SIZE)

/* EEPROM related API */
#define EEPROM_MEMCPY(dst,src,len)                                          \
    do {                                                                    \
        DRV_FLASH_Update((UINT16)(dst),                                     \
                         (UINT8)(len),                                      \
                         (const UINT8 SEG_XDATA *)(src));                   \
    } while (0)

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
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_FLASH_Init
 * DESCRIPTION:
 *   Flash driver internal init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
 #define DRV_FLASH_Init()               /* do nothing */

#else
 #define EEPROM_MEMCPY(dst,src,len)     NO_WARNING((dst)+(src)+(len))
 #define DRV_FLASH_Init()               /* do nothing */
#endif


#endif /* __DRV_FLASH_H */

