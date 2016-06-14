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
 *   Debug supporting.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DBG_H
#define __DBG_H


#if DRV_UART_SUPPORT
 #define __info         printf
 #define __warning      printf
 #define __error        printf
 #define __fatal        printf
#else
 #define __info         if
 #define __warning      if
 #define __error        if
 #define __fatal        if
#endif


#endif /* __DBG_H */

