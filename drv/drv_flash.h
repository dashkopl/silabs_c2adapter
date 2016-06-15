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

