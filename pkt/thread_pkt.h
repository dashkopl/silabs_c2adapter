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

