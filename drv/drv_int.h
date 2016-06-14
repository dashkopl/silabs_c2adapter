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
 *   Interrupt related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_INT_H
#define __DRV_INT_H


/* disable all interrupt */
#define DRV_INT_DisableAllInterrupt()       do { IE = 0x00; EIE1 = 0x00; } while (0)

/* global interrupt related */
#define DRV_INT_GlobalEnableInterrupt()     do { EA = 1; } while (0)
#define DRV_INT_GlobalDisableInterrupt()    do { EA = 0; } while (0)
#define DRV_INT_IsGlobalInterruptEnable()   (EA)
#define DRV_INT_LockGlobalInterrupt()       ((EA)? (EA=0, TRUE) : FALSE)
#define DRV_INT_UnlockGlobalInterrupt(_s)   do { EA = (_s); } while (0)

/* lock/unlock UART interrupt */
#define DRV_INT_LockUartInterrupt()         ((ES0)? (ES0=0, TRUE) : FALSE)
#define DRV_INT_UnlockUartInterrupt(_s)     do { ES0=(_s); } while (0)
#define DRV_INT_IsUartInterruptLocked()     (ES0 == 0)


#endif /* __DRV_INT_H */

