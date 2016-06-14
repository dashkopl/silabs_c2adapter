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
 *   CLI: I2C Master commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CMD_I2CM_H
#define __CMD_I2CM_H


#if (CLI_SUPPORT && DRV_I2CM_SUPPORT)

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_I2CM_Scan
 * DESCRIPTION:
 *   CLI Command: I2C Master Scan.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_I2CM_Scan(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_I2CM_Read
 * DESCRIPTION:
 *   CLI Command: I2C Master Read.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_I2CM_Read(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_I2CM_Write
 * DESCRIPTION:
 *   CLI Command: I2C Master Write.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_I2CM_Write(void);


/* I2CM related commands */
#define CMD_I2CM_LIST                                                       \
    { CMD_I2CM_Scan,  "i2cm_s",                                         },  \
    { CMD_I2CM_Read,  "i2cm_r -o[0|8|16|24|32] <addr> <off> {<len>}",   },  \
    { CMD_I2CM_Write, "i2cm_w -o[0|8|16|24|32] <addr> <off> {<dat>..}", },  \

#else
 #define CMD_I2CM_LIST      /* empty */
#endif



#endif /* __CMD_I2CM_H */

