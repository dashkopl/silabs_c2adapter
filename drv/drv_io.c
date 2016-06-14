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
 *   GPIO driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


#if DRV_IO_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_IO_Init
 * DESCRIPTION:
 *   IO Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_IO_Init(void)
{
    /* io internal init */
    P0      = _PORT_INIT(P0);
    P1      = _PORT_INIT(P1);
    P2      = _PORT_INIT(P2);
    P3      = _PORT_INIT(P3);
    P0MDIN  = _PORT_MDIN(P0);
    P1MDIN  = _PORT_MDIN(P1);
    P2MDIN  = _PORT_MDIN(P2);
    P3MDIN  = _PORT_MDIN(P3);
    P0MDOUT = _PORT_MDOUT(P0);
    P1MDOUT = _PORT_MDOUT(P1);
    P2MDOUT = _PORT_MDOUT(P2);
    P3MDOUT = _PORT_MDOUT(P3);

    /* default, all pins are skipped for cross-bar */
    P0SKIP = 0xFF;
    P1SKIP = 0xFF;
    P2SKIP = 0xFF;

    /* enable cross-bar */
    XBR0 = 0x00;
    XBR1 = 0x40;
}

#endif

