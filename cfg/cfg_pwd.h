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
#define CFG_PWD_OEM             0xDA17B67CUL /* OEM password              */
#define CFG_PWD_FACTORY         0xD1E95B93UL /* factory password          */
#define CFG_PWD_REBOOT          0xE37A97A1UL /* reboot password           */

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

