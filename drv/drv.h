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
 *   Driver related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_H
#define __DRV_H


/* core related peripheral */
#include "c8051f32x_defs.h"
#include "drv_int.h"
#include "drv_cpu.h"
#include "drv_vector.h"

/* on-chip digital peripheral */
#include "drv_clock.h"
#include "drv_reset.h"
#include "drv_pca.h"
#include "drv_watchdog.h"
#include "drv_io.h"
#include "drv_uart.h"
#include "drv_timer.h"
#include "drv_flash.h"
#include "drv_usb.h"

/* on-chip analog peripheral */
#include "drv_vref.h"
#include "drv_adc.h"

/* simulated peripheral */
#include "drv_i2cm.h"
#include "drv_mdiom.h"
#include "drv_c2m.h"

/* others */
#include "dbg.h"
#include "usbxpress_lib_f32x.h"

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_Entry
 * DESCRIPTION:
 *   Driver entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_Entry()         /* do nothing */

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_Init
 * DESCRIPTION:
 *   Driver init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_Init(void);

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_Init
 * DESCRIPTION:
 *   Driver pre-init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void DRV_PreInit(void);


#endif /* __DRV_H */

