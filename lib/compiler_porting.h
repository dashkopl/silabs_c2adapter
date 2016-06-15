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

#ifndef __COMPILER_PORTING_H
#define __COMPILER_PORTING_H


#include "compiler_defs.h"

#ifndef __C51__
 #error "Unsupported compiler yet!"
#endif

#define CROL(v, n)              do { (v) = _crol_((v), (n)); } while (0)
#define CROR(v, n)              do { (v) = _cror_((v), (n)); } while (0)
#define SBIT(name, addr, bit)   sbit name = addr^bit

/* macros defined in absacc.h (Keil C51) */
#define CBYTE               ((UINT8  volatile SEG_CODE  *)0)
#define DBYTE               ((UINT8  volatile SEG_DATA  *)0)
#define PBYTE               ((UINT8  volatile SEG_PDATA *)0)
#define XBYTE               ((UINT8  volatile SEG_XDATA *)0)
#define CWORD               ((UINT16 volatile SEG_CODE  *)0)
#define DWORD               ((UINT16 volatile SEG_DATA  *)0)
#define PWORD               ((UINT16 volatile SEG_PDATA *)0)
#define XWORD               ((UINT16 volatile SEG_XDATA *)0)
#define CDWORD              ((UINT32 volatile SEG_CODE  *)0)
#define DDWORD              ((UINT32 volatile SEG_DATA  *)0)
#define PDWORD              ((UINT32 volatile SEG_PDATA *)0)
#define XDWORD              ((UINT32 volatile SEG_XDATA *)0)

/* macro defined for memory accessing */
#define CODE_U8(_addr)      (*(UINT8  volatile SEG_CODE  *)((UINT16)(_addr)))
#define CODE_U16(_addr)     (*(UINT16 volatile SEG_CODE  *)((UINT16)(_addr)))
#define CODE_U32(_addr)     (*(UINT32 volatile SEG_CODE  *)((UINT16)(_addr)))
#define DATA_U8(_addr)      (*(UINT8  volatile SEG_DATA  *)((UINT8) (_addr)))
#define DATA_U16(_addr)     (*(UINT16 volatile SEG_DATA  *)((UINT8) (_addr)))
#define DATA_U32(_addr)     (*(UINT32 volatile SEG_DATA  *)((UINT8) (_addr)))
#define PDATA_U8(_addr)     (*(UINT8  volatile SEG_PDATA *)((UINT8) (_addr)))
#define PDATA_U16(_addr)    (*(UINT16 volatile SEG_PDATA *)((UINT8) (_addr)))
#define PDATA_U32(_addr)    (*(UINT32 volatile SEG_PDATA *)((UINT8) (_addr)))
#define XDATA_U8(_addr)     (*(UINT8  volatile SEG_XDATA *)((UINT16)(_addr)))
#define XDATA_U16(_addr)    (*(UINT16 volatile SEG_XDATA *)((UINT16)(_addr)))
#define XDATA_U32(_addr)    (*(UINT32 volatile SEG_XDATA *)((UINT16)(_addr)))


#endif /* __COMPILER_PORTING_H */

