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

