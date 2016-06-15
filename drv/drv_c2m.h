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
 *   Simulated C2 Master driver related.
 * HISTORY:
 *   2016.5.17        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_C2M_H
#define __DRV_C2M_H


#if DRV_C2M_SUPPORT

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
BOOL DRV_C2M_Reset(void);

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
UINT32 DRV_C2M_Probe(void);

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
BOOL DRV_C2M_ChipErase(void);

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
BOOL DRV_C2M_PageErase(UINT8 vPageNo);

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
);

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
);

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
void DRV_C2M_Init(void);

#endif


#endif /* __DRV_C2M_H */

