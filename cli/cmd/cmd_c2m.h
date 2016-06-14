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
 *   CLI: C2 Master commands related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CMD_C2M_H
#define __CMD_C2M_H


#if (CLI_SUPPORT && DRV_C2M_SUPPORT)

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_Reset
 * DESCRIPTION:
 *   CLI Command: C2 Master Reset Target Device.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_Reset(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_Probe
 * DESCRIPTION:
 *   CLI Command: C2 Master Probe Target Device ID.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_Probe(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_ChipErase
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Chip Erase.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_ChipErase(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_PageErase
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Page Erase.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_PageErase(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_ReadFlash
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Read Flash.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_ReadFlash(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CMD_C2M_WriteFlash
 * DESCRIPTION:
 *   CLI Command: C2 Master Target Device Write Flash.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.01.02        Panda.Xiong         Create/Update
 *****************************************************************************/
void CMD_C2M_WriteFlash(void);


/* C2M related commands */
#define CMD_C2M_LIST                                                        \
    { CMD_C2M_Reset,      "c2m_reset",                          },          \
    { CMD_C2M_Probe,      "c2m_probe",                          },          \
    { CMD_C2M_ChipErase,  "c2m_chiperase",                      },          \
    { CMD_C2M_PageErase,  "c2m_pageerase <page_no>",            },          \
    { CMD_C2M_ReadFlash,  "c2m_readflash <addr> {<len>}",       },          \
    { CMD_C2M_WriteFlash, "c2m_writeflash <addr> <dat> {..}",   },          \

#else
 #define CMD_C2M_LIST      /* empty */
#endif



#endif /* __CMD_C2M_H */

