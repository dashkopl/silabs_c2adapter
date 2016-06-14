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

