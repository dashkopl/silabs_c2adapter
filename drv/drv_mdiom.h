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

#ifndef __DRV_MDIOM_H
#define __DRV_MDIOM_H


#if DRV_MDIOM_SUPPORT

/* MDIO Low-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FrameAddress
 * DESCRIPTION:
 *      MDIO Master Low-Level API: Execute Frame - Address.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FrameWrite
 * DESCRIPTION:
 *      MDIO Master Low-Level API: Execute Frame - Write.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FrameRead
 * DESCRIPTION:
 *      MDIO Master Low-Level API: Execute Frame - Read.
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
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_FramePRIA
 * DESCRIPTION:
 *      MDIO Master Low-Level API: Execute Frame - Post-Read-Inc-Address.
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
);

#endif


/* MDIO High-Level API */
#if 1

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_ReadWords
 * DESCRIPTION:
 *      MDIO Master Read Words Data.
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
    IN  UINT8               vDataLen,
    OUT UINT16 SEG_XDATA   *pDataBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_WriteWords
 * DESCRIPTION:
 *      MDIO Master Write Words Data.
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
    IN       UINT8              vDataLen,
    IN const UINT16 SEG_XDATA  *pDataBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *      DRV_MDIOM_Init
 * DESCRIPTION:
 *      MDIO Master Driver Init.
 * PARAMETERS:
 *      N/A
 * RETURN:
 *      N/A
 * NOTES:
 *      N/A
 * HISTORY:
 *      2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void DRV_MDIOM_Init(void);

#endif

#endif


#endif /* __DRV_MDIOM_H */

