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

#define _CFG_PWD_INTERNAL_
#include "cfg.h"
#include "drv.h"


#if CFG_SUPPORT

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
void CFG_PWD_RefreshLevel(void)
{
    UINT32  vPasswd = CFG_GET(Vendor_PWD_Entry);

    switch (vPasswd)
    {
        case CFG_PWD_REBOOT:    /* reboot password */
            DRV_RESET_SoftwareReset();
            break;

        case CFG_PWD_FACTORY:   /* factory password */
            PWD_LEVEL_SET(CFG_PWD_LEVEL_FACTORY);
            break;

        case CFG_PWD_OEM:       /* OEM password */
            PWD_LEVEL_SET(CFG_PWD_LEVEL_OEM);
            break;

        default:
            if (vPasswd == CFG_GET(Vendor_PWD_UserRW))
            {
                /* UserRW password */
                PWD_LEVEL_SET(CFG_PWD_LEVEL_UserRW);
            }
            else if (vPasswd == CFG_GET(Vendor_PWD_UserRO))
            {
                /* UserRO password */
                PWD_LEVEL_SET(CFG_PWD_LEVEL_UserRO);
            }
            else
            {
                PWD_LEVEL_SET(CFG_PWD_LEVEL_NORMAL);
            }
            break;
    }
}


/******************************************************************************
 * FUNCTION NAME:
 *   CFG_PWD_Init
 * DESCRIPTION:
 *   Configuration password init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
void CFG_PWD_Init(void)
{
    /* set default password */
    CFG_SET(Vendor_PWD_Entry, CFG_PWD_DEFAULT);

    /* refresh password level */
    CFG_PWD_RefreshLevel();
}

#endif

