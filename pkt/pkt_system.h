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

