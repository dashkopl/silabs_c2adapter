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
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __BOOT_DEFINE_H
#define __BOOT_DEFINE_H


#include "cfg_system_def.h"

/* signature offset */
#define SIG_OFFSET          0x01E0

/* internal RAM (DATA/BDATA/IDATA) */
#define IRAM_SIZE           0x0100  /* 256B */

/* external RAM (PDATA/XDATA) */
#define XRAM_BASE           0x0000
#define XRAM_SIZE           0x0400  /* 1KB  */

/* flash */
#define FLASH_PAGE_SIZE     512
#define FLASH_BASE          0x0000
#define FLASH_SIZE          0xFA00  /* 62.5KB */

/* flash allocation */
#define BOOT_BASE           FLASH_BASE
#define BOOT_SIZE           0x0000  /* 0KB  */
#define APPL_BASE           (BOOT_BASE + BOOT_SIZE)
#define APPL_SIZE           (FLASH_SIZE - BOOT_SIZE)


#endif /* __BOOT_DEFINE_H */

