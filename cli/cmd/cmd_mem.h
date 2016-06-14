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
 *   CLI: Memory commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CMD_MEM_H
#define __CMD_MEM_H


#if CLI_SUPPORT

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_Mem_Read
 * DESCRIPTION:
 *   CLI Command: Read memory data.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_Mem_Read(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_Mem_Write
 * DESCRIPTION:
 *   CLI Command: Memory write Data.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2011.10.19        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_Mem_Write(void);


/* memory related commands */
#define CMD_MEM_LIST                                                        \
    { CMD_Mem_Read,     "m_r [code|xdata] <adr> {<cnt>}",      },           \
    { CMD_Mem_Write,    "m_w [code|xdata] <adr> <dat> {...}",  },           \

#endif


#endif /* __CMD_MEM_H */

