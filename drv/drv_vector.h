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
 *   Vector related.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#ifndef __DRV_VECTOR_H
#define __DRV_VECTOR_H


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

