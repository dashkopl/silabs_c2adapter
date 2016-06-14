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
 *   CLI: GPIO commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#define __CLI_INTERNAL
#include "cfg.h"
#include "drv.h"
#include "cli_porting.h"


#if (CLI_SUPPORT && DRV_IO_SUPPORT)

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_IO_Write
 * DESCRIPTION:
 *   CLI Command: IO Write pin.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.30        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_IO_Write(void)
{
    UINT8   vPort;
    UINT8   vBit;
    UINT8   vValue;

    if (CLI_vParam != 4)
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    vPort  = (UINT8)strtoul(CLI_aParam[1], NULL, 0);
    vBit   = (UINT8)strtoul(CLI_aParam[2], NULL, 0);
    vValue = (UINT8)strtoul(CLI_aParam[3], NULL, 0);

    if ((vPort > IO_PORT_MAX) || (vBit > IO_BIT_MAX) || (vValue > 1))
    {
        printf("\n\rInvalid Parameter!");
        return;
    }

    switch (vPort)
    {
      #if (IO_PORT_MAX >= 0)
        case 0 : drv_io_Write(P0, vBit, vValue); break;
      #endif
      #if (IO_PORT_MAX >= 1)
        case 1 : drv_io_Write(P1, vBit, vValue); break;
      #endif
      #if (IO_PORT_MAX >= 2)
        case 2 : drv_io_Write(P2, vBit, vValue); break;
      #endif
      #if (IO_PORT_MAX >= 3)
        case 3 : drv_io_Write(P3, vBit, vValue); break;
      #endif
      #if (IO_PORT_MAX >= 4)
        case 4 : drv_io_Write(P4, vBit, vValue); break;
      #endif
        default: break;
    }

    printf("\n\r IO Write P%bd.%bd=%bd ", vPort, vBit, vValue);
}


/******************************************************************************
 * FUNCTION NAME:
 *   CMD_IO_Monitor
 * DESCRIPTION:
 *   CLI Command: IO Monitor All Pins.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.30        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_IO_Monitor(void)
{
    UINT8   vPort;
    UINT8   vBit;

    printf("\n\r All IO Read Status:");
    for (vPort = 0; vPort <= IO_PORT_MAX; vPort++)
    {
        UINT8   vPortVal;

        printf("\n\r");

        switch (vPort)
        {
          #if (IO_PORT_MAX >= 0)
            case 0 : vPortVal = P0;   break;
          #endif
          #if (IO_PORT_MAX >= 1)
            case 1 : vPortVal = P1;   break;
          #endif
          #if (IO_PORT_MAX >= 2)
            case 2 : vPortVal = P2;   break;
          #endif
          #if (IO_PORT_MAX >= 3)
            case 3 : vPortVal = P3;   break;
          #endif
          #if (IO_PORT_MAX >= 4)
            case 4 : vPortVal = P4;   break;
          #endif
            default: vPortVal = 0x00; break;
        }

        for (vBit = 0; vBit <= IO_BIT_MAX; vBit++)
        {
            printf("  P%bd.%bd=%bd", vPort, vBit, (UINT8)READ_BIT(vPortVal, vBit));
        }
    }
}

#endif

