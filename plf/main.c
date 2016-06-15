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
 *   Platform system start entry.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "cfg.h"
#include "drv.h"


/******************************************************************************
 * FUNCTION NAME:
 *   _fixupInit
 * DESCRIPTION:
 *   System FixUp Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   This is a post init after system is ready.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
static void _fixupInit(void)
{
    /* Globally enable Interrupt */
    DRV_INT_GlobalEnableInterrupt();

  #if DRV_USB_SUPPORT
	/* enable USB interface */
	DRV_USB_Enable();
  #endif
}


/******************************************************************************
 * FUNCTION NAME:
 *   main
 * DESCRIPTION:
 *   System entry of C file.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void main(void)
{
	/* previous init */
	DRV_PreInit();

    /* init protothread */
    OS_Init();

    /* fixup init */
    _fixupInit();

    /* start protothread (never return) */
    OS_Start();
}

