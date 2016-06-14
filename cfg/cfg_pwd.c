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

