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

