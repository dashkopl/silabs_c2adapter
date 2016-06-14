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
 *   Mempage definition related.
 * HISTORY:
 *   2016.2.15        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CFG_MEMPAGE_H
#define __CFG_MEMPAGE_H


#include "~cfg_mempage_def.h"

#define MEMPAGE_RAM_PID2LID(pid)    ((pid) - MEMPAGE_RAM_PAGES_HEAD)
#define MEMPAGE_ROM_PID2LID(pid)    ((pid) - MEMPAGE_ROM_PAGES_HEAD)

#define MEMPAGE_RAM_LMA(pid)        (MEMPAGE_RAM_PAGES_BASE + MEMPAGE_RAM_PID2LID(pid)*CFG_RAM_PAGE_SIZE)
#define MEMPAGE_ROM_LMA(pid)        (MEMPAGE_ROM_PAGES_BASE + MEMPAGE_ROM_PID2LID(pid)*CFG_ROM_PAGE_SIZE)

/* mempage type related */
#define MEMPAGE_IsRAM(pid)          (((pid)>=MEMPAGE_RAM_PAGES_HEAD) && ((pid)<=MEMPAGE_RAM_PAGES_TAIL))
#define MEMPAGE_IsROM(pid)          (((pid)>=MEMPAGE_ROM_PAGES_HEAD) && ((pid)<=MEMPAGE_ROM_PAGES_TAIL))


#endif /* __CFG_MEMPAGE_H */


