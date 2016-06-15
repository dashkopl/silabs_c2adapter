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
 *   System power-on start entry.
 * HISTORY:
 *   2016.1.29        Panda.Xiong          Create
 *
 *****************************************************************************/

#define __assemble__
#include "boot_define.h"
#include "version.h"


/* standard SFR symbols */
#define SP      0x81
#define PCA0MD  0xD9


/* told compiler:
 *  ?STACK should be stored into idata area.
 *
 *  but, the Keil compiler may place it into data area,
 *   from the unused data start address,
 *   to make sure the stacking always use the deepest stack depth.
 */
?STACK      SEGMENT   IDATA
RSEG    ?STACK
    DS      1       /* Force reserving 1 byte for stacking */


/* told compiler that this function is an external API */
EXTRN CODE (?C_START)


/******************************************************************************
 * CPU power on entry
 *****************************************************************************/
    CSEG    AT  APPL_BASE
PUBLIC  ?C_STARTUP
?C_STARTUP:
    LJMP    _handler_reset


/* signature field */
    CSEG   AT  APPL_BASE+SIG_OFFSET
PUBLIC __sig
__sig:
    DB  MCU_TYPE        /* mcu type                */
    DB  IMAGE_TYPE      /* image type              */
    DB  FW_VERSION      /* file version            */
    DD  0x00000000      /* file user-defined-field */
    DD  0x00000000      /* file content size       */
    DD  0x00000000      /* file padded size        */
    DD  0x00000000      /* file checksum           */


/* told compiler:
 *  ?C_C51STARTUP should be stored into code area,
 *   and it must be put here (Including keil library)
 */
?C_C51STARTUP   SEGMENT   CODE
RSEG    ?C_C51STARTUP


/******************************************************************************
 * system start from here
 *****************************************************************************/
_handler_reset:

/* disable watchdog */
    CLR     A
    MOV     PCA0MD, A


/* clear IRAM to 0 */
#if (IRAM_SIZE > 0)

    MOV     R0, #(IRAM_SIZE - 1)

  idata_loop:
    MOV     @R0, A
    DJNZ    R0,  idata_loop

#endif


/* clear XRAM to 0 */
#if (XRAM_SIZE > 0)
 #if (XRAM_SIZE < 0x100)

    MOV     R0, #(XRAM_BASE)
    MOV     R7, #(XRAM_SIZE)

  pdata_loop:
    MOVX    @R0, A
    INC     R0
    DJNZ    R7,  pdata_loop

 #else

    MOV     DPTR, #(XRAM_BASE)
    MOV     R6,   #((XRAM_SIZE>>8)&0xFF)
    MOV     R7,   #((XRAM_SIZE>>0)&0xFF)

  xdata_loop:
    MOVX    @DPTR, A
    INC     DPTR
    DJNZ    R7, xdata_loop
    DJNZ    R6, xdata_loop

 #endif
#endif


/* init stack pointer */
    MOV     SP, #(?STACK - 1)


/* jump to main().
 *
 *  before jump to main(), the keil will call the internal library,
 *  to init static values.
 */
    LJMP    ?C_START


END

