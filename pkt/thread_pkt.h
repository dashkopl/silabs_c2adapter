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
 *   Thread: USB packet related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __THREAD_PKT_H
#define __THREAD_PKT_H


/******************************************************************************
 * FUNCTION NAME:
 *   thread_Pkt_Notify
 * DESCRIPTION:
 *   Thread-Packet event notify callback.
 * PARAMETERS:
 *   vEvent : Notify event.
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void thread_Pkt_Notify(IN UINT8 vEvent);

/******************************************************************************
 * FUNCTION NAME:
 *   thread_PKT_Entry
 * DESCRIPTION:
 *   Pkt Thread Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   OS_HANDLE
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.25        Panda.Xiong        Create/Update
 *****************************************************************************/
OS_HANDLE thread_PKT_Entry(void);

/******************************************************************************
 * FUNCTION NAME:
 *   thread_PKT_Init
 * DESCRIPTION:
 *   N/A
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2014.06.25        Panda.Xiong        Create/Update
 *****************************************************************************/
void thread_PKT_Init(void);


#endif /* __THREAD_PKT_H */

