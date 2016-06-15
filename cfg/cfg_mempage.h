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


