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
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_MDIOM_H
#define __DRV_MDIOM_H


#if DRV_MDIOM_SUPPORT

/* MDIO Low-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FrameAddr
 * DESCRIPTION:
 *   MDIO Master Low-Level API: Execute Frame - Address.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FrameWrite
 * DESCRIPTION:
 *   MDIO Master Low-Level API: Execute Frame - Write.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FrameRead
 * DESCRIPTION:
 *   MDIO Master Low-Level API: Execute Frame - Read.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_FramePRIA
 * DESCRIPTION:
 *   MDIO Master Low-Level API: Execute Frame - Post-Read-Inc-Address.
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
);

#endif


/* MDIO High-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_Probe
 * DESCRIPTION:
 *   MDIO master probe chip.
 * PARAMETERS:
 *   vPortAddr : MDIO Port Address;
 *   vDevAddr  : MDIO Device Address;
 * RETURN:
 *   TRUE   : Probe successfully.
 *   FALSE  : Probe failed.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_MDIOM_Probe(_vPortAddr, _vDevAddr)                              \
                    DRV_MDIOM_FrameRead((_vPortAddr),(_vDevAddr),NULL)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_ReadWords
 * DESCRIPTION:
 *   MDIO Master Read Words Data.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_WriteWords
 * DESCRIPTION:
 *   MDIO Master Write Words Data.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_MDIOM_Init
 * DESCRIPTION:
 *   MDIO Master Driver Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_MDIOM_Init(void);

#endif

#endif


#endif /* __DRV_MDIOM_H */

