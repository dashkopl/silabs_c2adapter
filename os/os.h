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
 *   OS related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __OS_H
#define __OS_H


#include "drv.h"
#include "pt-sem.h"

typedef char            OS_HANDLE;
typedef struct pt       OS_TCB;
typedef struct pt_sem   OS_SCB;

/* sleep millisecond */
#define OS_SLEEP_MS(tcb, ms)                                                        \
    do {                                                                            \
        static SEG_XDATA UINT64 vEndTick;                                           \
        vEndTick = (DRV_TIMER_GetTick() + (ms)/DRV_TIMER_INTERVAL);                 \
        PT_WAIT_WHILE(tcb, (DRV_WATCHDOG_Kick(), DRV_TIMER_GetTick()<vEndTick));    \
    } while (0)

typedef OS_HANDLE (*PT_FUNC)(void);
typedef void      (*PT_INIT_FUNC)(void);

/******************************************************************************
 * FUNCTION NAME:
 *   OS_Start
 * DESCRIPTION:
 *   OS Start Entry.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 ******************************************************************************/
void OS_Start(void);

/******************************************************************************
 * FUNCTION NAME:
 *   OS_Init
 * DESCRIPTION:
 *   OS Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 ******************************************************************************/
void OS_Init(void);


#endif /* __OS_H */

