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
 *   CLI: System commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CMD_SYSTEM_H
#define __CMD_SYSTEM_H


#if CLI_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_System_Clear
 * DESCRIPTION:
 *   CLI Command: clear
 * PARAMETERS:
 *   vParam    : Parameter counts;
 *   aParam[]  : Parameter lists;
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_System_Clear(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_System_Loopback
 * DESCRIPTION:
 *   CLI Command: loopback
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_System_Loopback(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_System_Reboot
 * DESCRIPTION:
 *   CLI Command: reboot
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_System_Reboot(void);


/* system related commands */
#define CMD_SYSTEM_LIST                                                     \
    { CMD_System_Clear,     "cls",                                  },      \
    { CMD_System_Loopback,  "loopback",                             },      \
    { CMD_System_Reboot,    "reboot",                               },      \

#endif


#endif /* __CMD_SYSTEM_H */

