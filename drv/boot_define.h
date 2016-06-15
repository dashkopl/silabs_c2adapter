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
#define FLASH_SIZE          0x3C00  /* 15KB */

/* flash allocation */
#define BOOT_BASE           FLASH_BASE
#define BOOT_SIZE           0x0000  /* 0KB  */
#define APPL_BASE           (BOOT_BASE + BOOT_SIZE)
#define APPL_SIZE           (FLASH_SIZE - BOOT_SIZE)


#endif /* __BOOT_DEFINE_H */

