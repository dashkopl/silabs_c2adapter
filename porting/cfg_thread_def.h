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
 *   Thread definition related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#include "thread_idle.h"
#include "thread_led.h"
#include "thread_pkt.h"


#ifdef DECLARE_THREAD

/* Protothread Definition.
 *
 *   entry     : Thread entry; (if non-exist or unused, set to NULL)
 *   init_func : Thread init function; (if non-exist or unused, set to NULL)
 *   desc      : Thread description;
 *
 *   Note      :
 *      N/A
 */

/*                     entry              init_func       desc   */
DECLARE_THREAD(thread_IDLE_Entry, thread_IDLE_Init, "Idle Thread")
DECLARE_THREAD(thread_LED_Entry,  thread_LED_Init,  "LED Thread")

#if PKT_SUPPORT
DECLARE_THREAD(thread_PKT_Entry, thread_PKT_Init,   "USB Packet Thread")
#endif

#endif

