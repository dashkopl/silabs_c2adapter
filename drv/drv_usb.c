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

