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

