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
 *   Configuration password related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __CFG_PWD_H
#define __CFG_PWD_H


#if CFG_SUPPORT

#ifdef _CFG_PWD_INTERNAL_
 #define _CFG_PWD_EXTERNAL_   /* empty */
#else
 #define _CFG_PWD_EXTERNAL_   extern
#endif

/* Config password level definition:
 *  -> NORMAL  : Default password level.
 *  -> USER_RO : For customer read-only  User EEPROM fields usage.
 *  -> USER_RW : For customer read/write User EEPROM fields usage.
 *  -> OEM     : For OEM write vendor fields usage.
 *  -> FACTORY : For factory calibration/diagnostic usage.
 */
#define CFG_PWD_DEFAULT         0x00000000UL /* default power-on password */
#define CFG_PWD_OEM             0xFC54D402UL /* OEM password              */
#define CFG_PWD_FACTORY         0xFDE7554FUL /* factory password          */
#define CFG_PWD_REBOOT          0xF62652A7UL /* reboot password           */

#define CFG_PWD_LEVEL_NORMAL    0x00        /* normal level          */
#define CFG_PWD_LEVEL_UserRO    0x01        /* user read-only level  */
#define CFG_PWD_LEVEL_UserRW    0x02        /* user read/write level */
#define CFG_PWD_LEVEL_OEM       0x04        /* OEM level             */
#define CFG_PWD_LEVEL_FACTORY   0x08        /* factory level         */
#define CFG_PWD_LEVEL_ROOT      0xFF        /* unused top level      */

_CFG_PWD_EXTERNAL_ UINT8        vCfgPwdLevel;
#define PWD_LEVEL_GET()         (vCfgPwdLevel)
#define PWD_LEVEL_SET(_v)       do { vCfgPwdLevel = (UINT8)(_v); } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_PWD_GetLevel
 * DESCRIPTION:
 *   Get run-time password level.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define CFG_PWD_GetLevel()      PWD_LEVEL_GET()

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_PWD_RefreshLevel
 * DESCRIPTION:
 *   Refresh config password level.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void CFG_PWD_RefreshLevel(void);

/******************************************************************************
 * FUNCTION NAME:
 *   CFG_PWD_Init
 * DESCRIPTION:
 *   Password init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void CFG_PWD_Init(void);

#endif


#endif /* __CFG_PWD_H */

