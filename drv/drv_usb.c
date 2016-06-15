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

#include "cfg.h"
#include "drv.h"


#if DRV_USB_SUPPORT

/* USB related strings: maximum 16 bytes USB string */
#define DRV_USB_STRING_TABLE_LEN  (2+16*2)
static UINT8 SEG_XDATA  aManufacturerStr[DRV_USB_STRING_TABLE_LEN];
static UINT8 SEG_XDATA  aProductStr[DRV_USB_STRING_TABLE_LEN];
static UINT8 SEG_XDATA  aSerialNumberStr[DRV_USB_STRING_TABLE_LEN];

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_USB_Init
 * DESCRIPTION:
 *   USB init driver.
 * PARAMETERS:
 *   None
 * RETURN:
 *
 * NOTES:
 *   None
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 ******************************************************************************/
void DRV_USB_Init(void)
{
    UINT8   vData;
    UINT8   vLoop;

    /* init USB manufacture string */
    aManufacturerStr[1] = 0x03;
    for (vLoop=2; vLoop<sizeof(aManufacturerStr); vLoop+=2)
    {
        vData = CFG_GETO8(EE_Vendor_Name, (vLoop>>1)-1);

        if ((vData < 0x20) || (vData >= 0x7F))
        {
            break;
        }

        aManufacturerStr[vLoop+0] = vData;
        aManufacturerStr[vLoop+1] = 0;
    }
    aManufacturerStr[0] = vLoop;

    /* init USB product string */
    aProductStr[1] = 0x03;
    for (vLoop=2; vLoop<sizeof(aProductStr); vLoop+=2)
    {
        vData = CFG_GETO8(EE_Vendor_PN, (vLoop>>1)-1);

        if ((vData < 0x20) || (vData >= 0x7F))
        {
            break;
        }

        aProductStr[vLoop+0] = vData;
        aProductStr[vLoop+1] = 0;
    }
    aProductStr[0] = vLoop;

    /* init USB serial number string */
    aSerialNumberStr[1] = 0x03;
    for (vLoop=2; vLoop<sizeof(aSerialNumberStr); vLoop+=2)
    {
        vData = CFG_GETO8(EE_Vendor_SN, (vLoop>>1)-1);

        if ((vData < 0x20) || (vData >= 0x7F))
        {
            break;
        }

        aSerialNumberStr[vLoop+0] = vData;
        aSerialNumberStr[vLoop+1] = 0;
    }
    aSerialNumberStr[0] = vLoop;

    /* set USB0 to the high priority level interrupt */
    EIP1 |= (1<<1);

    /* init USB device */
    USB_Clock_Start();
    USB_Init(DRV_USB_VID,
             DRV_USB_PID,
             aManufacturerStr,
             aProductStr,
             aSerialNumberStr,
             0xFA,      /* maximum current: 500mA */
             0x80,      /* bus-powered, remote wakeup is unsupported */
             0x100);    /* device release number 1.00 */

    /* the USB_Init() API will auto-enable global interrupt,
     * disable it here, and will be enabled later.
     */
    DRV_INT_GlobalDisableInterrupt();
}

#endif

