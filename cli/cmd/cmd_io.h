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
 *   CLI: GPIO commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CMD_IO_H
#define __CMD_IO_H


#if (CLI_SUPPORT && DRV_IO_SUPPORT)

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_IO_Write
 * DESCRIPTION:
 *   CLI Command: IO Write pin.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.30        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_IO_Write(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_IO_Monitor
 * DESCRIPTION:
 *   CLI Command: IO Monitor All Pins.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2015.12.30        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_IO_Monitor(void);


/* IO related commands */
#define CMD_IO_LIST                                                         \
    { CMD_IO_Write,     "io_w <port> <bit> <val>",      },                  \
    { CMD_IO_Monitor,   "io_m",                         },                  \

#endif


#endif /* __CMD_IO_H */

