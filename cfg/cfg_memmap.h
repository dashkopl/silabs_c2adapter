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
 *   Memmap definition related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CFG_MEMMAP_H
#define __CFG_MEMMAP_H


#include "~cfg_memmap_def.h"

/* memory type */
#define MEMMAP_TYPE_UNIT            0
#define MEMMAP_TYPE_BIT             1

/* memory LMA type */
#define MEMMAP_LMA_TYPE_RAM         0
#define MEMMAP_LMA_TYPE_ROM         1
#define MEMMAP_LMA_TYPE_VIRTUAL     2

#define MEMMAP_TYPE(name)           (UINT8)COMBINE2(MEMMAP_TYPE_,        name)
#define MEMMAP_PAGE(name)           (UINT8)COMBINE2(MEMMAP_PAGE_,        name)
#define MEMMAP_ADDR(name)           (UINT8)COMBINE2(MEMMAP_ADDR_,        name)
#define MEMMAP_OFFSET(name)         (UINT8)COMBINE2(MEMMAP_OFFSET_,      name)
#define MEMMAP_BIT(name)            (UINT8)COMBINE2(MEMMAP_BIT_,         name)
#define MEMMAP_LEN(name)            (UINT8)COMBINE2(MEMMAP_LEN_,         name)
#define MEMMAP_REAL_OFFSET(name)    (UINT8)COMBINE2(MEMMAP_REAL_OFFSET_, name)

#define MEMMAP_LMA_TYPE(name)       (UINT8)COMBINE2(MEMMAP_LMA_TYPE_,    name)
#define MEMMAP_LMA(name)            (UINT16)COMBINE2(MEMMAP_LMA_,        name)

#define MEMMAP_BIT_MASK(name)       (UINT32)(GET_MASK(MEMMAP_BIT(name),MEMMAP_LEN(name)))
#define MEMMAP_GET_BIT(v, name)     (((UINT32)(v) & MEMMAP_BIT_MASK(name)) >> MEMMAP_BIT(name))


#endif /* __CFG_MEMMAP_H */

