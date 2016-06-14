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

#define __CLI_INTERNAL
#include "cfg.h"
#include "drv.h"
#include "cli_porting.h"


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
void CMD_System_Clear(void)
{
    VT_ClearScreen(0);
}


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
void CMD_System_Loopback(void)
{
    printf("\n\r Warning: "
           "\n\r  Once entered loopback mode, "
           "\n\r  only hardware reset can recover to normal mode."
           "\n\r Continue? (Y/N) ");

    /* waiting for confirmation */
    for (;;)
    {
        int vChar = VT_ReadKey(PENDING);

        switch (vChar)
        {
            case 'Y':
            case 'y':
                printf("Y\n");
                goto _loopback;

            case 'N':
            case 'n':
                printf("N\n");
                return;

            default:
                break;
        }
    }

    /* echo loopback data */
  _loopback:
    for (;;)
    {
        UINT8 vChar = (UINT8)VT_ReadKey(PENDING);
        printf(" %.2bX", vChar);
    }
}


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
void CMD_System_Reboot(void)
{
    printf("\n\r System Rebooting ...");

    for (;;)
    {
        DRV_RESET_SoftwareReset();
    }
}

#endif

