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

