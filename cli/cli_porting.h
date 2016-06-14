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
 *   CLI: porting related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CLI_PORTING_H
#define __CLI_PORTING_H


#define CLI_CMD_MAX_LEN                 80
#define CLI_CMD_MAX_PARAM		        8

#define CLI_PROMPT                      ""
#define CLI_DISPLAY_CMD_PROMPT()        VT_Printf("\n\r%s>", CLI_PROMPT)

/* command edit supporting */
#define CLI_CMD_EDIT_SUPPORT            1

/* command history supporting */
#define CLI_CMD_HISTORY_SUPPORT         1
#define CLI_CMD_HISTORY_MAX_ITEM        4   /* should be aligned to 2^n */

/* CLI continuous command.
 * format: <command> <parameters> /C
 */
#define CLI_CONTINUOUS_CMD_SUPPORT      1
#define CLI_CONTINUOUS_CMD_KEYWORD      "/C"

/* CLI comment supporting, for script usage.
 * format: # <comment>
 */
#define CLI_COMMENT_SUPPORT             1
#define CLI_COMMENT_KEYWORD             "#"

/* CLI banner */
#define CLI_BANNER_SUPPORT              1
#define CLI_DISPLAY_BANNER()                                                                            \
    do {                                                                                                \
        printf("\n\r *****************************************************************************");   \
        printf("\n\r   Firmware Version : %bX%.2bX-%.2bX%.2bX-%.2bX-%.2bX-%.2bX-%.2bX",                 \
               FW_VERSION(0), FW_VERSION(1), FW_VERSION(2),                                             \
               FW_VERSION(3), FW_VERSION(4),                                                            \
               FW_VERSION(5), FW_VERSION(6), FW_VERSION(7));                                            \
        printf("\n\r   Build Time       : "__DATE__"  "__TIME__);                                       \
        printf("\n\r *****************************************************************************");   \
        printf("\n\r");                                                                                 \
    } while (0)


#include "cmd_system.h"
#include "cmd_mem.h"
#include "cmd_io.h"
#include "cmd_i2cm.h"
#include "cmd_c2m.h"

#define CLI_CMD_LIST        {                           \
                                CMD_SYSTEM_LIST         \
                                CMD_MEM_LIST            \
                                CMD_IO_LIST             \
                                CMD_I2CM_LIST           \
                                CMD_C2M_LIST            \
                            }


/* for CLI internal usage */
#ifdef __CLI_INTERNAL

#include "vt.h"

extern char  SEG_XDATA * SEG_XDATA aCmdParam[];
extern UINT8 SEG_XDATA  vCmdParamCount;
#define CLI_vParam  (vCmdParamCount)
#define CLI_aParam  (aCmdParam)

#endif


#endif /* __CLI_PORTING_H */

