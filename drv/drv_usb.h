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
 *   USB driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_USB_H
#define __DRV_USB_H


#if DRV_USB_SUPPORT

#define DRV_USB_BLOCK_MAX_LEN   64  /* bytes */

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_USB_WriteBlock
 * DESCRIPTION:
 *   Write USB block data.
 * PARAMETERS:
 *   _block : Block buffer;
 *   _len   : Block length to be written;
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 ******************************************************************************/
#define DRV_USB_WriteBlock(_block, _len)    Block_Write((_block), (_len))

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_USB_ReadBlock
 * DESCRIPTION:
 *   Read USB block data.
 * PARAMETERS:
 *   _block: Block buffer;
 *   _len  : Block length to be read;
 * RETURN:
 *   Actual read block data length;
 * NOTES:
 *   None
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 ******************************************************************************/
#define DRV_USB_ReadBlock(_block, _len)     Block_Read((_block), (_len))

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_USB_GetInterruptSource
 * DESCRIPTION:
 *   Get USB interrupt source.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   USB interrupt source.
 * NOTES:
 *   None
 * HISTORY:
 *   2016.01.06        Panda.Xiong        Create/Update
 ******************************************************************************/
#define DRV_USB_GetInterruptSource()        Get_Interrupt_Source()

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_USB_Enable
 * DESCRIPTION:
 *   Enable USB Slave interface.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 ******************************************************************************/
#define DRV_USB_Enable()                    USB_Int_Enable()

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_USB_Init
 * DESCRIPTION:
 *   USB init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 ******************************************************************************/
void DRV_USB_Init(void);

#endif


#endif /* __DRV_USB_H */

