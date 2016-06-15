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
 *   Packet command: System related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __PKT_SYSTEM_H
#define __PKT_SYSTEM_H


#if PKT_SYSTEM_SUPPORT

UINT16 PKT_System_Inspect(void);
UINT16 PKT_System_Loopback(void);

/* SYSTEM related commands */
#define PKT_SYSTEM_CMD_LIST                                                 \
    { 0x0000, PKT_System_Inspect,  },                                       \
    { 0x0010, PKT_System_Loopback, },                                       \

#else

/* SYSTEM related commands */
#define PKT_SYSTEM_CMD_LIST        /* empty */

#endif


#endif /* __PKT_SYSTEM_H */

