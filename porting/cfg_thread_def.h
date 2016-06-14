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

