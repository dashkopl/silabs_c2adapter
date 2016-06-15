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

#ifndef __TYPEDEF_H
#define __TYPEDEF_H


#include "compiler_porting.h"

/* these parameters are defined only for easy code reading */
#define IN                      /* nothing */
#define OUT                     /* nothing */

/* NULL pointer */
#ifdef NULL
 #undef NULL
#endif
#define NULL                    ((void *)0)

typedef bit                     BOOL;       /* Boolean: TRUE/FALSE */
typedef unsigned char           UINT8;      /*  8-bit */
typedef signed   char           SINT8;
typedef unsigned short          UINT16;     /* 16-bit */
typedef signed   short          SINT16;
typedef unsigned long           UINT32;     /* 32-bit */
typedef signed   long           SINT32;
#ifdef __have_longlong64
typedef unsigned long long      UINT64;     /* 64-bit */
typedef signed   long long      SINT64;
#else
typedef UINT32                  UINT64;     /* 64-bit */
typedef SINT32                  SINT64;
#endif

#define TRUE                    (BOOL)1
#define FALSE                   (BOOL)0
#define HIGH                    1
#define LOW                     0
#define ENABLE                  TRUE
#define DISABLE                 FALSE


#endif /* __TYPEDEF_H */

