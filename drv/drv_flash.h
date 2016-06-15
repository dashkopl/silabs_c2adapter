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

/* EEPROM/FLASH External API */
#define EEPROM_MEMCPY(_dst,_src,_len)   FLASH_MEMCPY((_dst), (_src), (_len))
#define FLASH_MEMCPY(_dst,_src,_len)    DRV_FLASH_Update((UINT16)(_dst),                    \
                                                         (const UINT8 SEG_XDATA *)(_src),   \
                                                         (UINT8)(_len))

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_FLASH_Update
 * DESCRIPTION:
 *   Flash update API.
 * PARAMETERS:
 *   vDstAddr : Flash start address to be updated.
 *   pSrcAddr : Update data buffer in ram.
 *   vLen     : Update byte length from flash, unit of byte. (max. 256 bytes)
 * RETURN:
 *   N/A
 * NOTES:
 *   1) If the update area is not empty, will auto-erase it,
 *       then write the new data into it.
 *   2) Only support update one flash page, if overlap flash pages,
 *       the overlapped data will be forcibly ignored.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_FLASH_Update
(
    IN       UINT16           vDstAddr,
    IN const UINT8 SEG_XDATA *pSrcAddr,
    IN       UINT8            vLen
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
#define DRV_FLASH_Init()                /* do nothing */

#else
 #define EEPROM_MEMCPY(dst,src,len)     NO_WARNING((dst)+(src)+(len))
 #define DRV_FLASH_Init()               /* do nothing */
#endif


#endif /* __DRV_FLASH_H */

