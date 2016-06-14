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

