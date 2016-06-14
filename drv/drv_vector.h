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
 *   Vector related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_VECTOR_H
#define __DRV_VECTOR_H


/* extended interrupt ID definition */
#define INTERRUPT_UserUSB       17  /* User USB ID (C8051F34x) */

/* register group definition */
#define REG_GROUP_0             0   /* register group 0 */
#define REG_GROUP_1             1   /* register group 1 */
#define REG_GROUP_2             2   /* register group 2 */
#define REG_GROUP_3             3   /* register group 3 */

#define __interrupt(_int_id)    interrupt _int_id
#define __using(_reg_group)     using _reg_group

/******************************************************************************
 * FUNCTION NAME:
 *   DRV_VECTOR_Init
 * DESCRIPTION:
 *   Vector Init.
 * PARAMETERS:
 *   N/A
 * RETURN:
 *   N/A
 * NOTES:
 *   N/A
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *****************************************************************************/
#define DRV_VECTOR_Init()       /* empty */


#endif /* __DRV_VECTOR_H */

