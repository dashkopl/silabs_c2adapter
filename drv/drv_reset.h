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
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_RESET_H
#define __DRV_RESET_H


#if DRV_RESET_SUPPORT

#define RSTSRC_USBRSF_BIT   7   /* USB Reset Flag                         */
#define RSTSRC_FERROR_BIT   6   /* Flash Error Reset Flag                 */
#define RSTSRC_C0RSEF_BIT   5   /* Comparator0 Reset Enable and Flag      */
#define RSTSRC_SWRSF_BIT    4   /* Software Reset Force and Flag          */
#define RSTSRC_WDTRSF_BIT   3   /* Watchdog Timer Reset Flag              */
#define RSTSRC_MCDRSF_BIT   2   /* Missing Clock Detector Enable and Flag */
#define RSTSRC_PORSF_BIT    1   /* Power-On/VDD Monitor Reset Flag, and VDD monitor Reset Enable */
#define RSTSRC_PINRSF_BIT   0   /* HW Pin Reset Flag                      */

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_RESET_EnableVDDMonitor
 * DESCRIPTION:
 *   Force Enable VDD Monitor as a reset source.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_RESET_EnableVDDMonitor()                                        \
    do {                                                                    \
        VDM0CN = 0x80;                                                      \
        RSTSRC = (1<<RSTSRC_MCDRSF_BIT) | (1<<RSTSRC_PORSF_BIT);            \
    } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_RESET_SoftwareReset
 * DESCRIPTION:
 *   Force Software Reset.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_RESET_SoftwareReset()                                           \
    do { RSTSRC = (1<<RSTSRC_PORSF_BIT) | (1<<RSTSRC_SWRSF_BIT); } while (0)

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_RESET_Init
 * DESCRIPTION:
 *   Init Reset Source.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_RESET_Init()        /* do nothing */

#endif


#endif /* __DRV_RESET_H */

