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
 *   Simulated I2C Master driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_I2CM_H
#define __DRV_I2CM_H


#if DRV_I2CM_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_Stream
 * DESCRIPTION:
 *   I2C master send write/read combined stream.
 * PARAMETERS:
 *   vI2cAddr  : I2C slave chip address.
 *   vWriteLen : Write length.
 *   aWriteBuf : Write buffer.
 *   vReadLen  : Read length.
 *   aReadBuf  : Read buffer.
 * RETURN:
 *   TRUE   : Send stream successfully.
 *   FALSE  : Send stream failed.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_I2CM_Stream
(
    IN       UINT8      vI2cAddr,
    IN       UINT8      vWriteLen,
    IN const UINT8     *aWriteBuf,
    IN       UINT8      vReadLen,
    OUT      UINT8     *aReadBuf
);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_Probe
 * DESCRIPTION:
 *   I2C master probe chip.
 * PARAMETERS:
 *   vI2cAddr : I2C chip address.
 * RETURN:
 *   TRUE   : Probe successfully.
 *   FALSE  : Probe failed.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
BOOL DRV_I2CM_Probe(IN UINT8 vI2cAddr);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_ReadByte
 * DESCRIPTION:
 *   I2C master random read one byte.
 * PARAMETERS:
 *   vI2cAddr : I2C slave chip address.
 *   vOffset  : I2C offset.
 * RETURN:
 *   I2C read data.
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
UINT8 DRV_I2CM_ReadByte(IN UINT8 vI2cAddr, IN UINT8 vOffset);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_WriteByte
 * DESCRIPTION:
 *   I2C master random write one byte.
 * PARAMETERS:
 *   vI2cAddr : I2C slave chip address.
 *   vOffset  : I2C offset.
 *   vData    : I2C data to be written.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_I2CM_WriteByte(IN UINT8 vI2cAddr, IN UINT8 vOffset, IN UINT8 vData);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_I2CM_Init
 * DESCRIPTION:
 *   I2C master driver init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_I2CM_Init(void);

#endif


#endif /* __DRV_I2CM_H */

